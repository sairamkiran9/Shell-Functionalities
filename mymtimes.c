#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

#define DEFAULT_HRS 24
#define DEFAULT_SECS 3600

void print_mtimes(time_t mytime, int mtimes[])
{
    /**
     * This method prints number files modifed for every hour from past 24 hrs.
     */
    char mytime_str[32];
    struct tm *mytime_info;

    mytime_info = localtime(&mytime);

    /* Update current time to 24hrs back */
    mytime_info->tm_hour -= 24;
    mytime = mktime(mytime_info);

    /* Iterate recursively and print number of files modified from the last 24hrs */
    for (int i = 23; i >= 0; i--)
    {
        /* Using strftime to modify timestamp format as required */
        strftime(mytime_str, sizeof(mytime_str), "%a %b %d %H:%M:%S %Y", mytime_info);
        printf("%s: %d\n", mytime_str, mtimes[i]);

        /* Increment current time by 1hr for each iteration */
        mytime_info->tm_hour += 1;
        mytime = mktime(mytime_info);
    }
}

/* Function to recursively traverse the directory and its subdirectories */
void get_mtimes(const char *dir, int *mtimes, time_t current_time)
{
    char path[1024];
    DIR *directory;
    time_t file_mtime;
    struct dirent *entry;
    struct stat stat_buf;

    /* Check if the directory can be opened */
    if (!(directory = opendir(dir)))
    {
        return;
    }

    /* Read all the entries in the directory */
    while ((entry = readdir(directory)) != NULL)
    {
        snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
        /* Check if the entry is a directory */
        if (entry->d_type == DT_DIR &&
            strcmp(entry->d_name, ".") != 0 &&
            strcmp(entry->d_name, "..") != 0)
        {
            get_mtimes(path, mtimes, current_time);
        }
        /* Check if the entry is a regular file */
        else if (entry->d_type == DT_REG)
        {
            if (lstat(path, &stat_buf) == -1)
            {
                closedir(directory);
                return;
            }

            file_mtime = stat_buf.st_mtime;
            int time_diff = (current_time - file_mtime) / DEFAULT_SECS;

            /* Check if the file was modified in the past 24 hours */
            if (DEFAULT_HRS > time_diff)
            {
                mtimes[time_diff] += 1;
            }
        }
    }
    closedir(directory);
    return;
}

int main(int argc, char *argv[])
{
    char *dir = ".";
    int mtimes[24] = {0};

    /* Check if a directory path was provided as an argument */
    if (argc == 2)
    {
        dir = argv[1];
    }

    /* Fetch current local time */
    time_t current_time;
    current_time = time(NULL);

    /* Check for files that got modified in the last 24hrs */
    get_mtimes(dir, mtimes, current_time);

    /* Print number files that got modified every hr from the last 24hrs */
    print_mtimes(current_time, mtimes);

    return 0;
}
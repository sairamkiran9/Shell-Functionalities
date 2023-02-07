#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

void print_mymtimes(int count[]){
    time_t mytime;
    struct tm *mytime_info;
    char mytime_str[50];
    mytime = time(NULL);
    mytime_info = localtime(&mytime);

    // strftime(mytime_str, sizeof(mytime_str), "%a %b %d %H:%M:%S %Y", mytime_info);
    // printf("%s\n", mytime_str);
    
    mytime_info->tm_hour -= 24;
    mytime = mktime(mytime_info);

    for (int i = 0; i < 24; i++)
    {
        strftime(mytime_str, sizeof(mytime_str), "%a %b %d %H:%M:%S %Y", mytime_info);
        printf("%s: %d\n", mytime_str, count[mytime_info->tm_hour ]);
        mytime_info->tm_hour++;
        mytime = mktime(mytime_info);
    }
}

// Function to recursively traverse the directory and its subdirectories
void check_dir(const char *dir, int *count)
{
    DIR *directory;
    struct dirent *entry;
    struct stat stat_buf;
    char path[1024];
    time_t current_time, file_time;
    struct tm *time_info;

    // Check if the directory can be opened
    if (!(directory = opendir(dir)))
        return;

    current_time = time(NULL);

    // Read all the entries in the directory
    while ((entry = readdir(directory)) != NULL)
    {
        // Check if the entry is a regular file
        if (entry->d_type == DT_REG)
        {
            snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
            if (lstat(path, &stat_buf) == -1)
            {
                printf("Error: %s\n", "000");
                closedir(directory);
                return;
            }
            file_time = stat_buf.st_mtime;

            // printf("%d\n", file_time);

            // Check if the file was modified in the past 24 hours
            if (difftime(current_time, file_time) <= 86400)
            {
                time_info = localtime(&file_time);
                count[time_info->tm_hour]++;
            }
        }
        // Check if the entry is a directory
        else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
            check_dir(path, count);
        }
    }

    closedir(directory);
    return;
}

int main(int argc, char *argv[])
{
    int count[24] = {0};
    char *dir = ".";
    
    // Check if a directory path was provided as an argument
    if (argc == 2)
    {
        dir = argv[1];
    }

    check_dir(dir, count);

    print_mymtimes(count);

    return 0;
}
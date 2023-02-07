#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>

void check_dir(const char *dir, int *count)
{
    DIR *d = opendir(dir);
    struct dirent *entry;
    struct stat stat_buf;
    char path[1024];
    time_t current_time, file_time;
    struct tm *time_info;

    if (!d)
    {
        printf("Error opening directory: %s\n", dir);
        return;
    }

    current_time = time(NULL);
    while ((entry = readdir(d)) != NULL)
    {
        if (entry->d_type == DT_REG)
        {
            snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
            if (lstat(path, &stat_buf) == -1)
            {
                printf("Error: %s\n", "000");
                closedir(d);
                return;
            }
            file_time = stat_buf.st_mtime;
            if (difftime(current_time, file_time) <= 86400)
            {
                time_info = localtime(&file_time);
                count[time_info->tm_hour]++;
            }
        }
        else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            snprintf(path, sizeof(path), "%s/%s", dir, entry->d_name);
            check_dir(path, count);
        }
    }

    closedir(d);
}

int main(int argc, char *argv[])
{
    int count[24] = {0};
    char *dir = ".";

    if (argc == 2)
    {
        dir = argv[1];
    }

    check_dir(dir, count);

    for (int i = 0; i < 24; i++)
    {
        printf("%02d:00-%02d:00: %d files\n", i, i + 1, count[i]);
    }

    return 0;
}

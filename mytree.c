#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static long dir_count = 0;
static long file_count = 0;

void print_tree(char *d_name, int depth)
{
    int i;
    for (i = 0; i < depth; i++)
    {
        printf("%s", "|   ");
    }
    printf("%s%s\n", "|-- ", d_name);
}

int print_dir_tree(char *prev_path, char *path, int depth, char *prefix)
{
    int n;
    struct dirent **namelist;
    char new_path[4096], *next_prefix, *segment;
    strcpy(new_path, prev_path);

    if ((strcmp(prev_path, "") != 0) &&
        (strcmp(prev_path, "./") != 0) &&
        (strcmp(prev_path, "../") != 0))
    {
        strcat(new_path, "/");
    }

    strcat(new_path, path);

    n = scandir(new_path, &namelist, NULL, alphasort);

    if (n == -1)
    {
        perror("scandir");
        return 0;
    }

    while (n--)
    {
        if (strncmp(namelist[n]->d_name, ".", 1) == 0)
        {
            free(namelist[n]);
            continue;
        }

        // print_tree(namelist[n]->d_name, depth);
        printf("%s%s%s\n", prefix, "|-- ", namelist[n]->d_name);
        if (namelist[n]->d_type == DT_DIR)
        {
            dir_count++;

            if (n == 2)
                segment = "    ";
            else
                segment = "|   ";

            next_prefix = malloc(strlen(prefix) + strlen(segment) + 1);
            sprintf(next_prefix, "%s%s", prefix, segment);
            print_dir_tree(new_path, namelist[n]->d_name, depth + 1, next_prefix);
        }
        else
        {
            file_count++;
        }
        free(namelist[n]);
    }

    free(namelist);
    return 0;
}

int main(int argc, char *argv[])
{
    char *dir = ".";

    // Check if a directory path was provided as an argument
    if (argc == 2)
    {
        dir = argv[1];
    }

    printf("%s\n", dir);
    print_dir_tree("", dir, 0, "");

    printf("\n%ld directories, %ld files\n", dir_count, file_count);

    return 0;
}

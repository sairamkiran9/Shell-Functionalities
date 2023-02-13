/**
 * This method walk's recursively through all the
 * parent and child directories and prints the output
 * similar to Unix tree command
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

static long dir_count = 0;
static long file_count = 0;

int print_dir_tree(char *prev_path, char *path, char *branch)
{
    /**
     * Recursive method which crawl's through sub-directories
     */
    int n, idx = 0;
    struct dirent **namelist;
    char new_path[4096], *next_branch, *segment;
    strcpy(new_path, prev_path);

    if ((strcmp(prev_path, "") != 0) &&
        (strcmp(prev_path, "./") != 0) &&
        (strcmp(prev_path, "../") != 0))
    {
        strcat(new_path, "/");
    }

    strcat(new_path, path);

    /**
     * fetch all files and directories to an array is sorted format
     */
    n = scandir(new_path, &namelist, NULL, alphasort);

    if (n == -1)
    {
        perror("failed scandir");
        return 0;
    }

    while (idx < n)
    {
        /* ignore . files */
        if (strncmp(namelist[idx]->d_name, ".", 1) == 0)
        {
            free(namelist[idx]);
            idx++;
            continue;
        }

        printf("%s%s%s\n", branch, "|-- ", namelist[idx]->d_name);
        /* Check if the entry is a directory */
        if (namelist[idx]->d_type == DT_DIR)
        {
            dir_count++;

            /* check for next prefix */
            if (idx == n - 1)
            {
                segment = "    ";
            }
            else
            {
                segment = "|   ";
            }

            /* update prefix branch */
            next_branch = malloc(strlen(branch) + strlen(segment) + 1);
            sprintf(next_branch, "%s%s", branch, segment);
            print_dir_tree(new_path, namelist[idx]->d_name, next_branch);
            free(next_branch);
        }
        /* Check if the entry is a regular file */
        else if (namelist[idx]->d_type == DT_REG)
        {
            file_count++;
        }
        free(namelist[idx]);
        idx++;
    }

    free(namelist);
    return 0;
}

int main(int argc, char *argv[])
{
    char *dir = ".";

    /* Check if a directory path was provided as an argument */
    if (argc == 2)
    {
        dir = argv[1];
    }

    printf("%s\n", dir);
    print_dir_tree("", dir, "");

    /* Print total number of files and directories */
    printf("\n%ld directories, %ld files\n", dir_count, file_count);

    return 0;
}

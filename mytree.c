#include <stdio.h>
#include <string.h>
#include <dirent.h>

static long dir_count = 0;
static long file_count = 0;

void print_depth(char *d_name, int depth, char *flag){
    int i;
    for(i=0;i<depth;i++){
        printf("%s", "|   ");
    }
    printf("%s%s%s\n", "|-- ", d_name, flag);
}

void print_directory_tree(char *path, int depth) {
    DIR *directory;
    struct dirent *dir;

    if (!(directory = opendir(path)))
        return;
    while ((dir = readdir(directory)) != NULL) {
        if (dir->d_type != DT_DIR) {
            file_count++;
            print_depth(dir->d_name, depth, "");      
        } else {
            char subdir[4096];

            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
                continue;

            snprintf(subdir, sizeof(subdir), "%s/%s", path, dir->d_name);
            dir_count++;
            print_depth(dir->d_name, depth, "/");         
            print_directory_tree(subdir, depth + 1);
        }
    }
    closedir(directory);
}

int main(int argc, char *argv[]) {
    char *path;
    if (argc < 2) path = "./";
    else path = argv[1];

    printf("%s\n", path);
    print_directory_tree(path, 0);
    printf("\n%ld directories, %ld files\n", dir_count, file_count);
    return 0;
}

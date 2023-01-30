#include <stdio.h>
#include <string.h>
#include <dirent.h>

void print_depth(char *d_name, int depth){
    int i;
    for(i=0;i<depth;i++){
        printf("%s", "|   ");
    }
    printf("%s%s/\n", "|-- ", d_name);
}

void print_directory_tree(char *path, int depth) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(path)))
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type != DT_DIR) {
            print_depth(entry->d_name, depth);      
        } else {
            char subdir[4096];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(subdir, sizeof(subdir), "%s/%s", path, entry->d_name);
            print_depth(entry->d_name, depth);         
            print_directory_tree(subdir, depth + 1);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    char *path;
    long 
    if (argc < 2) path = "./";
    else path = argv[1];

    printf("%s\n", path);
    print_directory_tree(path, 0);

    return 0;
}

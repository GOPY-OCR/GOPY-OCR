#include "file_utils.h"


int file_exists(const char *filename){
    return access(filename, F_OK) == 0;
}


char **list_files(const char *path, const int n, int append_path) {
    DIR *dir;
    struct dirent *ent;
    char **files = malloc(n * sizeof(char *));
    int i = 0;

    int pathle = strlen(path);
    pathle -= pathle > 0 && path[pathle - 1] == '/'; // ignore trailing slash

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL && i < n) {
            if (ent->d_type == DT_REG) {
                if (append_path) {
                    int filele = strlen(ent->d_name);
                    files[i] = malloc(pathle + filele + 2);
                    strcpy(files[i], path);
                    files[i][pathle] = '/';
                    strcpy(files[i] + pathle + 1, ent->d_name);
                } else {
                    files[i] = malloc(strlen(ent->d_name) + 1);
                    strcpy(files[i], ent->d_name);
                }
                if (files[i] != NULL) {
                    i++;
                }
            }
        }
        closedir(dir);
    } else {
        errx(1, "list_files: Could not open directory %s", path);
    }

    return files;
}


int count_files_in_dir(const char *path) {
    DIR *dir;
    struct dirent *ent;
    int i = 0;

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (ent->d_type == DT_REG) {
                i++;
            }
        }
        closedir(dir);
    } else {
        errx(1, "count_files_in_dir: Could not open directory %s", path);
    }

    return i;
}

#include "file_utils.h"


int file_exists(const char *filename){
    return access(filename, F_OK) == 0;
}

int dir_exists(const char *dirname){
    struct stat st;
    return stat(dirname, &st) == 0 && S_ISDIR(st.st_mode);
}

char **list_files(const char *path, const int n, int append_path) {
    DIR *dir;
    struct dirent *ent;
    char **files = malloc((n+1) * sizeof(char *));
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

    files[i] = NULL;

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

// source: https://stackoverflow.com/questions/5467725/how-to-delete-a-directory-and-its-contents-in-posix-c
void delete_dir_recursive(const char path[]){
    size_t path_len;
    char *full_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry;

    // stat for the path
    stat(path, &stat_path);

    if (S_ISDIR(stat_path.st_mode) == 0) {
        errx(1, "delete_dir_recursive: %s is not a directory", path);
    }

    if ((dir = opendir(path)) == NULL) {
        errx(1, "delete_dir_recursive: Could not open directory %s", path);
    }

    // the length of the path
    path_len = strlen(path);

    // iteration through entries in the directory
    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        // determinate a full path of an entry
        full_path = calloc(path_len + strlen(entry->d_name) + 2, sizeof(char));
        strcpy(full_path, path);
        strcat(full_path, "/");
        strcat(full_path, entry->d_name);

        // stat for the entry
        stat(full_path, &stat_entry);

        // recursively remove a nested directory
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            delete_dir_recursive(full_path);
            continue;
        }

        // remove a file object
        if (unlink(full_path) != 0)
            errx(1, "delete_dir_recursive: Could not remove file %s", full_path);
        free(full_path);
    }

    // remove the devastated directory and close the object of it
    if (rmdir(path) != 0)
        errx(1, "delete_dir_recursive: Could not remove directory %s", path);

    closedir(dir);
}

void copy_file(const char *src, const char *dst) {
    FILE *fsrc = fopen(src, "rb");
    FILE *fdst = fopen(dst, "wb");

    if (fsrc == NULL) {
        errx(1, "copy_file: Could not read file %s", src);
    }
    if (fdst == NULL) {
        errx(1, "copy_file: Could not write file %s", dst);
    }


    char buf[BUFSIZ];
    size_t size;
    while ((size = fread(buf, 1, BUFSIZ, fsrc)) > 0) {
        fwrite(buf, 1, size, fdst);
    }

    fclose(fsrc);
    fclose(fdst);
}

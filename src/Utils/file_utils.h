#pragma once
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <err.h>
#include <ftw.h>
#include <stdio.h>


int file_exists(const char *filename);

int dir_exists(const char *dirname);

// list files and sub-directories in a directory
//
// path: path to directory
// n: initial number of files to list, will be modified
//    with the number of files found
// append_path: if true, filenames will be prefixed with the path
// returns: list of files in directory
char **list_files(const char *path, const int n, int append_path);



int count_files_in_dir(const char *path);


void delete_dir_recursive(const char path[]);



void copy_file(const char *src, const char *dst);

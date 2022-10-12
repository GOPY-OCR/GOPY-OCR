#ifndef SOLVER_H
#define SOLVER_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>
#include <string.h>
#include <err.h>

int find_grid_number();
void save_grid_file(const int grid[81], const char *filename);

#endif

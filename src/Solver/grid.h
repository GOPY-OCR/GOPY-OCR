#ifndef SOLVER_GRID_H
#define SOLVER_GRID_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>
#include <string.h>
#include <err.h>

int find_grid_number();
void save_grid_file(const char *filename, const int grid[]);
int *load_grid_file(const char *filename);
void print_grid(const int grid[]);

#endif

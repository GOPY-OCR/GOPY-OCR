#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "solver.h"
#include "grid.h"


int main(int argc, char **argv) 
{ 
    if (argc != 1){
        errx(1, "You must give the file of the sudoku to solve");
    }

    else{
        int grid[81] = {0};
        char file[strlen(file) + 7] = argv[1];
        load_grid_file(file, grid);
        Solve(grid);
        strcat(file, ".result");
        save_grid_file(grid, file);
    }

    return 0; 
}

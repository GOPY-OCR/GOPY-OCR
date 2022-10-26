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
        char file[strlen(argv[1]) + 7] = argv[1];
        load_grid_file(file, grid);
        
        int board[][9] = {0};
        size_t line = 0;
        size_t column = 0;
        int count = 0;

        for (size_t i = 0; i < 81; i ++){
            if (column == 8){
                line += 1;
                column = 0;
            }

            board[line][column] = grid[i];
            column += 1;
        }

        Solve(board);
        strcat(file, ".result");
        save_grid_file(grid, file);
    }

    return 0; 
}

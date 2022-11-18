#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include "solver.h"
#include "grid.h"


int main(int argc, char **argv) 
{ 
    if (argc != 2){
        errx(1, "You should enter one argument");
    }

    else{
        char *file = calloc(strlen(argv[1]) + 7, sizeof(char));
        strcat(file, argv[1]);
        int *board = load_grid_file(file);
        
        Solve(board);
        strcat(file, ".result");
        save_grid_file(file, board);

        free(board);
        free(file);
    }

    return 0; 
}

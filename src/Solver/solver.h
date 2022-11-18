#ifndef SOLVER_H
#define SOLVER_H
#include <stdio.h>
#include <stdlib.h>

// Size of the board
// Just in case to avoid conflicts with postprocess functions
#ifndef BOARDSIZE
    #define BOARDSIZE 9
#endif

//PROTOTYPES
int IsLineValid(int board[], size_t line);
int IsColumnValid(int board[], size_t column);
int IsSquareValid(int board[], size_t line, size_t column);
int IsBoardValid(int board[]);
int IsSolved(int board[]);
int Solve(int board[]);


#endif

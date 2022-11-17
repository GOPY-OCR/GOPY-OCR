#ifndef SOLVER_H
#define SOLVER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//size of the board
#define BOARDSIZE 9

//PROTOTYPES
int IsLineValid(int board[], size_t line);
int IsColumnValid(int board[], size_t column);
int IsSquareValid(int board[], size_t line, size_t column);
int IsBoardValid(int board[]);
int IsSolved(int board[]);
int Solve(int board[]);


#endif

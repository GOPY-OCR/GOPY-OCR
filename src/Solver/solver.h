#ifndef SOLVER_H
#define SOLVER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//size of the board
#define BOARDSIZE 9

//PROTOTYPES
int IsLineValid(int board[BOARDSIZE], size_t line);
int IsColumnValid(int board[BOARDSIZE], size_t column);
int IsSquareValid(int board[BOARDSIZE], int line, int column);
int IsBoardValid(int board[BOARDSIZE]);
int IsSolved(int board[BOARDSIZE]);
int Solve(int board[BOARDSIZE]);


#endif

#ifndef SOLVER_H
#define SOLVER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int BOARDSIZE = 9;

//PROTOTYPES
int Contains(int list[], int x);
int IsLineValid(int board[][BOARDSIZE]);
int IsColumnValid(int board[][BOARDSIZE]);
int IsSquareValid(int board[][BOARDSIZE], int line, int column);
int IsBoardValid(int board[][BOARDSIZE]);
int IsSolved(int board[][BOARDSIZE]);
int Solve(int board[][BOARDSIZE]);


#endif

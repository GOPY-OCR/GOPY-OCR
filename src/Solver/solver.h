#ifndef SOLVER_H
#define SOLVER_H


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//PROTOTYPES
int Contains(int list[], int x);
int IsLignValid(int board[][BOARDSIZE]);
int IsColumnValid(int board[][BOARDSIZE]);
int IsSquareValid(int board[][BOARDSIZE], int lign, int column);
int IsBoardValid(int board[][BOARDSIZE]);
int IsSolved(int board[][BOARDSIZE]);
int Solve(int board[][BOARDSIZE]);


#endif

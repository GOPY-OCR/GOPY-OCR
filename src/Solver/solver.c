#include "solver.h"

//Contains checks if an element x is in the list
//returns 1 if the list contains x
//else returns 0
int Contains(int list[], int x){
    size_t i = 0;
    while ((int)i < BOARDSIZE && list[i] != x)
        i ++;
    return ((int)i == BOARDSIZE) ? 0 : 1;
}

//_IsLineValid checks if the lign is valid
int IsLineValid(int board[][BOARDSIZE]){
    for (size_t line = 0; (int)line < BOARDSIZE; line ++){
        int numbers[BOARDSIZE] = {0};
        for (size_t column = 0; (int)column < BOARDSIZE; column ++){
            if (board[line][column] != 0){
                if (numbers[board[line][column] - 1] == 1){
                    return 0;
                }
                else{ 
                    numbers[board[line][column] - 1] = 1;
                }
            }
        }
    }

    return 1;
}

//_IsColumnValid checks if the column is valid
int IsColumnValid(int board[][BOARDSIZE]){
     for (size_t column = 0; (int)column < BOARDSIZE; column ++){
         int numbers[BOARDSIZE] = {0};
         for (size_t line = 0; (int)line < BOARDSIZE; line ++){
            if (board[line][column] != 0){
                 if (numbers[board[line][column] - 1] == 1){
                     return 0;
                 }
                 else{
                     numbers[board[line][column] - 1] = 1;
                 }
             }         
         }
     }

     return 1;
 }

//IsSquareValid checks if the Square is valid
int IsSquareValid(int board[][BOARDSIZE], int line, int column){
    int numbers[BOARDSIZE] = {0};

    for (size_t i = line; (int)i < line + 3; i ++){
        for (size_t j = column; (int)j < column + 3; j ++){
            if (board[i][j] != 0){
                 if (numbers[board[i][j] - 1] == 1){
                     return 0;
                 }
                 else{
                     numbers[board[i][j] - 1] = 1;
                 }
             }        
        }
    }

    return 1;
}

//IsBoardValid checks if the board is valid
int IsBoardValid(int board[][BOARDSIZE]){
    if (!IsColumnValid(board) || !IsLineValid(board))
        return 0;

    for (size_t line = 0; (int)line <= 6; line += 3){
        for (size_t column = 0; (int)column <= 6; column += 3){
            if (!IsSquareValid(board, line, column))
                return 0;
        }
    }

    return 1;
}

//IsSolved checks if the board is solved
int IsSolved(int board[][BOARDSIZE]){
    int solved = 1;
    if (IsBoardValid(board)){
        for (size_t i = 0; (int)i < BOARDSIZE; i ++){
            for (size_t j = 0; (int)j < BOARDSIZE; j ++){
                if (board[i][j] == '0'){
                    solved = 0;
                }
            }
        }
    }
    else{
        solved = 0;
    }

    return solved;
}

int zero(int list[BOARDSIZE]){
    size_t i = 0;
    while (i < BOARDSIZE && list[i] == 0){
        i ++;
    }
    return (i == BOARDSIZE) ? 1 : 0;
}


//Solve solves the board
int Solve(int board[][BOARDSIZE]){
    
    for (size_t i = 0; (int)i < BOARDSIZE; i ++){
        for (size_t j = 0; (int)j < BOARDSIZE; j ++){
            if (board[i][j] == 0){
                int num = 1;
                for (; num <= BOARDSIZE; num ++){
                    board[i][j] = num;
                    if (IsBoardValid(board)){
                        if (Solve(board) == 1){
                            break;
                        }
                        else{
                            continue;
                        }
                    }
                }
 
                if (num == BOARDSIZE + 1){
                    board[i][j] = 0;
                    return 0;
                }
            }
        }
    }

    
    return 1;
}



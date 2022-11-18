#include "solver.h"


//_IsLineValid checks if the lign is valid
int IsLineValid(int board[], size_t line) {
    int numbers[BOARDSIZE] = {0};

    for (size_t column = 0; column < BOARDSIZE; column++) {
        if (board[line * BOARDSIZE + column] != 0) {
            if (numbers[board[line * BOARDSIZE + column] - 1] == 1) {
                return 0;
            }
            else { 
                numbers[board[line * BOARDSIZE + column] - 1] = 1;
            }
        }
    }
    
    return 1;
}

//_IsColumnValid checks if the column is valid
int IsColumnValid(int board[], size_t column) {
    int numbers[BOARDSIZE] = {0};

    for (size_t line = 0; line < BOARDSIZE; line++) {
        if (board[line * BOARDSIZE + column] != 0) {
            if (numbers[board[line * BOARDSIZE + column] - 1] == 1) {
                return 0;
            }
            else {
                numbers[board[line * BOARDSIZE + column] - 1] = 1;
            }
        }         
    }

    return 1;
 }

//IsSquareValid checks if the Square is valid
int IsSquareValid(int board[], size_t line, size_t column) {
    line = line / 3 * 3;
    column = column / 3 * 3;
    int numbers[BOARDSIZE] = {0};

    for (size_t i = line; i < line + 3; i ++) {
        for (size_t j = column; j < column + 3; j ++) {
            if (board[i * BOARDSIZE + j] != 0) {
                 if (numbers[board[i * BOARDSIZE + j] - 1] == 1) {
                     return 0;
                 }
                 else {
                     numbers[board[i * BOARDSIZE + j] - 1] = 1;
                 }
             }        
        }
    }

    return 1;
}

//IsBoardValid checks if the board is valid
int IsBoardValid(int board[]) {
    for (size_t i = 0; i < BOARDSIZE; i++) {
        if (!IsColumnValid(board, i) || !IsLineValid(board, i))
            return 0;
    }

    for (size_t line = 0; line <= 6; line += 3) {
        for (size_t column = 0; column <= 6; column += 3) {
            if (!IsSquareValid(board, line, column))
                return 0;
        }
    }

    return 1;
}

//IsSolved checks if the board is solved
int IsSolved(int board[]) {
    if (IsBoardValid(board)) {
        for (size_t i = 0; i < BOARDSIZE; i++) {
            for (size_t j = 0; j < BOARDSIZE; j++) {
                if (board[i * BOARDSIZE + j] == 0) {
                    return 0;
                }
            }
        }

        return 1;
    }
    
    return 0;
}


//Solve solves the board
int Solve(int board[]) {
    
    for (size_t i = 0; i < BOARDSIZE; i++) {
        for (size_t j = 0; j < BOARDSIZE; j++) {
            if (board[i * BOARDSIZE + j] == 0) {
                int num = 1;
                for (; num <= BOARDSIZE; num++) {
                    board[i * BOARDSIZE + j] = num;
                    if (IsLineValid(board, i) && 
                        IsColumnValid(board, j) && 
                        IsSquareValid(board, i, j) &&
                        Solve(board) == 1)
                            break;
                }
 
                if (num == BOARDSIZE + 1) {
                    board[i * BOARDSIZE + j] = 0;
                    return 0;
                }
            }
        }
    }

    return 1;
}



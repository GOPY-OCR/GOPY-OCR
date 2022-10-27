#include "solver.h"

int board[][BOARDSIZE] =  { {5, 3, 0, 0, 7, 0, 0, 0, 0},
                            {6, 0, 0, 1, 9, 5, 0, 0, 0},
                            {0, 9, 8, 0, 0, 0, 0, 6, 0},
                            {8, 0, 0, 0, 6, 0, 0, 0, 3},
                            {4, 0, 0, 8, 0, 3, 0, 0, 1},
                            {7, 0, 0, 0, 2, 0, 0, 0, 6},
                            {0, 6, 0, 0, 0, 0, 2, 8, 0},
                            {0, 0, 0, 4, 1, 9, 0, 0, 5},
                            {0, 0, 0, 0, 8, 0, 0, 7, 9}
                          };

int solved[][BOARDSIZE] =  { {5, 3, 4, 6, 7, 8, 9, 1, 2},
                             {6, 7, 2, 1, 9, 5, 3, 4, 8},
                             {1, 9, 8, 3, 4, 2, 5, 6, 7},
                             {8, 5, 9, 7, 6, 1, 4, 2, 3},
                             {4, 2, 6, 8, 5, 3, 7, 9, 1},
                             {7, 1, 3, 9, 2, 4, 8, 5, 6},
                             {9, 6, 1, 5, 3, 7, 2, 8, 4},
                             {2, 8, 7, 4, 1, 9, 6, 3, 5},
                             {3, 4, 5, 2, 8, 6, 1, 7, 9}
                          };



Test(board, test_contains) {
    
    int element2search = 2;
    int results[9] = {0, 0, 0, 0, 0, 1, 1, 0, 0};

    for ( size_t i = 0; (int)i < BOARDSIZE; i ++){
        int contains = Contains(board[i], element2search);
        
        if (contains != results[i]){
            if (results[i] == 0){
                cr_assert_fail("Wrong ! The array contains %i\n", element2search);
            }
            else{
                cr_assert_fail("Wrong ! The array doesn't contain %i\n", element2search);
            }
        }
    }
}


Test(board, test_IsLineValid){
    
    int results1 = 1;
    
    int lineValid = IsLineValid(board);
    
    if (lineValid != results1){
            if (results1 == 0){
                 cr_assert_fail("Wrong ! The lines are not valid\n");
            }
            else{
                 cr_assert_fail("Wrong ! The lines are valid\n");
            }
    }
}


Test(board, test_IsColumnValid){

    int results2 = 1;

    int columnValid = IsColumnValid(board);
    
    if (columnValid != results2){
            if (results2 == 0){
                cr_assert_fail("Wrong ! The columns are not valid\n");
            }
            else{
                cr_assert_fail("Wrong ! The columns are valid\n");
            }
    }
    
}

Test(board, test_IsSquareValid){
 
     int results2 = 1;
 
     int squareValid = IsSquareValid(board, 0, 0);
 
     if (squareValid != results2){
             if (results2 == 0){
                 cr_assert_fail("Wrong ! square not valid\n");
             }
             else{
                 cr_assert_fail("Wrong ! square valid\n");
             }
     }
 
 }


Test(board, test_IsBoardValid){
   
    int results3 = 1;
    
    int boardValid = IsBoardValid(board);
 
    if (boardValid != results3){
            if (results3 == 0){
                cr_assert_fail("Wrong ! The board is not valid\n");
            }
            else{
                cr_assert_fail("Wrong ! The board is valid\n");
            }
    }
      
}


Test(board, test_IsSolved){
    
     int results4 = 1;
 
     int isSolved = IsSolved(board);

     if (isSolved != results4){
             if (results4 == 0){
                 cr_assert_fail("Wrong ! The board is not solved\n");
             }
             else{
                 cr_assert_fail("Wrong ! The board is solved\n");
             }
     }
 
}


Test(board, test_Solve){

      Solve(board);

      for (size_t line = 0; (int)line < BOARDSIZE; line ++){
          for (size_t column = 0; (int)column < BOARDSIZE; column ++){
              if (board[line][column] != solved[line][column]){
                  cr_assert_fail("The solution is not the expected one\n");
              }
          }
      }
}

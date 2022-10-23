#include "solver.h"


int BOARDSIZE = 9;

int board[][BOARDSIZE] = { {5, 3, 0, 0, 7, 0, 0, 0, 0},
                            {6, 0, 0, 1, 9, 5, 0, 0, 0},
                            {0, 9, 8, 0, 0, 0, 0, 6, 0},
                            {8, 0, 0, 0, 6, 0, 0, 0, 3},
                            {4, 0, 0, 8, 0, 3, 0, 0, 1},
                            {7, 0, 0, 0, 2, 0, 0, 0, 6},
                            {0, 6, 0, 0, 0, 0, 2, 8, 0},
                            {0, 0, 0, 4, 1, 9, 0, 0, 5},
                            {0, 0, 0, 0, 8, 0, 0, 7, 9}
                          };

int solved[][BOARDSIZE] = { {5, 3, 0, 0, 7, 0, 0, 0, 0},
                             {6, 0, 0, 1, 9, 5, 0, 0, 0},
                             {0, 9, 8, 0, 0, 0, 0, 6, 0},
                             {8, 0, 0, 0, 6, 0, 0, 0, 3},
                             {4, 0, 0, 8, 0, 3, 0, 0, 1},
                             {7, 0, 0, 0, 2, 0, 0, 0, 6},
                             {0, 6, 0, 0, 0, 0, 2, 8, 0},
                             {0, 0, 0, 4, 1, 9, 0, 0, 5},
                             {0, 0, 0, 0, 8, 0, 0, 7, 9}
                          };



Test(board, test_contains) {
    setup();
    
    int element2search = 2;
    int results[9] = {0, 0, 0, 0, 0, 1, 1, 0, 0};

    for ( size_t i = 0; i < BOARDSIZE; i ++){
        if (Contains(board[i][], element2search) != results[i])
            if (results[i] == 0)
                cr_assert_fail("Wrong ! The array contains %i\n", element2search);
            else
                cr_assert_fail("Wrong ! The array doesn't contain %i\n", element2search);
    }
}


Test(board, test_IsLineValid){
    setup();
    
    int results1 = 1;

    if (IsLineValid(board) != results1)
            if (results1 == 0)
                 cr_assert_fail("Wrong ! The lines are not valid\n");
             else
                 cr_assert_fail("Wrong ! The lines are valid\n");

}


Test(board, test_IsColumnValid){
    setup();

    int results2 = 1;

    if (IsColumnValid(board) != results2)
            if (results2 == 0)
                cr_assert_fail("Wrong ! The columns are not valid\n");
            else
                cr_assert_fail("Wrong ! The columns are valid\n");
    
}


Test(board, test_IsBoardValid){
    setup();
   
    int results3 = 1;
 
    if (IsBoardValid(board) != results3)
            if (results3 == 0)
                cr_assert_fail("Wrong ! The board is not valid\n");
            else
                cr_assert_fail("Wrong ! The board is valid\n");
      
}


Test(board, test_IsSolved){
     setup();
    
     int results4 = 1;
 
     if (IsSolved(board) != results4)
             if (results4 == 0)
                 cr_assert_fail("Wrong ! The board is not solved\n");
             else
                 cr_assert_fail("Wrong ! The board is solved\n");
 
}


Test(board, test_Solve){
      setup();

      Solve(board);

      for (size_t line = 0; line < BOARDSIZE; line ++){
          for (size_t column = 0; column < BOARDSIZE; column ++){
              if (board[i][j] != solved[i][j])
                  cr_assert_fail("The solution is not the expected one\n");
          }
      }
}

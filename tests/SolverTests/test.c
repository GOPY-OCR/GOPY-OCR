#include <criterion/criterion.h>
#include "solver.h"
#include "grid.h"

int is_the_same(int *board, char *filename) {
    int *ref = load_grid_file(filename);

    for (size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++)
        if (board[i] != ref[i]) {
            save_grid_file(board, "modified_grid");
            return 0;
        }

    free(ref);

    return 1;
}


Test(IsLineValid, valid_lines) {
    int *board = load_grid_file("valid_lines");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(IsLineValid(board, i));

    cr_assert(is_the_same(board, "valid_lines"));

    free(board);
}

Test(IsLineValid, wrong_lines) {
    int *board = load_grid_file("wrong_lines");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(!IsLineValid(board, i));

    cr_assert(is_the_same(board, "wrong_lines"));

    free(board);
}

Test(IsColumnValid, valid_columns) {
    int *board = load_grid_file("valid_columns");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(IsColumnValid(board, i));

    cr_assert(is_the_same(board, "valid_columns"));

    free(board);
}

Test(IsColumnValid, wrong_columns) {
    int *board = load_grid_file("wrong_columns");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(!IsColumnValid(board, i));

    cr_assert(is_the_same(board, "wrong_columns"));

    free(board);
}

Test(IsSquareValid, valid_square) {
    int *board = load_grid_file("valid_square");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(IsSquareValid(board, i % BOARDSIZE, i / BOARDSIZE));

    cr_assert(is_the_same(board, "valid_square"));

    free(board);
}

Test(IsSquareValid, wrong_square) {
    int *board = load_grid_file("wrong_square");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(!IsSquareValid(board, i % BOARDSIZE, i / BOARDSIZE));

    cr_assert(is_the_same(board, "wrong_square"));

    free(board);
}

Test(IsBoardValid, valid_not_solved_board) {
    int *board = load_grid_file("valid_not_solved_board");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(IsBoardValid(board));

    cr_assert(is_the_same(board, "valid_not_solved_board"));

    free(board);
}

Test(IsBoardValid, valid_solved_board) {
    int *board = load_grid_file("valid_solved_board");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(IsBoardValid(board));

    cr_assert(is_the_same(board, "valid_solved_board"));

    free(board);
}

Test(IsBoardValid, wrong_board) {
    int *board = load_grid_file("wrong_board");

    for (size_t i = 0; i < BOARDSIZE; i++)
        cr_expect(!IsBoardValid(board));

    cr_assert(is_the_same(board, "wrong_board"));

    free(board);
}

Test(IsSolved, solved_board) {
    int *board = load_grid_file("solved_board");

    cr_expect(IsSolved(board));

    cr_assert(is_the_same(board, "solved_board"));

    free(board);
}

Test(IsSolved, not_solved_valid_board) {
    int *board = load_grid_file("not_solved_valid_board");

    cr_expect(!IsSolved(board));

    cr_assert(is_the_same(board, "not_solved_valid_board"));

    free(board);
}

Test(IsSolved, not_solved_not_valid_board) {
    int *board = load_grid_file("not_solved_not_valid_board");

    cr_expect(!IsSolved(board));

    cr_assert(is_the_same(board, "not_solved_not_valid_board"));

    free(board);
}

Test(Solve, solvable) {
    int *board = load_grid_file("solvable");

    cr_expect(Solve(board));

    cr_assert(IsSolved(board));

    free(board);
}

Test(Solve, not_solvable) {
    int *board = load_grid_file("not_solvable");

    cr_expect(!Solve(board));

    cr_assert(is_the_same(board, "not_solvable"));

    free(board);
}

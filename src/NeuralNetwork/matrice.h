#pragma once
#include <stdlib.h>
#include <string.h>
#include <err.h>
#include <stdio.h>

typedef struct matrice {
  int columns;
  int rows;
  double *data;
} matrice;

matrice* matrice_new(int rows, int columns);
matrice* matrice_from_string(char *str);
void matrice_free(matrice *m);
void matrice_print(matrice *m);

double matrice_get(matrice *m, int row, int column);
void matrice_set(matrice *m, int row, int column, double value);

matrice* matrice_dot(matrice *m1, matrice *m2);
matrice* matrice_add(matrice *m1, matrice *m2);
matrice* matrice_transpose(matrice *m);

matrice* matrice_random(int rows, int columns, double min, double max);
matrice* matrice_zeros(int rows, int columns);

int matrice_equals(matrice *m1, matrice *m2);

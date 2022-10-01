#pragma once

typedef struct matrice {
  int columns;
  int rows;
  double **data;
} matrice;

matrice *matrice_new(int rows, int columns);
void matrice_free(matrice *m);
void matrice_print(matrice *m);

matrice matrice_dot(matrice *m1, matrice *m2);
matrice matrice_add(matrice *m1, matrice *m2);
matrice matrice_transpose(matrice *m);

matrice matrice_random(int rows, int columns);
matrice matrice_zeros(int rows, int columns);

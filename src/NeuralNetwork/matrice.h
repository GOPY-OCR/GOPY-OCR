#pragma once
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrice {
    int columns;
    int rows;
    double *data;
} matrice;

matrice *matrice_new(int rows, int columns);
void matrice_free(matrice *m);

void matrice_print(matrice *m);

matrice *matrice_from_string(char *str);

char *matrice_serialize(matrice *m);
matrice *matrice_deserialize(char *str);

matrice *matrice_clone(matrice *m);

double matrice_get(matrice *m, int row, int column);
void matrice_set(matrice *m, int row, int column, double value);

matrice *matrice_random(int rows, int columns, double min, double max);
matrice *matrice_zeros(int rows, int columns);

int matrice_equals(matrice *m1, matrice *m2);

matrice *matrice_dot(matrice *m1, matrice *m2);
matrice *matrice_add(matrice *m1, matrice *m2);
matrice *matrice_transpose(matrice *m);

// inplace operations
void matrice_map(matrice *m, double (*f)(double));
void matrice_multiply(matrice *m, double scalar);

#pragma once
#include "str_utils.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct matrice {
    int rows;
    int columns;
    double *data;
} matrice;

matrice *matrice_new(int rows, int columns);
void matrice_free(matrice *m);

void matrice_print(matrice *m);

matrice *matrice_from_string(char *str);

char *matrice_serialize(matrice *m, char *name);
matrice *matrice_deserialize(char *str);

void matrice_to_csv(matrice *m, char *filename, char *name);
matrice *matrice_read_csv(char *filename);

matrice *matrice_clone(matrice *m);

double matrice_get(matrice *m, int row, int column);
double *matrice_get_ref(matrice *m, int row, int column);
void matrice_set(matrice *m, int row, int column, double value);

matrice *matrice_random(int rows, int columns, double min, double max);
matrice *matrice_zeros(int rows, int columns);

int matrice_equals(matrice *m1, matrice *m2);

matrice *matrice_dot(matrice *m1, matrice *m2);
matrice *matrice_transpose(matrice *m);

// element wise operations
matrice *matrice_elementwise(matrice *m1, matrice *m2,
                             double (*f)(double, double));
matrice *matrice_add(matrice *m1, matrice *m2);
matrice *matrice_sub(matrice *m1, matrice *m2);
matrice *matrice_mul(matrice *m1, matrice *m2);

// inplace operations
matrice *matrice_map(matrice *m, double (*f)(double));
matrice *matrice_multiply(matrice *m, double scalar);

double *matrice_max(matrice *m, int *row, int *column);

double matrice_sum(matrice *m);

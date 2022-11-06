#pragma once
#include "str_utils.h"
#include "matrice_multithread.h"
#include "matrice_type.h"
#include "str_utils.h"
#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <maths.h>


matrice *matrice_new(int rows, int columns);
void matrice_free(matrice *m);

void matrice_print(matrice *m);

matrice *matrice_from_string(char *str);

char *matrice_serialize(matrice *m, char *name);
matrice *matrice_deserialize(char *str);

void matrice_to_csv(matrice *m, char *filename, char *name);
matrice *matrice_read_csv(char *filename);

matrice *matrice_clone(matrice *m);

float matrice_get(matrice *m, int row, int column);
float *matrice_get_ref(matrice *m, int row, int column);
void matrice_set(matrice *m, int row, int column, float value);

matrice *matrice_random(int rows, int columns, float min, float max);
matrice *matrice_zeros(int rows, int columns);

int matrice_equals(matrice *m1, matrice *m2);

matrice *matrice_dot(matrice *m1, matrice *m2);
matrice *matrice_transpose(matrice *m);

// element wise operations
matrice *matrice_elementwise(matrice *m1, matrice *m2,
                             float (*f)(float, float));
matrice *matrice_add(matrice *m1, matrice *m2);
matrice *matrice_sub(matrice *m1, matrice *m2);
matrice *matrice_mul(matrice *m1, matrice *m2);

// inplace operations
matrice *matrice_map(matrice *m, float (*f)(float));
matrice *matrice_multiply(matrice *m, float scalar);

void matrice_add_inplace(matrice *dest, matrice *source);
void matrice_sub_inplace(matrice *dest, matrice *source);

float *matrice_max(matrice *m, int *row, int *column);

float matrice_sum(matrice *m);
float matrice_mean(matrice *m);
// std = standard deviation = écart type = sqrt(variance)
float matrice_std(matrice *m);

#pragma once
#include "matrice.h"

typedef struct {
    matrice *data;
    int size;
} array;

double array_get(array *a, int i);
void array_set(array *a, int i, double value);

array *array_new(int size);
array *array_range(double start, double end, double step);
array *array_zeros(int size);

void array_free(array *a);

array *array_clone(array *a);

// not inplace ! it clones the array before applying the function
array *array_map(array *a, double (*f)(double));

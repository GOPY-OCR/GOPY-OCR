#include "array.h"

array *array_new(int size){
    array *a = malloc(sizeof(array));
    a->data = matrice_new(size, 1);
    a->size = size;
    return a;
}

array *array_range(double start, double end, double step){
    int size = (end - start) / step;
    array *a = array_new(size);
    for(int i = 0; i < size; i++){
        array_set(a, i, start + i * step);
    }
    return a;
}

array *array_zeros(int size){
    array *a = malloc(sizeof(array));
    a->data = matrice_zeros(size, 1);
    a->size = size;
    return a;
}


double array_get(array *a, int i){
    return matrice_get(a->data, i, 0);
}

void array_set(array *a, int i, double value){
    matrice_set(a->data, i, 0, value);
}

array *array_map(array *a, double (*f)(double)){
    array *result = array_clone(a);
    matrice_map(result->data, f);
    return result;
}

array *array_clone(array *a){
    array *clone = malloc(sizeof(array));
    clone->data = matrice_clone(a->data);
    clone->size = a->size;
    return clone;
}

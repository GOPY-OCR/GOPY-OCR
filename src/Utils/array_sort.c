#include "array_sort.h"

int compare_int(const void *a, const void *b){
    int *ia = (int *)a;
    int *ib = (int *)b;

    if (*ia > *ib) 
        return 1;
    else if (*ia < *ib) 
        return -1;
    else
        return 0;
}

void sort_int_array(int *a, int size){
    qsort(a, size, sizeof(int), compare_int);
}

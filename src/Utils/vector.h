#pragma once
#include <stdlib.h>

typedef struct {
    size_t size;
    size_t capacity;
    void** data;
} Vector;

Vector *vector_new(size_t capacity);
void vector_free(Vector *vector);

void* vector_get(Vector *vector, size_t index);
void vector_set(Vector *vector, size_t index, void *value);

void vector_double_capacity_if_full(Vector *vector);

void vector_push(Vector *vector, void *value);

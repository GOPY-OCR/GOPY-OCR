#include "vector.h"


Vector *vector_new(size_t capacity) {
    Vector *vector = malloc(sizeof(Vector));
    vector->capacity = capacity;
    vector->size = 0;
    vector->data = malloc(capacity * sizeof(void *));
    return vector;
}

void vector_free(Vector *vector) {
    free(vector->data);
    free(vector);
}

void* vector_get(Vector *vector, size_t index) {
    return vector->data[index];
}

void vector_set(Vector *vector, size_t index, void *value) {
    vector->data[index] = value;
}

void vector_push(Vector *vector, void *value) {
    vector_double_capacity_if_full(vector);
    vector->data[vector->size++] = value;
}

void vector_double_capacity_if_full(Vector *vector) {
    if (vector->size >= vector->capacity) {
        vector->capacity *= 2;
        vector->data = realloc(vector->data, vector->capacity * sizeof(void *));
    }
}

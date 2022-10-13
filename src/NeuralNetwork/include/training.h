#pragma once
#include "maths.h"
#include "matrice.h"
#include "neural_network.h"
#include <dirent.h>
#include <utils.h>

typedef struct dataset {
    matrice **inputs;
    matrice **targets;
    int size;
} dataset;

void train(NeuralNetwork *nn, int epochs, float learning_rate, int batch_size,
           dataset *training_data, dataset *testing_data);

dataset *load_dataset(const char *path, int size);

char **list_files(const char *path, int n);

void update_mini_batch(NeuralNetwork *nn, dataset *data, float learning_rate,
                       int start, int end);

void backprop(NeuralNetwork *nn, matrice *input, matrice *target,
              matrice **nabla_b, matrice **nabla_w);

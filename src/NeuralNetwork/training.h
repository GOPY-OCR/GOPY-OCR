#pragma once
#include "matrice.h"
#include "neural_network.h"
#include "maths.h"
#include <utils.h>
#include <dirent.h>

typedef struct dataset {
    matrice *inputs;
    matrice *targets;
} dataset;

void train(NeuralNetwork nn, int epochs, float learning_rate,
           dataset training_data, dataset testing_data);

dataset* load_dataset(const char *path, int size);


char** list_files(const char *path, int n);

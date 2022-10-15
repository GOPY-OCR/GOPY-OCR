#pragma once
#include "maths.h"
#include "matrice.h"
#include "neural_network.h"
#include "utils.h"
#include <dirent.h>

typedef struct dataset {
    matrice **inputs;
    matrice **targets;
    int size;
} dataset;

dataset *create_dataset(int size);

void train(NeuralNetwork *nn, 
           int epochs, 
           float learning_rate, 
           int batch_size,
           dataset *training_data, 
           dataset *testing_data, 
           int verbose);

dataset *load_dataset(const char *path, int size);

char **list_files(const char *path, int n);

void update_mini_batch(NeuralNetwork *nn, 
                       dataset *data, 
                       float learning_rate,
                       int start, 
                       int end);

void backprop(NeuralNetwork *nn, 
              matrice *input, 
              matrice *target,
              matrice **nabla_b, 
              matrice **nabla_w);



float evaluate(NeuralNetwork *nn, dataset *data, int verbose);

int max_output(matrice *output);

void shuffle_dataset(dataset *data);


dataset *copy_dataset(dataset *data, int deepcopy);

#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"

typedef struct Layer {
    Matrix *weights;
    Matrix *biases;
} Layer;

typedef struct NeuralNetwork {
    int nb_layers;
    Layer *layers;
} NeuralNetwork;

NeuralNetwork *create_neural_network(int nb_layers, int *nb_neurons);
void free_neural_network(NeuralNetwork *nn);



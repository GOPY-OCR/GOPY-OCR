#pragma once
#include "matrice.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Layer {
  matrice *weights;
  matrice *biases;
} Layer;

typedef struct NeuralNetwork {
  int nb_layers;
  Layer *layers;
} NeuralNetwork;

NeuralNetwork *create_neural_network(int nb_layers, int *nb_neurons);
void free_neural_network(NeuralNetwork *nn);

void save_neural_network(NeuralNetwork *nn, char *filename);
NeuralNetwork *load_neural_network(char *filename);

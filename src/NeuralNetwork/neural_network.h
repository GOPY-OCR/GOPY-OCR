#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "maths.h"
#include "matrice.h"
#include "str_utils.h"
#include "sdl_utils.h"
#include "cost_functions.h"

#ifndef NN_SAVE_FILENAME
    #define NN_SAVE_FILENAME "./ocr_save.nn"
#endif

typedef struct Layer {
    matrice *weights;
    matrice *biases;
} Layer;

typedef struct NeuralNetwork {
    int nb_layers;
    Layer **layers;
    CostFunction cost_function;
} NeuralNetwork;

Layer *create_layer(int nb_neurons, int nb_inputs);
void free_layer(Layer *layer);


/*
 * Creates a neural network, its weights and biases are randomised
 * nb_layers: number of layers in the neural network
 * nb_inputs: number of inputs of the neural network
 * nb_neurons: number of neurons in each layer
 */
NeuralNetwork *create_neural_network(int nb_layers,
                                     int nb_inputs,
                                     int *nb_neurons);

void free_neural_network(NeuralNetwork *nn);


void save_neural_network(NeuralNetwork *nn, char *filename);
// Loads a neural network from a file
// Returns NULL if the file doesn't exist
NeuralNetwork *load_neural_network(char *filename);

int *neural_network(SDL_Surface **splitted);


/*
 * Computes the output of a neural network
 * nn: neural network
 * inputs: inputs of the neural network
 */
matrice *feedforward(NeuralNetwork *nn, matrice *inputs);

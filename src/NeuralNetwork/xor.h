#pragma once
#include "neural_network.h"
#include "training.h"
#include "matrice.h"

// Calls one of the modes below
void xor_main(int verbose, int argc, char **argv);
// Mode 1: Trains, tests and saves the network
void xor_train(int verbose, int argc, char **argv);
// Mode 2: Loads the network and tests it
float test_xor_inputs(NeuralNetwork *network, int verbose, float input1, float input2);
// Mode 3: Loads the network and plot the output
void save_network_plot(NeuralNetwork *network, int verbose);

void train_xor_network(NeuralNetwork *network, int verbose, dataset *data);
int test_xor_network(NeuralNetwork *network, int verbose, dataset *data);

NeuralNetwork *load_xor_network(int verbose);
NeuralNetwork *create_xor_network();
dataset *create_xor_dataset();
matrice *expected_xor_output(matrice *input);

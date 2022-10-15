#pragma once
#include "neural_network.h"
#include "training.h"
#include "matrice.h"

NeuralNetwork *create_xor_network();

void train_xor_network(NeuralNetwork *network, int verbose);
int test_xor_network(NeuralNetwork *network);

dataset *create_xor_dataset();

matrice *expected_xor_output(matrice *input);

void xor_main();

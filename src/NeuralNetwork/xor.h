#pragma once
#include "neural_network.h"
#include "training.h"

NeuralNetwork *create_xor_network();

void train_xor_network(NeuralNetwork *network);
int test_xor_network(NeuralNetwork *network);

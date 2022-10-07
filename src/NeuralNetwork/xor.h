#pragma once
#include "neural_network.h"

NeuralNetwork* create_xor_network();

void train_xor_network(NeuralNetwork *network);
void test_xor_network(NeuralNetwork *network);

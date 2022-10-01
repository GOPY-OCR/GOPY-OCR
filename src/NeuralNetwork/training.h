#pragma once
#include "neural_network.h"

void train(NeuralNetwork nn, int epochs, float learning_rate,
           Dataset training_data, Dataset testing_data);

struct Dataset {
  Matrix inputs;
  Matrix targets;
};

Dataset load_dataset(const char *path);

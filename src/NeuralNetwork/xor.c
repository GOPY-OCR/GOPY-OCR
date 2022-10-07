#include "xor.h"

NeuralNetwork create_xor_network() {
    int layers[3] = {2, 2, 1};
    NeuralNetwork network = create_network(2, layers);
}

void train_xor_network(NeuralNetwork &network);
void test_xor_network(NeuralNetwork &network);

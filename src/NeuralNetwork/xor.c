#include "xor.h"

NeuralNetwork* create_xor_network() {
    int layers[2] = {2, 1};
    NeuralNetwork *network = create_neural_network(2, 2, layers);

    return network;
}

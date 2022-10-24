#include "xor.h"


#define XOR_EPOCHS 2000
#define XOR_LEARNING_RATE 5

void xor_main(int verbose) {
    dataset *data = create_xor_dataset();
    NeuralNetwork *network = create_xor_network();

    train_xor_network(network, verbose, data);

    if (!test_xor_network(network, 0, data)) {
        errx(1, "XOR network failed to learn\n");
    }

    free_neural_network(network);
}

NeuralNetwork *create_xor_network() {
    int layers[2] = {3, 1};
    NeuralNetwork *network = create_neural_network(2, 2, layers);

    return network;
}

void train_xor_network(NeuralNetwork *network, int verbose, dataset *data) {
    train(network, XOR_EPOCHS, XOR_LEARNING_RATE, 4, data, data, verbose);
}

#define MIN_ACCURACY 0.9
int test_xor_network(NeuralNetwork *network, int verbose, dataset *data) {
    //data = create_xor_dataset();
    float accuracy = evaluate(network, data, verbose);

    return accuracy >= MIN_ACCURACY;
}

dataset *create_xor_dataset(){
    dataset *data = create_dataset(4);
    data->inputs[0] = matrice_from_string("0,"
                                          "0");

    data->inputs[1] = matrice_from_string("0,"
                                          "1");

    data->inputs[2] = matrice_from_string("1,"
                                          "0");

    data->inputs[3] = matrice_from_string("1,"
                                          "1");

    for (int i = 0; i < 4; i++) {
        data->targets[i] = expected_xor_output(data->inputs[i]);
    }

    return data;
}

matrice *expected_xor_output(matrice *input) {
    matrice *output = matrice_zeros(1, 1);

    if (matrice_get(input, 0, 0) == matrice_get(input, 1, 0)) {
        matrice_set(output, 0, 0, 0);
    } else {
        matrice_set(output, 0, 0, 1);
    }

    return output;
}



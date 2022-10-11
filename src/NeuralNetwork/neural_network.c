#include "neural_network.h"

Layer *create_layer(int nb_neurons, int nb_inputs) {
    Layer *layer = malloc(sizeof(Layer));
    layer->weights = matrice_random(nb_neurons, nb_inputs, -1, 1);
    layer->biases = matrice_random(nb_neurons, 1, -1, 1);
    return layer;
}

void free_layer(Layer *layer) {
    matrice_free(layer->weights);
    matrice_free(layer->biases);
    free(layer);
}

/*
 * Creates a neural network, its weights and biases are randomised
 * nb_layers: number of layers in the neural network
 * nb_inputs: number of inputs of the neural network
 * nb_neurons: number of neurons in each layer
 */
NeuralNetwork *create_neural_network(int nb_layers, int nb_inputs,
                                     int *nb_neurons) {
    NeuralNetwork *neural_network = malloc(sizeof(NeuralNetwork));
    neural_network->nb_layers = nb_layers;
    neural_network->layers = malloc(sizeof(Layer *) * nb_layers);

    neural_network->layers[0] = create_layer(nb_neurons[0], nb_inputs);

    for (int i = 1; i < nb_layers; i++) {
        neural_network->layers[i] =
            create_layer(nb_neurons[i], nb_neurons[i - 1]);
    }

    return neural_network;
}

void free_neural_network(NeuralNetwork *nn) {
    for (int i = 0; i < nn->nb_layers; i++) {
        free_layer(nn->layers[i]);
    }
    free(nn->layers);
    free(nn);
}

void save_neural_network(NeuralNetwork *nn, char *filename) {
    //! TODO
}

NeuralNetwork *load_neural_network(char *filename) {
    //! TODO
    return NULL;
}

/*
 * Computes the output of a neural network
 * nn: neural network
 * inputs: inputs of the neural network
 */
matrice *feed_forward(NeuralNetwork *nn, matrice *inputs) {
    matrice *output = inputs;

    for (int i = 0; i < nn->nb_layers; i++) {
        output = matrice_add(
            matrice_dot(nn->layers[i]->weights, output),
            nn->layers[i]->biases);   // output = weights * output + biases
        matrice_map(output, sigmoid); // output = sigmoid(output)
    }

    return output;
}

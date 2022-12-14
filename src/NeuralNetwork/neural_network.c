#include "neural_network.h"

Layer *create_layer(int nb_neurons, int nb_inputs) {
    Layer *layer = malloc(sizeof(Layer));
    layer->weights = matrice_random(nb_neurons, nb_inputs, -1, 1);
    layer->biases = matrice_random(nb_neurons, 1, -1, 1);

    // improved weights initialization:
    // http://neuralnetworksanddeeplearning.com/chap3.html#weight_initialization
    matrice_multiply(layer->weights, 1 / sqrt(nb_inputs));

    return layer;
}

void free_layer(Layer *layer) {
    matrice_free(layer->weights);
    matrice_free(layer->biases);
    free(layer);
}

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

    // initialize default cost function
    neural_network->cost_function = mse_cost;

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
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        errx(1, "save_neural_network: Could not open file %s\n", filename);
    }

    fprintf(f, "%i\n", nn->nb_layers);
    fprintf(f, "%i\n", nn->cost_function.id);

    for (int i = 0; i < nn->nb_layers; i++){
        char *serialized_weights = matrice_serialize(nn->layers[i]->weights, NULL);
        fprintf(f, "# Weights of layers[%i] :\n{\n%s}\n", i, serialized_weights);

        char *serialized_biases = matrice_serialize(nn->layers[i]->biases, NULL);
        fprintf(f, "# Biases of layers[%i] :\n{\n%s}\n", i, serialized_biases);

        free(serialized_weights);
        free(serialized_biases);
    }

    fclose(f);
}

NeuralNetwork *load_neural_network(char *filename) {
    char *content = read_from_file(filename);

    int nb_layers;
    int cost_function_id;
    sscanf(content, "%i\n%i\n", &nb_layers, &cost_function_id);

    NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));

    Layer **layers = malloc(sizeof(Layer *) * nb_layers);

    char *ptr;
    char *end = content;
    for (int i = 0; i < nb_layers; i++) {
        // find next {} block
	ptr = strstr(end, "{") + 2;

        // Deserialize weights
	layers[i] = malloc(sizeof(Layer));
	layers[i]->weights = matrice_deserialize(ptr, &end);

        // Deserialize biases
        ptr = strstr(end, "{") + 2;
	layers[i]->biases = matrice_deserialize(ptr, &end);
    }

    nn->nb_layers = nb_layers;
    nn->cost_function = COST_FUNCTIONS[cost_function_id];
    nn->layers = layers;

    free(content);
    
    return nn;
}

matrice *feedforward(NeuralNetwork *nn, matrice *inputs) {
    matrice *output = inputs;
    matrice *old_output;
    for (int i = 0; i < nn->nb_layers; i++) {
        old_output = output;
        matrice *dot = matrice_dot(nn->layers[i]->weights, output);
        output = matrice_add(dot, nn->layers[i]->biases);   // output = weights * output + biases
        matrice_map(output, sigmoid); // output = sigmoid(output)

        matrice_free(dot);
        if (i > 0) {
            matrice_free(old_output);
        }
    }

    //matrice_free(old_output);

    return output;
}

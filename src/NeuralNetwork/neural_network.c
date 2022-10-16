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
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        errx(1, "save_neural_network: Could not open file %s\n", filename);
    }

    fprintf(f, "%i\n", nn->nb_layers);

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
    sscanf(content, "%i", &nb_layers);

    NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));
    nn->nb_layers = nb_layers;
    nn->layers = malloc(sizeof(Layer *) * nb_layers);

    char *ptr = content;
    for (int i = 0; i < nb_layers; i++) {
	ptr = strstr(ptr, "{") + 2;
	char *end = strstr(ptr, "}") - 1;
	int size = end - ptr;
	char *weights = malloc(sizeof(char) * size);
	strncpy(weights, ptr, size);
	weights[size - 1] = '\0';
	printf("weights = %s\n", weights);
	nn->layers[i] = malloc(sizeof(Layer));
	nn->layers[i]->weights = matrice_deserialize(weights);
	free(weights);

	ptr = strstr(end, "{") + 2;
	end = strstr(ptr, "}") - 1;
	size = end - ptr;
	char *biases = malloc(sizeof(char) * size);
	strncpy(biases, ptr, size);
	biases[size - 1] = '\0';
	printf("biases = %s\n", biases);
	nn->layers[i]->biases = matrice_deserialize(biases);
	free(biases);
	ptr = end;
    }
    
    return nn;
}

matrice *feedforward(NeuralNetwork *nn, matrice *inputs) {
    matrice *output = inputs;

    for (int i = 0; i < nn->nb_layers; i++) {
        output = matrice_add(
            matrice_dot(nn->layers[i]->weights, output),
            nn->layers[i]->biases);   // output = weights * output + biases
        matrice_map(output, sigmoid); // output = sigmoid(output)
    }

    return output;
}

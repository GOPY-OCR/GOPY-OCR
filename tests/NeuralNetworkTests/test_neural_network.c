#include <criterion/parameterized.h>
#include "neural_network.h"
#include "cost_functions.h"

struct neural_network_create_params {
    int nb_layers;
    int input_size;
    int *nb_neurons;
    CostFunction cost_function;
};

ParameterizedTestParameters(neuralnetworks, test_save_load_neural_network) {
    const size_t nb_params = 4;
    struct neural_network_create_params *params = cr_malloc(sizeof(struct neural_network_create_params) * nb_params);

    int nb_layers = 1;
    int input_size = 1;
    int *nb_neurons = cr_malloc(sizeof(int) * nb_layers);
    nb_neurons[0] = 1;
    params[0] = (struct neural_network_create_params) { nb_layers, input_size, nb_neurons, mse_cost };

    nb_layers = 2;
    input_size = 10;
    nb_neurons = cr_malloc(sizeof(int) * nb_layers);
    nb_neurons[0] = 2;
    nb_neurons[1] = 2;
    params[1] = (struct neural_network_create_params) { nb_layers, input_size, nb_neurons, cross_entropy_cost };

    nb_layers = 5;
    input_size = 100;
    nb_neurons = cr_malloc(sizeof(int) * nb_layers);
    nb_neurons[0] = 50;
    nb_neurons[1] = 31;
    nb_neurons[2] = 27;
    nb_neurons[3] = 8;
    nb_neurons[4] = 1;
    params[2] = (struct neural_network_create_params) { nb_layers, input_size, nb_neurons, mse_cost };

    nb_layers = 3;
    input_size = 40;
    nb_neurons = cr_malloc(sizeof(int) * nb_layers);
    nb_neurons[0] = input_size;
    nb_neurons[1] = input_size / 2;
    nb_neurons[2] = 10;
    params[3] = (struct neural_network_create_params) { nb_layers, input_size, nb_neurons, cross_entropy_cost };

    return cr_make_param_array(struct neural_network_create_params, params, nb_params);
}

#define EPSILON 0.0000001
ParameterizedTest(struct neural_network_create_params *params, neuralnetworks, test_save_load_neural_network){
    NeuralNetwork *nn = create_neural_network(params->nb_layers, params->input_size, params->nb_neurons);

    nn->cost_function = params->cost_function;
    
    char *filename = malloc(200);
    sprintf(filename, "../_build/tests/NeuralNetworkTests/TEMP_test_neural_network_%i.nn", nn->nb_layers);

    save_neural_network(nn, filename);
    NeuralNetwork *nn2 = load_neural_network(filename);

    cr_assert(nn->nb_layers == nn2->nb_layers);

    for(int i = 0; i < nn->nb_layers; i++){
        // we check that the mean difference is less than a small value
        // instead of checking matrice_equals because of rounding errors
        // when saving and loading
        matrice *weights_diff = matrice_sub(nn->layers[i]->weights, nn2->layers[i]->weights);
        matrice_map(weights_diff, doubleabs);
        double mean_diff = matrice_sum(weights_diff) / (weights_diff->rows * weights_diff->columns);
        cr_assert(mean_diff < EPSILON, "loaded neural network weights are not the same as saved neural network weights\n"
                                       "mean difference: %.20f (should be less than %.20f)\n", mean_diff, EPSILON);

        matrice *biases_diff = matrice_sub(nn->layers[i]->biases, nn2->layers[i]->biases);
        matrice_map(biases_diff, doubleabs);
        mean_diff = matrice_sum(biases_diff) / (biases_diff->rows * biases_diff->columns);
        cr_assert(mean_diff < EPSILON, "loaded neural network biases are not the same as saved neural network biases\n"
                                       "mean difference: %.20f (should be less than %.20f)\n", mean_diff, EPSILON);
    }

    cr_assert(nn->cost_function.id == nn2->cost_function.id,
              "loaded neural network cost function is not the same as saved neural network cost function\n"
              "loaded cost function id: %i, saved cost function id: %i\n", nn2->cost_function.id, nn->cost_function.id);

    free_neural_network(nn);
}

double max_value(matrice *m){
    int i, j;
    matrice_max(m, &i, &j);
    return matrice_get(m, i, j);
}

double min_value(matrice *m){
    int i, j;
    matrice_max(matrice_multiply(m,-1), &i, &j);
    return -matrice_get(m, i, j);
}

Test(neuralnetworks, test_create_neural_network_easy) {
    NeuralNetwork *nn = create_neural_network(2, 2, (int []) {2, 2});
    cr_assert(nn->nb_layers == 2, "nb_layers is not correct");
    cr_assert(nn->layers[0]->weights->rows == 2, "weights dimensions are not correct");
    cr_assert(nn->layers[0]->weights->columns == 2, "nb_inputs is not correct");
    cr_assert(nn->layers[1]->weights->rows == 2, "weights dimensions are not correct");
    cr_assert(nn->layers[1]->weights->columns == 2, "weights dimensions are not correct");
    cr_assert(nn->layers[0]->biases->rows == 2, "biases dimensions are not correct");
    cr_assert(nn->layers[0]->biases->columns == 1, "biases dimensions are not correct");
    cr_assert(nn->layers[1]->biases->rows == 2, "biases dimensions are not correct");
    cr_assert(nn->layers[1]->biases->columns == 1, "biases dimensions are not correct");



    for (int i = 0; i < nn->nb_layers; i++) {
        double max_weight = max_value(nn->layers[i]->weights);
        double min_weight = min_value(nn->layers[i]->weights);
        cr_assert(max_weight <= 1, "max weight is greater than 1");
        cr_assert(min_weight >= -1, "min weight is less than -1");

        double max_bias = max_value(nn->layers[i]->biases);
        double min_bias = min_value(nn->layers[i]->biases);
        cr_assert(max_bias <= 1, "max bias is greater than 1");
        cr_assert(min_bias >= -1, "min bias is less than -1");
    }
}

Test(neuralnetowks, test_create_neural_network_hard) {
    NeuralNetwork *nn = create_neural_network(5, 100, (int []) {11, 10, 10, 10, 10});

    cr_assert(nn->nb_layers == 5, "nb_layers is not correct");
    cr_assert(nn->layers[0]->weights->columns == 100, "nb_inputs is not correct");
    cr_assert(nn->layers[0]->weights->rows == 11, "weights dimensions are not correct");
    cr_assert(nn->layers[1]->weights->columns == 11, "weights dimensions are not correct");
    cr_assert(nn->layers[1]->weights->rows == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[2]->weights->columns == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[2]->weights->rows == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[3]->weights->columns == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[3]->weights->rows == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[4]->weights->columns == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[4]->weights->rows == 10, "weights dimensions are not correct");
    cr_assert(nn->layers[0]->biases->rows == 11, "biases dimensions are not correct");
    cr_assert(nn->layers[0]->biases->columns == 1, "biases dimensions are not correct");
    // ... this should be enough

    for (int i = 0; i < nn->nb_layers; i++) {
        double max_weight = max_value(nn->layers[i]->weights);
        double min_weight = min_value(nn->layers[i]->weights);
        cr_assert(max_weight <= 1, "max weight is greater than 1");
        cr_assert(min_weight >= -1, "min weight is less than -1");

        double max_bias = max_value(nn->layers[i]->biases);
        double min_bias = min_value(nn->layers[i]->biases);
        cr_assert(max_bias <= 1, "max bias is greater than 1");
        cr_assert(min_bias >= -1, "min bias is less than -1");
    }
}

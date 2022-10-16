#include <criterion/parameterized.h>
#include "neural_network.h"

ParameterizedTestParameters(neuralnetworks, test_save_load_neural_network) {
    size_t nb_params = 3;
    NeuralNetwork **neural_networks = malloc(sizeof(NeuralNetwork *) * nb_params);
    neural_networks[0] = create_neural_network(1, 1, (int []) {1});
    neural_networks[1] = create_neural_network(2, 2, (int []) {2, 2});
    neural_networks[2] = create_neural_network(5, 100, (int []) {11, 10, 10, 10, 10});

    return cr_make_param_array(NeuralNetwork, neural_networks, nb_params);
}

ParameterizedTest(NeuralNetwork *nn, neuralnetworks, test_save_load_neural_network){
  char *filename = malloc(200);
  sprintf(filename, "../_build/tests/TEMP_test_neural_network_%i.nn", nn->nb_layers);
  printf("Saving to %s\n", filename);

  save_neural_network(nn, filename);
  NeuralNetwork *nn2 = load_neural_network(filename);

  for(int i = 0; i < nn->nb_layers; i++){
      // we check that the mean difference is less than a small value
      // instead of checking matrice_equals because of rounding errors
      // when saving and loading
      matrice *weights_diff = matrice_sub(nn->layers[i]->weights, nn2->layers[i]->weights);
      matrice_map(weights_diff, doubleabs);
      double mean_diff = matrice_sum(weights_diff) / (weights_diff->rows * weights_diff->columns);
      cr_assert(mean_diff < 0.01, "matrices are not equal");

      matrice *biases_diff = matrice_sub(nn->layers[i]->biases, nn2->layers[i]->biases);
      matrice_map(biases_diff, doubleabs);
      mean_diff = matrice_sum(biases_diff) / (biases_diff->rows * biases_diff->columns);
      cr_assert(mean_diff < 0.01, "matrices are not equal");
  }
}

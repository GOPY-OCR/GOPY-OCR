#include "training.h"
#include "xor.h"

// Test(training, test_load_dataset){
//     int nb_data = 15;
//     dataset *data = load_dataset("../src/NeuralNetwork/data/training/",
//     nb_data);
//
//     cr_assert(data != NULL);
//     cr_assert(data->inputs->rows == INPUT_SIZE);
//     cr_assert(data->inputs->cols == 10 * nb_data);
//     cr_assert(data->outputs->rows == 11);
// }

Test(training, test_xor_training) {
    NeuralNetwork *network = create_xor_network();

    cr_assert(network != NULL);

    train_xor_network(network);
}

Test(training, test_max_output) {
    matrice *outputs = matrice_from_string("0.1,"
                                           "0.2,"
                                           "0.3,"
                                           "0.4,"
                                           "0.5,"
                                           "0.6,"
                                           "0.7,"
                                           "0.8,"
                                           "0.9");
    cr_assert(max_output(outputs) == 8);

    matrice_set(outputs, 4, 0, 1);
    cr_assert(max_output(outputs) == 4);
}

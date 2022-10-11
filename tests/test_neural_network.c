#include "../src/NeuralNetwork/training.h"
#include "../src/NeuralNetwork/xor.h"

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

Test(training, test_xor_network) {
    NeuralNetwork *network = create_xor_network();
    cr_assert(network != NULL);
    train_xor_network(network);
    //    cr_assert(test_xor_network(network) == 1);
}

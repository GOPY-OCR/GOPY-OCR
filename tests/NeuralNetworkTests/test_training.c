#include "training.h"
#include "xor.h"
#include "dataset.h"

Test(training, test_xor_training) {
    NeuralNetwork *network = create_xor_network();
    dataset *data = create_xor_dataset();

    cr_assert(network != NULL);

    train_xor_network(network, 0, data);

    int test = test_xor_network(network, 0, data);

    if (!test) {
        printf("Training failed, results:\n");
        evaluate(network, data, 1);
    }

    cr_assert(test, "Failed to train XOR network");
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

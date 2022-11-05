#include "xor.h"


#define XOR_EPOCHS 1000
#define XOR_LEARNING_RATE 80.0
#define SAVE_FILENAME "_build/xor_network.nn"
#define XOR_SHAPE (int[]){2, 1}
void display_help() {
    printf("Usage: ./main -x [-v/-vv/-vvv] [mode]\n"
           "Available modes:\n"
           "  train [EPOCHS=%i] [LEARNING_RATE=%f]: Train the network and saves it to a file.\n"
           "  test X Y: Load and test the network with the given inputs.\n"
           "  plot: output a csv file containing the network's output for each possible input.\n",
           XOR_EPOCHS, XOR_LEARNING_RATE);
}


void xor_main(int verbose, int argc, char **argv){
    if (argc == 0) {
        display_help();
        return;
    }

    if (strcmp(argv[0], "train") == 0) {
        xor_train(verbose, argc - 1, argv + 1);
    } else if (strcmp(argv[0], "test") == 0) {
        if (argc < 3) {
            printf("Error: not enough arguments for test mode.\n");
            display_help();
            return;
        }
        NeuralNetwork *network = load_xor_network(verbose);

        double output = test_xor_inputs(network, verbose, strtod(argv[1], NULL), strtod(argv[2], NULL));
        printf("XOR Neural Network Output: %f\n", output);

    } else if (strcmp(argv[0], "plot") == 0) {
        NeuralNetwork *network = load_xor_network(verbose);

        save_network_plot(network, verbose);
    } else {
        printf("Error: unknown mode '%s'.\n", argv[0]);
        display_help();
    }
}

// Main mode 1
void xor_train(int verbose, int argc, char **argv) {
    dataset *data = create_xor_dataset();
    NeuralNetwork *network = create_xor_network();

    int epochs = XOR_EPOCHS;
    double learning_rate = XOR_LEARNING_RATE;

    if (argc > 0) {
        epochs = strtol(argv[0], NULL, 10);
    }
    if (argc > 1) {
        learning_rate = strtod(argv[1], NULL);
    }

    train(network, epochs, learning_rate, 4, data, data, verbose, 1, 0, 0);

    if (!test_xor_network(network, 0, data)) {
        errx(1, "XOR network failed to learn\n");
    }

    if (verbose){
        printf("Saving XOR network to %s\n", SAVE_FILENAME);
    }

    save_neural_network(network, SAVE_FILENAME);

    free_neural_network(network);
    free_dataset(data);
}

// Main mode 2
double test_xor_inputs(NeuralNetwork *network, int verbose, double input1, double input2) {
    matrice *input = matrice_new(2, 1);
    matrice_set(input, 0, 0, input1);
    matrice_set(input, 1, 0, input2);

    matrice *output = feedforward(network, input);

    double result = matrice_get(output, 0, 0);

    matrice_free(input);
    matrice_free(output);

    return result;
}

// Main mode 3
#define PLOT_SIZE 1000
#define PLOT_FILENAME "_build/xor_plot.csv"
#define PLOT_SCALE 0.5
void save_network_plot(NeuralNetwork *network, int verbose) {
    matrice *plot = matrice_new(PLOT_SIZE * PLOT_SIZE, 3);
    
    if (verbose){
        printf("Computing plot of size %i x %i...\n", PLOT_SIZE, PLOT_SIZE);
    }

    for (int i = 0; i < PLOT_SIZE; i++) {
        for (int j = 0; j < PLOT_SIZE; j++) {
            double input1 = (double) i / PLOT_SIZE / PLOT_SCALE - 0.5 / PLOT_SCALE + 0.5;
            double input2 = (double) j / PLOT_SIZE / PLOT_SCALE - 0.5 / PLOT_SCALE + 0.5;

            double output = test_xor_inputs(network, 0, input1, input2);
            matrice_set(plot, i * PLOT_SIZE + j, 0, input1);
            matrice_set(plot, i * PLOT_SIZE + j, 1, input2);
            matrice_set(plot, i * PLOT_SIZE + j, 2, output);
        }
    }

    if (verbose) {
        printf("Saving plot to %s\n", PLOT_FILENAME);
    }

    matrice_to_csv(plot, PLOT_FILENAME, "X;Y;XOR");
}

void train_xor_network(NeuralNetwork *network, int verbose, dataset *data) {
    train(network, XOR_EPOCHS, XOR_LEARNING_RATE, 4, data, data, verbose, 0, 0, 0);
}

#define MIN_ACCURACY 0.9
int test_xor_network(NeuralNetwork *network, int verbose, dataset *data) {
    float accuracy = evaluate(network, data, verbose);

    return accuracy >= MIN_ACCURACY;
}

NeuralNetwork *load_xor_network(int verbose){
    if (verbose){
        printf("Loading XOR network from %s\n", SAVE_FILENAME);
    }

    NeuralNetwork *network = load_neural_network(SAVE_FILENAME);

    if (verbose) {

        printf("Evaluating Loaded XOR Network...\n");

    }
    dataset *data = create_xor_dataset();

    if (!test_xor_network(network, verbose, data)) {
        errx(1, "Loaded neural network is not correct\n");
    }

    free_dataset(data);

    return network;
}

NeuralNetwork *create_xor_network() {
    NeuralNetwork *network = create_neural_network(sizeof(XOR_SHAPE) / sizeof(int), 2, XOR_SHAPE);
    return network;
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

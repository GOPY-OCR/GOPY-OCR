#include "training.h"
// see http://neuralnetworksanddeeplearning.com/chap2.html

// trains the neural network with the given training data
//
// neural_network: the neural network to train
// epochs: the number of epochs to train the neural network
// training_data: the training dataset to train the neural network with
// testing_data: (optional) used to evaluate the neural network after each epoch
void train(NeuralNetwork *nn, int epochs, float learning_rate, int batch_size,
           dataset *training_data, dataset *testing_data) {

    int verbose = testing_data != NULL;
    int training_nb = training_data->size;

    for (int e = 0; e < epochs; e++) {
        shuffle_dataset(training_data);
        for (int i = 0; i < training_nb - batch_size; i += batch_size) {
            update_mini_batch(nn, training_data,
                              learning_rate / (float)batch_size, i,
                              i + batch_size);
        }
        if (verbose) {
            // TODO: evaluate the neural network, and print the results
            int correct = evaluate(nn, testing_data);
            int total = testing_data->size;
            float accuracy = (float)correct / (float)total * 100.0;
            printf("Epoch %d: %d / %d correct (%.2f%%)\n", e, correct, total,
                   accuracy);
        }
    }
}

void update_mini_batch(NeuralNetwork *nn, dataset *data, float learning_rate,
                       int start, int end) {
    matrice **nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **nabla_w = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **delta_nabla_b;
    matrice **delta_nabla_w;
    for (int i = 0; i < nn->nb_layers; i++) {
        Layer *layer = nn->layers[i];
        nabla_b[i] = matrice_zeros(layer->biases->rows, layer->biases->columns);
        nabla_w[i] =
            matrice_zeros(layer->weights->rows, layer->weights->columns);
    }

    for (int i = start; i < end; i++) {
        matrice *input = data->inputs[i];
        matrice *target = data->targets[i];
        backprop(nn, input, target, delta_nabla_b, delta_nabla_w);

        for (int j = 0; j < nn->nb_layers; j++) {
            nabla_b[i] = matrice_add(nabla_b[i], delta_nabla_b[i]);
            nabla_w[i] = matrice_add(nabla_w[i], delta_nabla_w[i]);
        }
    }

    // update NeuralNetwork weights
    for (int i = 0; i < nn->nb_layers; i++) {
        nn->layers[i]->weights =
            matrice_sub(nn->layers[i]->weights,
                        matrice_multiply(nabla_w[i], (double)learning_rate));
        nn->layers[i]->biases =
            matrice_sub(nn->layers[i]->biases,
                        matrice_multiply(nabla_b[i], (double)learning_rate));
    }
}

// Returns nabla_b, nabla_w representing the
// gradient for the cost function.  nabla_b and
// nabla_w are arrays of matrices, similar
// to NeuralNetwork->biases and NeuralNetwork->weights.
void backprop(NeuralNetwork *nn, matrice *input, matrice *target,
              matrice **nabla_b, matrice **nabla_w) {
    nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    nabla_w = malloc(nn->nb_layers * sizeof(matrice *));

    // feedforward
    matrice *output = input;
    matrice **activations = malloc((nn->nb_layers + 1) * sizeof(matrice *));
    activations[0] = input; // list to store all the activations, layer by layer
    matrice **zs = malloc(
        nn->nb_layers *
        sizeof(matrice *)); // list to store all the z vectors, layer by layer
    for (int i = 0; i < nn->nb_layers; i++) {
        output = matrice_add(matrice_dot(nn->layers[i]->weights, output),
                             nn->layers[i]->biases);
        zs[i] = matrice_clone(output);
        matrice_map(output, sigmoid);
        activations[i + 1] = matrice_clone(output);
    }

    // backpropagation
    // delta = cost_derivative(activations, target) * sigmoid_prime(zs[-1])
    // delta = (ouput - target) * map(zs[nn->nb_layers - 1], sigmoid_prime);
    matrice *sig = matrice_clone(zs[nn->nb_layers - 1]);
    matrice_map(sig, sigmoid_prime);
    matrice *delta = matrice_mul(matrice_sub(output, target), sig);

    nabla_b[nn->nb_layers - 1] = matrice_clone(delta);
    nabla_w[nn->nb_layers - 1] =
        matrice_dot(delta, matrice_transpose(activations[nn->nb_layers - 1]));

    for (int i = nn->nb_layers - 2; i >= 0; i--) {
        sig = matrice_clone(zs[i]);
        matrice_map(sig, sigmoid_prime);
        delta = matrice_mul(
            matrice_dot(matrice_transpose(nn->layers[i + 1]->weights), delta),
            sig);
        nabla_b[i] = matrice_clone(delta);
        nabla_w[i] = matrice_dot(delta, matrice_transpose(activations[i]));
    }
}

// Returns the number of test inputs for which the neural
// network outputs the correct result.
int evaluate(NeuralNetwork *nn, dataset *data) {
    // TODO
    return 0;
}

#define INPUT_SIZE 784
// loads a dataset from a given path
// dataset is a folder containing 10 folders, one for each digit
//
// path: path to the dataset, e.g. "data/training/"
// size: number of images per class
// returns: a dataset
dataset *load_dataset(const char *path, int size) {
    dataset *data = malloc(sizeof(dataset));
    data->inputs = matrice_new(size * 10, INPUT_SIZE);
    data->targets = matrice_new(size * 10, 10);

    int pathle = strlen(path);
    for (int i = 0; i < 10; i++) {
        char *folder = malloc(pathle + 2);
        strcpy(folder, path);
        // last folder character is the digit e.g. "data/training/0"
        folder[pathle] = i + '0';
        folder[pathle + 1] = '\0';

        char **images_paths = list_files(folder, size);

        for (int j = 0; j < size; j++) {
            SDL_Surface *image = load_image(images_paths[j]);

            // !TODO: convert image to input vector
            // !TODO: set target vector
        }
    }

    return data;
}

// converts a list of images to a list of inputs
// images: list of images
// size: number of images

// list files and sub-directories in a directory
//
// path: path to directory
// n: maximum number of files to list
// returns: list of files in directory
char **list_files(const char *path, int n) {
    DIR *dir;
    struct dirent *ent;
    char **files = malloc(n * sizeof(char *));
    int i = 0;

    if ((dir = opendir(path)) != NULL) {
        while ((ent = readdir(dir)) != NULL && i < n) {
            if (ent->d_type == DT_REG) {
                files[i] = malloc(strlen(ent->d_name) + 1);
                strcpy(files[i], ent->d_name);
                i++;
            }
        }
        closedir(dir);
    } else {
        perror("Could not open directory");
    }

    return files;
}

void shuffle_dataset(dataset *data) {
    for (int i = 0; i < data->size; i++) {
        int j = rand() % data->size;
        matrice *tmp = data->inputs[i];
        data->inputs[i] = data->inputs[j];
        data->inputs[j] = tmp;
        tmp = data->targets[i];
        data->targets[i] = data->targets[j];
        data->targets[j] = tmp;
    }
}
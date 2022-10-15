#include "training.h"
// see http://neuralnetworksanddeeplearning.com/chap2.html

// trains the neural network with the given training data
//
// neural_network: the neural network to train
// epochs: the number of epochs to train the neural network
// training_data: the training dataset to train the neural network with
// testing_data: (optional) used to evaluate the neural network after each epoch
// verbose_level: 0 = no output, 1 = per epoch summary, 2 = per testing data summary every epoch
void train(NeuralNetwork *nn, 
           int epochs, 
           float learning_rate, 
           int batch_size,
           dataset *training_data, 
           dataset *testing_data,
           int verbose) {

    int training_nb = training_data->size;

    if(verbose > 0)
        printf( "----- TRAINING SUMMARY -----\n"
                "Training on %d samples\n"
                "Testing on %d samples\n"
                "Learning rate: %f\n"
                "Batch size: %d\n"
                "Epochs: %d\n"
                "----------------------------\n",
                training_nb, 
                testing_data->size, 
                learning_rate, 
                batch_size, 
                epochs);

    float mini_batch_learning_rate = learning_rate / batch_size;

    // if testing data is the same dataset as training data, we have
    // to make a copy of it to avoid modifying the order each epoch
    if(testing_data == training_data) {
        testing_data = copy_dataset(testing_data, 0);
    }

    for (int e = 0; e < epochs; e++) {
        shuffle_dataset(training_data);
        for (int i = 0; i <= training_nb - batch_size; i += batch_size) {
            update_mini_batch(nn, 
                              training_data,
                              mini_batch_learning_rate, 
                              i,
                              i + batch_size);
        }
        if (verbose) {

            if(testing_data != NULL && testing_data->size > 0) {
                printf("Epoch %i: ", e);
                float accuracy = evaluate(nn, testing_data, verbose);
            }
            
        }
    }
}

void update_mini_batch(NeuralNetwork *nn, dataset *data, float learning_rate,
        int start, int end) {
    matrice **nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **nabla_w = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **delta_nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **delta_nabla_w = malloc(nn->nb_layers * sizeof(matrice *));
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
            nabla_b[j] = matrice_add(nabla_b[j], delta_nabla_b[j]);
            nabla_w[j] = matrice_add(nabla_w[j], delta_nabla_w[j]);
        }
    }

    // update NeuralNetwork weights
    for (int i = 0; i < nn->nb_layers; i++) {

        //printf("nn->layers[%d]->weights = \n", i);
        //matrice_print(nn->layers[i]->weights);
        //printf("nabla_w[%d] = \n", i);
        //matrice_print(nabla_w[i]);
        //printf("nn->layers[%d]->biases = \n", i);
        //matrice_print(nn->layers[i]->biases);
        //printf("\n\n");

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

// Returns the maximum output row index
int max_output(matrice *output) {
    int i;
    int j;
    matrice_max(output, &i, &j);
    return i;
}

// Returns the accuracy of the NeuralNetwork
// on the given data. 
// Will print a summary if verbose is 1 or more.
// Will print the output of each test if verbose is 2 or more.
float evaluate(NeuralNetwork *nn, 
        dataset *data, 
        int verbose) {
    int correct = 0;
    int total = data->size;
    int target_size = data->targets[0]->rows;
    matrice **outputs = malloc(total * sizeof(matrice *));

    matrice *accuracy_matrice = matrice_new(1, total);

    for (int i = 0; i < total; i++) {
        outputs[i] = feedforward(nn, data->inputs[i]);

        // compute accuracy
        matrice *error = matrice_sub(outputs[i] , data->targets[i]); // error = output - target
        matrice_map(error, doubleabs);
        double acc = 1 - matrice_sum(error) / target_size; // accuracy = 1 - mean(abs(error))

        matrice_set(accuracy_matrice, 0, i, acc);

        correct += acc >= 0.5;

        matrice_free(error);
    }

    float accuracy = matrice_sum(accuracy_matrice) / (float) total;

    if (verbose > 0) {
        printf("%i / %i correct (%.2f%%)\n", 
                    correct, 
                    total,
                    accuracy);
    }

    if(verbose > 1) {
        printf("\n");
        for (int i = 0; i < total; i++) {
            printf("Test %i: \n", i);
            matrice_print(data->inputs[i]);
            printf("Target: ");
            matrice_print(data->targets[i]);
            printf("Output: ");
            matrice_print(outputs[i]);
            printf("\n");
        }
        printf("\n\n");
    }

    for (int i = 0; i < total; i++) {
        matrice_free(outputs[i]);
    }
    matrice_free(accuracy_matrice);
    free(outputs);

    return accuracy;
}

#define INPUT_SIZE 784
// loads a dataset from a given path
// dataset is a folder containing 10 folders, one for each digit
//
// path: path to the dataset, e.g. "data/training/"
// size: number of images per class
// returns: a dataset
dataset *load_dataset(const char *path, int size) {
    dataset *data = create_dataset(size * 10);
    data->inputs = malloc(size * 10 * sizeof(matrice *));
    data->targets = malloc(size * 10 * sizeof(matrice *));

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
            SDL_FreeSurface(image);
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

// note that matrices are left uninitialized
dataset *create_dataset(int size) {
    dataset *data = malloc(sizeof(dataset));
    data->inputs = malloc(size * sizeof(matrice *));
    data->targets = malloc(size * sizeof(matrice *));
    data->size = size;
    return data;
}

// if deepcopy is 1, the matrices will be copied
// otherwise, the dataset will only contain pointers to the matrices
// this is useful to keep the same order of the dataset
dataset *copy_dataset(dataset *data, int deepcopy) {
    dataset *copy = create_dataset(data->size);
    for (int i = 0; i < data->size; i++) {
        copy->inputs[i] = matrice_clone(data->inputs[i]);
        copy->targets[i] = matrice_clone(data->targets[i]);
    }
    return copy;
}

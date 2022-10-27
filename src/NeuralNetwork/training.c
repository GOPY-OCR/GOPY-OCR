#include "training.h"
// see http://neuralnetworksanddeeplearning.com/chap2.html

#define PROGRESS_BAR_WIDTH 20
#define PROGRESS_BAR_INTERVAL 1000 // in epochs
#define ACCURACIES_CSV_FILE "_build/accuracies.csv"
void train(NeuralNetwork *nn, 
           int epochs, 
           float learning_rate, 
           int batch_size,
           dataset *training_data, 
           dataset *testing_data,
           int verbose,
           int save_accuracies) {

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

    matrice *accuracies = matrice_new(epochs, 1);
    float accuracy;

    // if testing data is the same dataset as training data, we have
    // to make a copy of it to avoid modifying the order each epoch
    if(testing_data == training_data) {
        testing_data = copy_dataset(testing_data, 0); // 0 = shallow copy, no need to copy the data, only the order
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


        if(testing_data != NULL && testing_data->size > 0) {
            if (verbose > 1) {
                printf("Epoch %i: ", e);
                accuracy = evaluate(nn, testing_data, verbose - 1);
            }

            if (verbose == 1 && (e+1) % PROGRESS_BAR_INTERVAL == 0) {
                accuracy = evaluate(nn, testing_data, 0);

                char progress_indicator[20];
                sprintf(progress_indicator, "Epochs (%.2f%%)", accuracy * 100);
                
                progress_bar(PROGRESS_BAR_WIDTH, e+1, epochs, progress_indicator);
            }

            matrice_set(accuracies, e, 0, accuracy);
        }
        else if (verbose == 1 && (e+1) % PROGRESS_BAR_INTERVAL == 0) {
            progress_bar(PROGRESS_BAR_WIDTH, e+1, epochs, "Epochs");
        }
    }
    if (verbose == 1) {
        progress_bar(PROGRESS_BAR_WIDTH, epochs, epochs, "Epochs");
        printf("\n");
    }

    if (save_accuracies) {

        if (verbose) {
            printf("Saving accuracies to %s\n", ACCURACIES_CSV_FILE);
        }

        char *message = malloc(sizeof(char) * 100);
        sprintf(message, "Accuracy over %d epochs", epochs);
        matrice_to_csv(accuracies, ACCURACIES_CSV_FILE, message);
        free(message);
    }

    if (verbose > 0) {
        printf("Last epoch results: ");
        float accuracy = evaluate(nn, testing_data, 1);
        printf("\n");
    }
}

void update_mini_batch(NeuralNetwork *nn, 
        dataset *data, float learning_rate,
        int start, int end) {
    matrice **nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **nabla_w = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **delta_nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **delta_nabla_w = malloc(nn->nb_layers * sizeof(matrice *));
    matrice *tofree = NULL;

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
            tofree = nabla_b[j];
            nabla_b[j] = matrice_add(nabla_b[j], delta_nabla_b[j]);
            matrice_free(tofree);

            tofree = nabla_w[j];
            nabla_w[j] = matrice_add(nabla_w[j], delta_nabla_w[j]);
            matrice_free(tofree);

            matrice_free(delta_nabla_b[j]);
            matrice_free(delta_nabla_w[j]);
        }
    }

    // update NeuralNetwork weights
    for (int i = 0; i < nn->nb_layers; i++) {
        tofree = nn->layers[i]->weights;
        nn->layers[i]->weights =
            matrice_sub(nn->layers[i]->weights,
                    matrice_multiply(nabla_w[i], (double)learning_rate));
        matrice_free(tofree);

        tofree = nn->layers[i]->biases;
        nn->layers[i]->biases =
            matrice_sub(nn->layers[i]->biases,
                    matrice_multiply(nabla_b[i], (double)learning_rate));
        matrice_free(tofree);

        matrice_free(nabla_b[i]);
        matrice_free(nabla_w[i]);
    }

    free(nabla_b);
    free(nabla_w);
    free(delta_nabla_b);
    free(delta_nabla_w);
}


void backprop(NeuralNetwork *nn, 
        matrice *input, 
        matrice *target,
        matrice **nabla_b, 
        matrice **nabla_w) {
    // feedforward
    matrice *output = input;
    matrice **activations = malloc((nn->nb_layers + 1) * sizeof(matrice *));
    activations[0] = input; // list to store all the activations, layer by layer

    matrice **zs = malloc(nn->nb_layers * sizeof(matrice *)); // list to store all the z vectors, layer by layer
    matrice *dot;
    matrice *sig;
    matrice *delta;
    matrice *sub;
    matrice *transpose;

    for (int i = 0; i < nn->nb_layers; i++) {
        dot = matrice_dot(nn->layers[i]->weights, output);

        output = matrice_add(dot, nn->layers[i]->biases);
        matrice_free(dot);

        zs[i] = matrice_clone(output);
        matrice_map(output, sigmoid);
        activations[i + 1] = output;
    }

    // backpropagation
    // delta = cost_derivative(activations, target) * sigmoid_prime(zs[-1])
    // delta = (ouput - target) * map(zs[nn->nb_layers - 1], sigmoid_prime);
    sig = matrice_clone(zs[nn->nb_layers - 1]);
    matrice_map(sig, sigmoid_prime);
    sub = matrice_sub(output, target);
    delta = matrice_mul(sub, sig);
    transpose = matrice_transpose(activations[nn->nb_layers - 1]);

    nabla_b[nn->nb_layers - 1] = matrice_clone(delta);
    nabla_w[nn->nb_layers - 1] = matrice_dot(delta, transpose);

    matrice_free(sig);
    matrice_free(sub);
    matrice_free(transpose);

    for (int i = nn->nb_layers - 2; i >= 0; i--) {
        sig = matrice_clone(zs[i]);
        matrice_map(sig, sigmoid_prime);
        transpose = matrice_transpose(nn->layers[i + 1]->weights);
        dot = matrice_dot(transpose, delta);

        matrice_free(delta);
        matrice_free(transpose);

        delta = matrice_mul(dot, sig);
        transpose = matrice_transpose(activations[i]);
        nabla_b[i] = matrice_clone(delta);
        nabla_w[i] = matrice_dot(delta, transpose);

        matrice_free(sig);
        matrice_free(dot);
        matrice_free(transpose);
    }

    matrice_free(delta);

    for (int i = 0; i < nn->nb_layers; i++) {
        matrice_free(zs[i]);
    }

    for (int i = 1; i < nn->nb_layers + 1; i++) {
        matrice_free(activations[i]);
    }

    free(zs);
    free(activations);
}


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
                accuracy * 100);
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


int max_output(matrice *output) {
    int i;
    int j;
    matrice_max(output, &i, &j);
    return i;
}


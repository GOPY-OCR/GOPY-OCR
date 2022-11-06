#include "training.h"
// see http://neuralnetworksanddeeplearning.com/chap2.html



// Optimizations to be made:
// - adaptive learning rate (eg *=0.8 if accuracy is not improving for 5 epochs)
// - different loss functions (cross entropy, MSE)
// - data augmentation (eg random rotation, translation, distortion)
// - regularization (eg dropout)
// - convolutional layers
// - early stopping (eg add parameter to stop training if accuracy is not improving for X epochs)

// Currently used techniques:
// - data normalization in image_to_matrix()

// progress bar is visible with verbose=1
#define PROGRESS_BAR_WIDTH 30
#define PROGRESS_BAR_INTERVAL 10000 // in epochs

#define ACCURACIES_CSV_FILE "_build/accuracies.csv"
// max number of training examples to use for computing training accuracy
#define NB_TRAINING_SAMPLES 50000

void train(NeuralNetwork *nn, 
           int epochs, 
           float learning_rate, 
           int batch_size,
           dataset *training_data, 
           dataset *testing_data,
           int verbose,
           int save_accuracies,
           int multithread,
           int compute_training_accuracy,
           float learning_rate_decay) {

    int testing_nb = testing_data != NULL ? testing_data->size : 0;
    int training_nb = training_data->size;

    if(verbose > 0){
        printf( "----- TRAINING SUMMARY -----\n"
                "Training on %d samples\n"
                "Testing on %d samples\n"
                "Learning rate: %s\n"
                "Batch size: %d\n"
                "Epochs: %d\n",
                training_nb, 
                testing_nb, 
                double_to_string(learning_rate),
                batch_size, 
                epochs);

        if(verbose > 1){
            printf("\nOptions enabled: ");
            if(multithread) printf("[multithread] ");
            if(save_accuracies) printf("[save accuracies] ");
            if(learning_rate_decay != 0) 
                printf("[learning_rate_decay (factor: %s)]", 
                        double_to_string(learning_rate_decay));
            printf("\n");

            printf("Network shape: {");
            for(int i=0; i<nn->nb_layers; i++){
                printf("%d", nn->layers[i]->biases->rows);
                if(i < nn->nb_layers-1) printf(", ");
            }
            printf("}\n");
        }

        printf("-----------------------------\n");
    }


    matrice *accuracies = matrice_new(epochs, 1 + compute_training_accuracy);
    float accuracy = -1;
    
    dataset *training_samples = NULL;
    if(compute_training_accuracy){
        shuffle_dataset(training_data);
        int nb_training_samples = training_data->size < NB_TRAINING_SAMPLES ? training_data->size : NB_TRAINING_SAMPLES;
        training_samples = dataset_slice(training_data, 0, nb_training_samples);
    }

    // if testing data is the same dataset as training data, we have
    // to make a copy of it to avoid modifying the order each epoch
    if(testing_data == training_data) {
        testing_data = copy_dataset(testing_data, 0); // 0 = shallow copy, no need to copy the data, only the order
    }

    for (int e = 0; e < epochs; e++) {
        shuffle_dataset(training_data);


        float mini_batch_learning_rate = learning_rate / batch_size;

        for (int i = 0; i <= training_nb - batch_size; i += batch_size) {
            update_mini_batch(nn, 
                              training_data,
                              mini_batch_learning_rate, 
                              i,
                              i + batch_size,
                              multithread);
        }


        if(testing_data != NULL && testing_data->size > 0) {
            if (verbose == 1 && (e==0 || ((e+1) % PROGRESS_BAR_INTERVAL == 0))) {
                accuracy = evaluate(nn, testing_data, 0);

                char progress_indicator[20];
                sprintf(progress_indicator, "Epochs (%.2f%%)", accuracy * 100);
                
                progress_bar(PROGRESS_BAR_WIDTH, e+1, epochs, progress_indicator);
            }

            else if (verbose > 1){
                printf("Epoch %i: ", e);
                accuracy = evaluate(nn, testing_data, verbose - 1);
            }


            matrice_set(accuracies, e, 0, accuracy);

            if (compute_training_accuracy) {
                accuracy = evaluate(nn, training_samples, 0);
                matrice_set(accuracies, e, 1, accuracy);

                if (verbose > 1) {
                    printf(" (training accuracy: %.2f%%)\n", accuracy * 100);
                }
            }
        }
        else if (verbose == 1 && (e==0 || ((e+1) % PROGRESS_BAR_INTERVAL == 0))) {
            progress_bar(PROGRESS_BAR_WIDTH, e+1, epochs, "Epochs");
        }

        apply_learning_rate_decay(e, &learning_rate, verbose, learning_rate_decay);
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
        sprintf(message, "Accuracy over %d epochs (test;train)", epochs);
        matrice_to_csv(accuracies, ACCURACIES_CSV_FILE, message);
        free(message);
    }

    if (testing_data != NULL && testing_data->size > 0 && verbose > 0) {
        printf("Last epoch results: ");
        evaluate(nn, testing_data, 1);
        printf("\n");
    }
}

void update_mini_batch(NeuralNetwork *nn, 
        dataset *data, float learning_rate,
        int start, int end,
        int multithread) {
    matrice **nabla_b = malloc(nn->nb_layers * sizeof(matrice *));
    matrice **nabla_w = malloc(nn->nb_layers * sizeof(matrice *));
    pthread_t threads[THREADS_COUNT];

    for (int i = 0; i < nn->nb_layers; i++) {
        Layer *layer = nn->layers[i];
        nabla_b[i] = matrice_zeros(layer->biases->rows, layer->biases->columns);
        nabla_w[i] =
            matrice_zeros(layer->weights->rows, layer->weights->columns);
    }
    if (multithread) {
        int batch_size = (end - start) / THREADS_COUNT;
        for (int i = 0; i < THREADS_COUNT; i++) {
            int start_index = start + i * batch_size;
            int end_index = start_index + batch_size;
            if (i == THREADS_COUNT - 1) {
                end_index = end;
            }
            struct backprop_thread_args *args = malloc(sizeof(struct backprop_thread_args));
            args->nn = nn;
            args->data = data;
            args->start = start_index;
            args->end = end_index;
            args->nabla_b = nabla_b;
            args->nabla_w = nabla_w;
            pthread_create(&threads[i], NULL, backprog_thread, args);
        }

        for (int i = 0; i < THREADS_COUNT; i++) {
            pthread_join(threads[i], NULL);
        }

        start = start + THREADS_COUNT * batch_size; // this is to avoid missing the lasts samples
    }

    for (int i = start; i < end; i++) {
        matrice *input = data->inputs[i];
        matrice *target = data->targets[i];
        backprop(nn, input, target, nabla_b, nabla_w);
    }

    // update NeuralNetwork weights
    for (int i = 0; i < nn->nb_layers; i++) {
        matrice_sub_inplace(nn->layers[i]->weights, 
                matrice_multiply(nabla_w[i], (double)learning_rate));

        matrice_sub_inplace(nn->layers[i]->biases,
                matrice_multiply(nabla_b[i], (double)learning_rate));

        matrice_free(nabla_b[i]);
        matrice_free(nabla_w[i]);
    }

    free(nabla_b);
    free(nabla_w);
}

void *backprog_thread(void *arg) {
    struct backprop_thread_args *args = (struct backprop_thread_args *)arg;
    for (int i = args->start; i < args->end; i++) {
        matrice *input = args->data->inputs[i];
        matrice *target = args->data->targets[i];
        backprop(args->nn, input, target, args->nabla_b, args->nabla_w);
    }
    return NULL;
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
        output = matrice_dot(nn->layers[i]->weights, output);
        matrice_add_inplace(output, nn->layers[i]->biases);

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
    dot = matrice_dot(delta, transpose);

    matrice_add_inplace(nabla_b[nn->nb_layers - 1], delta);
    matrice_add_inplace(nabla_w[nn->nb_layers - 1], dot);

    matrice_free(sig);
    matrice_free(sub);
    matrice_free(transpose);
    matrice_free(dot);

    for (int i = nn->nb_layers - 2; i >= 0; i--) {
        sig = matrice_clone(zs[i]);
        matrice_map(sig, sigmoid_prime);
        transpose = matrice_transpose(nn->layers[i + 1]->weights);
        dot = matrice_dot(transpose, delta);

        matrice_free(delta);
        matrice_free(transpose);

        delta = matrice_mul(dot, sig);
        matrice_free(dot);

        transpose = matrice_transpose(activations[i]);
        dot = matrice_dot(delta, transpose);
        matrice_add_inplace(nabla_b[i], delta);
        matrice_add_inplace(nabla_w[i], dot);

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

        if (is_correct(outputs[i], data->targets[i])) {
            correct++;
        } else if (verbose > 1) {
            printf("Test %i:\n", i);
            printf("expected: %i, got: %i\n", 
                    max_output(data->targets[i]), 
                    max_output(outputs[i]));
        }
        
        matrice_free(error);
    }

    float accuracy = matrice_sum(accuracy_matrice) / (float) total;

    if (verbose > 0) {
        printf("%i / %i correct (%.2f%%)\n", 
                correct, 
                total,
                accuracy * 100);
    }

    for (int i = 0; i < total; i++) {
        matrice_free(outputs[i]);
    }

    matrice_free(accuracy_matrice);
    free(outputs);

    return accuracy;
}

void apply_learning_rate_decay(int epoch, 
                               float *learning_rate, 
                               int verbose,
                               float decay_rate) {

    if (*learning_rate < 0.000001 || *learning_rate > 10000000){
        // this is to prevent the learning rate from exploding or vanishing
        return;
    }
    *learning_rate *= (1 - decay_rate);

    if (verbose > 1)
        printf("Learning rate decayed to %.2f\n", *learning_rate);
}

int is_correct(matrice *output, matrice *target) {
    return max_output(target) == max_output(output);
}

int max_output(matrice *output) {
    int i;
    int j;
    matrice_max(output, &i, &j);
    return i;
}


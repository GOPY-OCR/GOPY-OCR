#include "digit_recognition.h"

#define NUM_INPUTS 784
#define NN_LAYERS (int[]){64, 10}

// corresponding datasets are 10 times larger
#define TRAINING_SAMPLES_PER_DIGIT 5000 // upto 5000
#define TEST_SAMPLES_PER_DIGIT 100 // upto 800

#define EPOCHS 100
#define LEARNING_RATE 5
#define BATCH_SIZE 1000

#define ENABLE_MULTITHREADING 1

#define RUN_EVALUATIONS 0 // way slower with evaluations

#define SAVE_FILENAME "_build/ocr_save.nn"
int digit_recognition_main(int argc, char **argv, int verbose){
    NeuralNetwork *nn;
    // check if save file exists
    if (file_exists(SAVE_FILENAME)){
        printf("Loading save file: %s\n", SAVE_FILENAME);
        nn = load_neural_network(SAVE_FILENAME);
    } else {
        printf("Creating new neural network\n");
        nn = createOCRNeuralNetwork();
    }

    int epochs = EPOCHS;
    if (argc > 3){
        epochs = atoi(argv[3]);
    }

    // Load the data
    dataset *train_dataset = load_dataset("data/training/", TRAINING_SAMPLES_PER_DIGIT);
    dataset *test_dataset = NULL;
    if (RUN_EVALUATIONS){
        test_dataset = load_dataset("data/testing/", TEST_SAMPLES_PER_DIGIT);
    }

    // TEMP
    // computes the mean and standard deviation of the training dataset
    // and prints it to the console
    // this is used to normalize the input data
    matrice *concat = matrice_new(train_dataset->inputs[0]->rows, train_dataset->inputs[0]->columns * train_dataset->size);

    for (int i = 0; i < train_dataset->size; i++){
        int offset = i * train_dataset->inputs[0]->columns;
        for (int row = 0; row < train_dataset->inputs[i]->rows; row++){
            for (int col = 0; col < train_dataset->inputs[i]->columns; col++){
                matrice_set(concat, row, offset + col, matrice_get(train_dataset->inputs[i], row, col));
            }
        }
    }

    double mean = matrice_mean(concat);
    double std = matrice_std(concat);
    
    printf("mean: %.20f, std: %.20f\n", mean, std);
    
    // TEMP

    // Train the neural network
    train(nn, epochs, LEARNING_RATE, BATCH_SIZE, train_dataset, test_dataset, verbose, RUN_EVALUATIONS, ENABLE_MULTITHREADING);

    // Save the neural network
    if (verbose)
        printf("Saving the neural network to %s\n", SAVE_FILENAME);

    save_neural_network(nn, SAVE_FILENAME);

    float accuracy = evaluate(nn, test_dataset!=NULL?test_dataset:train_dataset, verbose > 0);

    return 0;
}


NeuralNetwork* createOCRNeuralNetwork() {
    int nb_layers = sizeof(NN_LAYERS) / sizeof(int);

    NeuralNetwork* nn = create_neural_network(nb_layers, NUM_INPUTS, NN_LAYERS);

    return nn;
}

int predict_digit(char* filename, NeuralNetwork *nn) {
    SDL_Surface *img = load_image(filename);

    matrice *m = image_to_matrice(img);

    matrice *output = feedforward(nn, m);

    int digit = max_output(output);

    // Free the image and data
    SDL_FreeSurface(img);
    matrice_free(m);
    matrice_free(output);

    return digit;
}


void predict_image(NeuralNetwork *nn, char *filename) {
    int digit = predict_digit(filename, nn);

    printf("Predicted digit: %d\n", digit);
}

void predict_all_images_in_dir(NeuralNetwork *nn, char *folder){
    int nb_files = count_files_in_dir(folder);
    char **files = list_files(folder, nb_files, 1);
    int predictions[10] = {0};
    for (int i = 0; i < nb_files; i++) {
        int prediction = predict_digit(files[i], nn);
        predictions[prediction]++;
    }
    printf(    "|Digit|Predictions|\n");
    printf(    "|-----|-----------|\n");
    for (int i = 0; i < 10; i++) {
        if (predictions[i] > 0) {
            printf("|  %d  |%11d|\n", i, predictions[i]);
        } else {
            printf("|  %d  |           |\n", i);
        }
    }
}

void predict_all_images(NeuralNetwork *nn) {
    int results[100] = {0};
    for (int i = 0; i < 10; i++) {
        char folder[100];
        sprintf(folder, "data/testing/%d/", i);
        int nb_files = count_files_in_dir(folder);
        char **files = list_files(folder, nb_files, 1);
        for (int j = 0; j < nb_files; j++) {
            int prediction = predict_digit(files[j], nn);
            results[i * 10 + prediction]++;
        }
    }
    printf("Running predictions on all images in data/testing/\n");
    // this is one line, the formatting is to avoid 80 char limit
    printf("|predict\\expect"
           "|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |\n");
    for (int i = 0; i < 10; i++) {
        printf("|      %d       |", i);
        for (int j = 0; j < 10; j++) {
            if (results[i * 10 + j] > 0) {
                printf("%5d|", results[i * 10 + j]);
            } else {
                printf("     |");
            }
        }
        printf("\n");
    }

    int grand_total = 0;
    printf("| Total misses |");
    for (int i = 0; i < 10; i++) {
        int total = 0;
        for (int j = 0; j < 10; j++) {
            if (i != j) {
                total += results[i * 10 + j];
            }
        }
        printf("%-5d|", total);
        grand_total += total;
    }
    printf("\n");
    printf("Grand total: %d\n", grand_total);
}


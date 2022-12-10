#include "digit_recognition.h"

#define NUM_INPUTS 784
#define NN_LAYERS (int[]){128, 10}

// corresponding datasets are 10 times larger
#define TRAINING_SAMPLES_PER_DIGIT 500 // 500 images from github, 22 from our sudokus
#define TEST_SAMPLES_PER_DIGIT 40

#define EPOCHS 20
#define LEARNING_RATE 0.7
#define BATCH_SIZE 200

#define ENABLE_MULTITHREADING 1

#define LEARNING_RATE_DECAY -0.03

#define RUN_EVALUATIONS 1
#define RUN_EVALUATIONS_ON_TRAINING 1

#define COST_FUNCTION cross_entropy_cost


int *neural_network(SDL_Surface **splitted) {
    int *res = calloc(81, sizeof(int));
    NeuralNetwork *nn = load_neural_network(NN_SAVE_FILENAME);
    for (size_t i = 0; i < 81; i++)
        res[i] = predict_surface(splitted[i], nn);

    return res;
}

int digit_recognition_main(int argc, char **argv, int verbose){
    NeuralNetwork *nn;
    // check if save file exists
    if (file_exists(NN_SAVE_FILENAME)){
        printf("Loading save file: %s\n", NN_SAVE_FILENAME);
        nn = load_neural_network(NN_SAVE_FILENAME);
    } else {
        printf("Creating new neural network\n");
        nn = create_OCR_Neural_Network();
    }

    // temporary usage: ./main -t -v/vv/vvv [epochs] [learning rate] [batch size]
    int epochs = EPOCHS;
    if (argc > 3){
        epochs = atoi(argv[3]);
    }
    double learning_rate = LEARNING_RATE;
    if (argc > 4){
        learning_rate = atof(argv[4]);
    }
    int batch_size = BATCH_SIZE;
    if (argc > 5){
        batch_size = atoi(argv[5]);
    }

    // Load the data
    dataset *train_dataset = load_dataset("data/training/", TRAINING_SAMPLES_PER_DIGIT);
    dataset *test_dataset = NULL;
    if (RUN_EVALUATIONS){
        test_dataset = load_dataset("data/testing/", TEST_SAMPLES_PER_DIGIT);
    }

    // get mean and std (for normalization)
    //matrice *all = matrice_new(train_dataset->size * NUM_INPUTS, 1);
    //for (int i = 0; i < train_dataset->size; i++){
    //    for (int j = 0; j < NUM_INPUTS; j++){
    //        matrice_set(all, i * NUM_INPUTS + j, 0, matrice_get(train_dataset->inputs[i], j, 0));
    //    }
    //}
    //double mean = matrice_mean(all);
    //double std = matrice_std(all);
    //printf("mean: %.10f, std: %.10f\n", mean, std);

    // Train the neural network
    train(nn, 
          epochs, 
          learning_rate, 
          batch_size, 
          train_dataset, 
          test_dataset, 
          verbose, 
          RUN_EVALUATIONS, 
          ENABLE_MULTITHREADING, 
          RUN_EVALUATIONS_ON_TRAINING,
          LEARNING_RATE_DECAY);


    // Save the neural network
    if (verbose)
        printf("Saving the neural network to %s\n", NN_SAVE_FILENAME);

    save_neural_network(nn, NN_SAVE_FILENAME);

    evaluate(nn, test_dataset!=NULL?test_dataset:train_dataset, verbose > 0);

    return 0;
}


NeuralNetwork* create_OCR_Neural_Network() {
    int nb_layers = sizeof(NN_LAYERS) / sizeof(int);

    NeuralNetwork* nn = create_neural_network(nb_layers, NUM_INPUTS, NN_LAYERS);

    nn->cost_function = COST_FUNCTION;

    return nn;
}

int predict_digit(char* filename, NeuralNetwork *nn) {
    SDL_Surface *img = load_image(filename);

    int digit = predict_surface(img, nn);

    // Free the image and data
    SDL_FreeSurface(img);

    return digit;
}

int predict_surface(SDL_Surface *img, NeuralNetwork *nn) {
    if (img->w != 28 || img->h != 28) {
        // resize the image
        SDL_Surface *resized = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);
        SDL_BlitScaled(img, NULL, resized, NULL);
        SDL_FreeSurface(img);
        img = resized;
    }

    matrice *m = image_to_matrice(img);

    matrice *output = feedforward(nn, m);

    int digit = max_output(output);

    // Free the image and data
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

void predict_all_images(NeuralNetwork *nn, int argc, char **argv, int verbose) {
    int results[100] = {0};
    int tot_files = 0;

    char *misses_folder = "data/misses/";
    int le = strlen(misses_folder);
    char *subfolder = malloc(le + 3);

    int save_misses = (argc > 0 && (strcmp(argv[0], "-s") == 0 
                                 || strcmp(argv[0], "--save-misses") == 0));

    if (save_misses){
        // deletes the old misses folder, and recreate it empty
        if (dir_exists(misses_folder)){
            if (verbose)
                printf("Deleting old misses folder: %s\n", misses_folder);

            delete_dir_recursive(misses_folder);
        }

        if (verbose)
            printf("Creating new misses folder: %s\n", misses_folder);
        
        mkdir(misses_folder, 0777);

        subfolder[le + 1] = '/';
        subfolder[le + 2] = '\0';
        strcpy(subfolder, misses_folder);
        for (int i = 0; i < 10; i++) {
            subfolder[le] = '0' + i;
            if (!dir_exists(subfolder)){
                mkdir(subfolder, 0777);
            }
        }
    }

    for (int i = 0; i < 10; i++) {
        char folder[100];
        sprintf(folder, "data/testing/%d/", i);
        int nb_files = count_files_in_dir(folder);
        tot_files += nb_files;
        char **files = list_files(folder, nb_files, 1);
        for (int j = 0; j < nb_files; j++) {
            int prediction = predict_digit(files[j], nn);
            results[i * 10 + prediction]++;

            if (prediction != i && save_misses){
                subfolder[le] = '0' + i;
                char *new_filename = malloc(strlen(subfolder) + strlen(files[j]) + 1);
                strcpy(new_filename, subfolder);
                
                // this is the length of "data/testing/"
                const int prefix_trim = 15; 

                strcat(new_filename, files[j] + prefix_trim);
                copy_file(files[j], new_filename);
            }
        }
    }
    printf("Running predictions on all images in data/testing/\n");
    // this is one line, this formatting is to avoid 80 char limit
    printf("|predict\\expect"
           "|  0  |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |\n");
    for (int i = 0; i < 10; i++) {
        printf("|      %d       |", i);
        for (int j = 0; j < 10; j++) {
            if (results[j * 10 + i] > 0) {
                printf("%5d|", results[j * 10 + i]);
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
        printf("%5d|", total);
        grand_total += total;
    }
    printf("\n");
    printf("Grand total: %d/%d misses (%.2f%% accuracy)\n", 
            grand_total, tot_files, 100.0 * (tot_files - grand_total) / tot_files);
}


void sort_images(int argc, char **argv, int verbose){
    char *folder = ".";

    if (argc > 0){
        folder = argv[0];

        int le = strlen(folder);
        if (folder[le - 1] == '/'){
            folder[le - 1] = '\0';
        }
    }

    int nb_files = count_files_in_dir(folder);
    char **files = list_files(folder, nb_files, 1);
    int nb_folders = 10;
    char **folders = malloc(sizeof(char *) * nb_folders);

    NeuralNetwork *nn = load_neural_network(NN_SAVE_FILENAME);
    
    for (int i = 0; i < nb_folders; i++) {
        folders[i] = malloc(100);
        sprintf(folders[i], "%s/%d", folder, i);
        if (!dir_exists(folders[i])){
            if (verbose == 2)
                printf("Creating folder: %s\n", folders[i]);
            mkdir(folders[i], 0777);
        }
    }

    for (int i = 0; i < nb_files; i++) {
        char *filename = files[i];
        int len = strlen(filename);

        // check if ends with .png
        if (!(len > 4 && strcmp(filename + len - 4, ".png") == 0)) {
            continue;
        }

        int digit = predict_digit(filename, nn);

        char *new_filename = malloc(strlen(folders[digit]) + len + 2);
        strcpy(new_filename, folders[digit]);
        strcat(new_filename, "/");
        strcat(new_filename, filename + strlen(folder) + 1);

        if (verbose == 1)
            printf("Moving %s to %s\r", filename, new_filename);
        else if (verbose == 2)
            printf("Moving %s to %s\n", filename, new_filename);

        move_file(filename, new_filename);


        free(new_filename);
        free(filename);
    }

    for (int i = 0; i < nb_folders; i++) {
        free(folders[i]);
    }

    free(folders);
    free_neural_network(nn);
    free(files);
}

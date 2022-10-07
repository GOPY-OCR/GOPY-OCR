#include "training.h"

void train(NeuralNetwork nn, int epochs, float learning_rate,
           dataset training_data, dataset testing_data) {
    //! TODO
    dataset data = load_dataset("data/training/");
}

// loads a dataset from a given path
// dataset is a folder containing 10 folders, one for each digit
//
dataset load_dataset(const char *path) { dataset data; }

// list files in a directory
//
// path: path to directory
// n: maximum number of files to list
// returns: list of files in directory
char **list_files(const char *path, int n) {}

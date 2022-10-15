#pragma once
#include "maths.h"
#include "matrice.h"
#include "neural_network.h"
#include "utils.h"
#include <dirent.h>


#define INPUT_SIZE 784 // 28x28 pixel images

typedef struct dataset {
    matrice **inputs;
    matrice **targets;
    int size;
} dataset;

// note that matrices are left uninitialized
dataset *create_dataset(int size);

// if deepcopy, the matrices will be copied too
// otherwise, the dataset will only contain pointers to the matrices
// this is useful to keep the same order of the dataset without 
// needing to allocate twice as much memory for the dataset
dataset *copy_dataset(dataset *data, int deepcopy);

// trains the neural network with the given training data
// by calling the update_mini_batch function repeatedly
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
           int verbose);


// Applies the backpropagation algorithm to a mini-batch.
// A mini-batch is a subset of the training data.
void update_mini_batch(NeuralNetwork *nn, 
                       dataset *data, 
                       float learning_rate,
                       int start, 
                       int end);


// Returns nabla_b, nabla_w representing the
// gradient for the cost function.  nabla_b and
// nabla_w are arrays of matrices, similar
// to NeuralNetwork->biases and NeuralNetwork->weights.
void backprop(NeuralNetwork *nn, 
              matrice *input, 
              matrice *target,
              matrice **nabla_b, 
              matrice **nabla_w);




// Returns the accuracy of the NeuralNetwork
// on the given data. 
// Will print a summary if verbose is 1 or more.
// Will print the output of each test if verbose is 2 or more.
float evaluate(NeuralNetwork *nn, dataset *data, int verbose);

// loads a dataset from a given path
// dataset is a folder containing 10 folders, one for each digit
//
// path: path to the dataset, e.g. "data/training/"
// size: number of images per class
// returns: a dataset
dataset *load_dataset(const char *path, int size);


// converts a list of images to a list of inputs
// images: list of images
// size: number of images

// list files and sub-directories in a directory
//
// path: path to directory
// n: maximum number of files to list
// returns: list of files in directory
char **list_files(const char *path, int n);


void shuffle_dataset(dataset *data);


// Returns the maximum output row index
int max_output(matrice *output);

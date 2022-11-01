#pragma once
#include "maths.h"
#include "matrice.h"
#include "matrice_multithread.h"
#include "neural_network.h"
#include "sdl_utils.h"
#include "dataset.h"
#include "progress_bar.h"
#include <pthread.h>

// trains the neural network with the given training data
// by calling the update_mini_batch function repeatedly
//
// neural_network: the neural network to train
// epochs: the number of epochs to train the neural network
// training_data: the training dataset to train the neural network with
// testing_data: (optional) used to evaluate the neural network after each epoch
// verbose_level: 0 = no output, 
// 		  1 = parameters summary and final eval,
//		  2 = per epoch summary, 
//		  3 = per testing data summary every epoch
void train(NeuralNetwork *nn, 
           int epochs, 
           float learning_rate, 
           int batch_size,
           dataset *training_data, 
           dataset *testing_data, 
           int verbose,
           int save_accuracies,
           int multithread);

// Applies the backpropagation algorithm to a mini-batch.
// A mini-batch is a subset of the training data.
void update_mini_batch(NeuralNetwork *nn, 
                       dataset *data, 
                       float learning_rate,
                       int start, 
                       int end,
                       int multithread);


struct backprop_thread_args {
    NeuralNetwork *nn;
    dataset *data;
    int start;
    int end;
    matrice **nabla_b;
    matrice **nabla_w;
};

void *backprog_thread(void *arg);
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

// Returns the maximum output row index
int max_output(matrice *output);


int is_correct(matrice *output, matrice *target);

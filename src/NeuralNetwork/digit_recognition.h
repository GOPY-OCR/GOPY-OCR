#pragma once
#include "neural_network.h"
#include "training.h"
#include "matrice.h"
#include "file_utils.h"
#include <argp.h>

int digit_recognition_main(int argc, char **argv, int verbose);

NeuralNetwork* createOCRNeuralNetwork();


int predict_digit(char* filename, NeuralNetwork *nn);



void predict_image(NeuralNetwork *nn, char *filename) ;
void predict_all_images_in_dir(NeuralNetwork *nn, char *folder);
void predict_all_images(NeuralNetwork *nn) ;

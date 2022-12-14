#pragma once
#include "neural_network.h"
#include "training.h"
#include "matrice.h"
#include "file_utils.h"
#include "cost_functions.h"
#include <argp.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>

#define NN_SAVE_FILENAME "assets/NeuralNetwork/ocr_save.nn"

// main function called in GUI and CLI
int *neural_network(SDL_Surface **splitted);

int digit_recognition_main(int argc, char **argv, int verbose);

NeuralNetwork* create_OCR_Neural_Network();

int predict_digit(char* filename, NeuralNetwork *nn);

int predict_surface(SDL_Surface *img, NeuralNetwork *nn);
void predict_image(NeuralNetwork *nn, char *filename) ;
void predict_all_images_in_dir(NeuralNetwork *nn, char *folder);
void predict_all_images(NeuralNetwork *nn, int argc, char **argv, int verbose);

void sort_images(int argc, char **argv, int verbose);

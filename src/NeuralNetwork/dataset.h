#pragma once
#include "matrice.h"
#include "sdl_utils.h"
#include "pixel_utils.h"
#include "file_utils.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <dirent.h>

#define INPUT_SIZE 784 // 28x28 pixel images

typedef struct dataset {
    matrice **inputs;
    matrice **targets;
    int size;
} dataset;

// note that matrices are left uninitialized
dataset *create_dataset(int size);
void free_dataset(dataset *d);

// if deepcopy, the matrices will be copied too
// otherwise, the dataset will only contain pointers to the matrices
// this is useful to keep the same order of the dataset without 
// needing to allocate twice as much memory for the dataset
dataset *copy_dataset(dataset *data, int deepcopy);

// loads a dataset from a given path
// dataset is a folder containing 10 folders, one for each digit
//
// path: path to the dataset, e.g. "data/training/"
// size: number of images per class
// returns: a dataset
dataset *load_dataset(const char *path, int size);

matrice *image_to_matrice(SDL_Surface *image);

void shuffle_dataset(dataset *data);


dataset *dataset_slice(dataset *data, int start, int end);

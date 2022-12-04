#ifndef PREPROCESS_BINARIZE_H
#define PREPROCESS_BINARIZE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "vector.h"
#include "matrice.h"
#include "pixel_utils.h"

void binarize(SDL_Surface *base, int threshold, SDL_Surface *result);

void otsu_binarize(SDL_Surface *base);

int find_threshold(SDL_Surface *base);

// algorithm from https://en.wikipedia.org/wiki/Otsu%27s_method#Python_implementation
double compute_otsu_criteria(SDL_Surface *base, int threshold);

double pixel_variance(Vector *v);

#endif

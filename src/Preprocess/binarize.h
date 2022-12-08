#ifndef PREPROCESS_BINARIZE_H
#define PREPROCESS_BINARIZE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "matrice.h"

void binarize(SDL_Surface *base, int threshold);

void adaptative(SDL_Surface **base);

#endif



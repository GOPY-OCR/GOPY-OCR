#ifndef PREPROCESS_BINARIZE_H
#define PREPROCESS_BINARIZE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <assert.h>
#include "matrice.h"
#include "pixel_utils.h"

void binarize(SDL_Surface *base, int threshold);

void adaptative_binarize(SDL_Surface *base);

#endif



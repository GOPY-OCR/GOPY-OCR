#ifndef PREPROCESS_RESIZE_H
#define PREPROCESS_RESIZE_H
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>
#include "point.h"
#include "pixel_utils.h"
#include "maths.h"

#define NEW_SIZE 500
#define NN_SIZE 28

void resize(SDL_Surface **base);
void neural_network_resize(SDL_Surface *splitted[81]);

#endif



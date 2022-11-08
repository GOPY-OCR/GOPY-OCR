#ifndef PREPROCESS_NOISE_H
#define PREPROCESS_NOISE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sdl_utils.h"
#include "pixel_utils.h"

#define SIZE_SIDE_FILTER 7
const int FILTER[] = {
    0, 0, 1, 1, 1, 0, 0,
    0, 1, 1, 1, 1, 1, 0,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1,
    0, 1, 1, 1, 1, 1, 0,
    0, 0, 1, 1, 1, 0, 0
};


Uint32 max_color_pixels(SDL_Surface *surface, int x, int y);
Uint32 min_color_pixel(SDL_Surface *surface, int x, int y);
SDL_Surface *dilation(SDL_Surface *base);
SDL_Surface *erosion(SDL_Surface *base);
SDL_Surface *closing(SDL_Surface *base);

#endif



#ifndef PREPROCESS_BRIGHTNESS_H
#define PREPROCESS_BRIGHTNESS_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sdl_utils.h"
#include "morphology.h"

SDL_Surface *divide_images(SDL_Surface *numerator, SDL_Surface *denominator);
SDL_Surface *correct_brightness(SDL_Surface *base);

#endif



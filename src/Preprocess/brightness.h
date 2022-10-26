#ifndef PREPROCESS_BRIGHTNESS_H
#define PREPROCESS_BRIGHTNESS_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "sdl_utils.h"
#include "morphology.h"

void divide_images(SDL_Surface *numerator, SDL_Surface *denominator);
void correct_brightness(SDL_Surface *base);

#endif



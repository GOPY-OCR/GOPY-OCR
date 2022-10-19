#ifndef PREPROCESS_NOISE_H
#define PREPROCESS_NOISE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL2.h>

SDL_Surface *erosion(SDL_Surface *base);
SDL_Surface *dilation(SDL_Surface *base);
SDL_Surface *opening(SDL_Surface *base);
SDL_Surface *closing(SDL_Surface *base);

#endif



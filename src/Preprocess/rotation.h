#pragma once
#include "SDL2_rotozoom.h"
#include "grid_detection.h"

SDL_Surface *manual_rot(SDL_Surface* image, double angle);
SDL_Surface *auto_rot(SDL_Surface *image);


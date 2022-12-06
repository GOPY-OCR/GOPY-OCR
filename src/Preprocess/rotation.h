#pragma once
#include <math.h>
#include <SDL2/SDL.h>
#include "pixel_utils.h"
#include "grid_detection.h"

void manual_rot(SDL_Surface **image, double angle);
void automatic_rot(SDL_Surface **image);

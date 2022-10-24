#pragma once
#include "pixel_utils.h"
#include "point.h"
#include "queue.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// returns the number of pixels filled
int flood_fill(SDL_Surface *image, Point point, Uint32 color);

#pragma once
#include <SDL2/SDL.h>
#include "point.h"
#include "flood_fill.h"

// Extracts the maximum component from the image
//
// flood_fill_connectivity: 2 for grid detection, 1 for cell denoise
SDL_Surface *extract_max_component(SDL_Surface *image, int flood_fill_connectivity, int remove);

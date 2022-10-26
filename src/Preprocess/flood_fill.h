#pragma once
#include "pixel_utils.h"
#include "point.h"
#include "queue.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// returns the number of pixels filled
//
// params:
//  surface: the surface to fill
//  Point{x, y}: the starting point
//  Uint32: the color to fill with
//  max_fill: set do 0 to fill the entire surface,
//            otherwise, when the max_fill is reached,
//            the fill will be canceled, and it will
//            return -1
//
//
//  THIS IS WIP:
//  TODO: implement grid detection using flood fill
int flood_fill(SDL_Surface *image, Point point, Uint32 color);

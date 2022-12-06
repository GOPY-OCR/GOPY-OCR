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
//  cancel_fill: if true, the filled pixels will be reset to the original color
//  dest: if not null, the filled pixels will be copied to this surface
//
//  THIS IS WIP:
//  TODO: implement grid detection using flood fill
int flood_fill(SDL_Surface *image, Point point, Uint32 color, int cancel_fill, SDL_Surface *dest, int connectivity);

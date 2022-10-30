#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// returns a pointer to the pixel
// at (x, y) in the image surface
// or NULL if the pixel is out of bounds
Uint32 *getpixel(SDL_Surface *surface, int x, int y);
int is_pixel_white(SDL_Surface *image, int x, int y);
void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

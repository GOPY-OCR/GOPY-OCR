#ifndef PREPROCESS_GRAYSCALE_H
#define PREPROCESS_GRAYSCALE_H
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);
void surface_to_grayscale(SDL_Surface* surface);

#endif



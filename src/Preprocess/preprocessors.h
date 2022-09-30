#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


SDL_Surface* load_image(const char* path);

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format);

void surface_to_grayscale(SDL_Surface* surface);

void surface_rotate(SDL_Surface* surface, int angle);

void surface_flip(SDL_Surface* surface, int flip_mode);

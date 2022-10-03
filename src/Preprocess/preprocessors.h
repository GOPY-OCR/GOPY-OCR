#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <utils.h>

void save_image(const char *path, SDL_Surface *image);

Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat *format);
void surface_to_grayscale(SDL_Surface *surface);

void surface_rotate(SDL_Surface *surface, int angle);
void surface_flip(SDL_Surface *surface, int flip_mode);

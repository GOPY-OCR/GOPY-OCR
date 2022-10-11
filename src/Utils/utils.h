#pragma once
#include <stddef.h>
#include <SDL2/SDL.h>

SDL_Surface *load_image(const char *path);
void save_image(SDL_Surface *surface, const char *path);

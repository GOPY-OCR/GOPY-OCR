#ifndef UTILS_H
#define UTILS_H
#include <stddef.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Surface *new_blank_surface(SDL_Surface *base);
SDL_Surface *load_image(const char *path);
void save_image(SDL_Surface *surface, const char *path);

#endif

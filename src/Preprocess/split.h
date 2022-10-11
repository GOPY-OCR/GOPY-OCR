#ifndef PREPROCESS_SPLIT_H
#define PREPROCESS_SPLIT_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Surface* crop_surface(const SDL_Surface* grid, int x, int y, int width, int height);
SDL_Surface*[] split_sudoku(const SDL_Surface* grid);

#endif



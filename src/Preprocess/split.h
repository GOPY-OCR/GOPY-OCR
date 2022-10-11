#ifndef PREPROCESS_SPLIT_H
#define PREPROCESS_SPLIT_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

SDL_Surface* crop_surface(SDL_Surface* grid, int x, int y, 
                          int width, int height);
void split_sudoku(SDL_Surface* grid, SDL_Surface *splitted[81]);

#endif



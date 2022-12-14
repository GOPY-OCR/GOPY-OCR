#ifndef POST_CREATE_IMAGE_H
#define POST_CREATE_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#define OLD_NUMBER_COLOR (SDL_Color){0, 0, 0, 255}
#define NEW_NUMBER_COLOR (SDL_Color){0, 0, 255, 255}
#define BACK_COLOR 0xFFFFFFFF
#define GRID_COLOR 0
#define FONT "assets/font/ArchivoNarrow-Regular.ttf"

#ifndef CELL_SIZE
    #define CELL_SIZE 100
#endif
#ifndef BOARDSIZE
    #define BOARDSIZE 9
#endif

void add_number(SDL_Surface *res, int x, int y, int number, int *grid);

#endif

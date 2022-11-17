#ifndef POST_CREATE_IMAGE_H
#define POST_CREATE_IMAGE_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#define OLD_NUMBER_COLOR {0, 0, 0}
#define NEW_NUMBER_COLOR {0, 0, 255}
#define GRID_COLOR 0xFFFFFFFF
#define BACK_COLOR 0
#define CELL_SIZE 100
#define FONT "ArchivoNarrow-Regular.ttf"

#ifndef BOARDSIZE
    #define BOARDSIZE 9
#endif

int is_initial_number(int x, int y, int *grid);
void draw_grid(SDL_Surface *res, int nb_cases);
void add_number(SDL_Surface *res, int x, int y, int number);

#endif

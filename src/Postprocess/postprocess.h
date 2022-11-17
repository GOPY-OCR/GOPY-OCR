#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include "sdl_utils.h"
#include "create_image.h"

#ifndef CELL_SIZE
    #define CELL_SIZE 100
#endif
#ifndef BOARDSIZE
    #define BOARDSIZE 9
#endif

SDL_Surface *postprocess(int *grid, int *solved);

#endif



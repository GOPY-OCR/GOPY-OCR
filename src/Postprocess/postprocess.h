#ifndef POSTPROCESS_H
#define POSTPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include "sdl_utils.h"
#include "create_image.h"

#ifndef BOARDSIZE
    #define BOARDSIZE 9
#endif

SDL_Surface *postprocess(int *grid, int *solved);

#endif



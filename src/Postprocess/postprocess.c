#include "postprocess.h"

SDL_Surface *postprocess(int *grid, int *solved) {
    SDL_Surface *res = SDL_CreateRGBSurfaceWithFormat(0,
                                                   BOARDSIZE * CELL_SIZE,
                                                   BOARDSIZE * CELL_SIZE,
                                                   32,                      // 32 bits per pixel
                                                   SDL_PIXELFORMAT_RGB888);

    draw_grid(res);

    for(size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++)
        add_number(res,
                   i % BOARDSIZE,
                   i / BOARDSIZE,
                   solved[i],
                   grid);

    return res;
}


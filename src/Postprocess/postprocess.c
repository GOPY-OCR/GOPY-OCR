#include "postprocess.h"

SDL_Surface *postprocess(int *grid, int *solved) {
    SDL_Surface *res = SDL_CreateSurfaceWithFormat(0,
                                                   BOARDSIZE * 100,
                                                   BOARDSIZE * 100,
                                                   32,                      // 32 bits per pixel
                                                   SDL_PIXELFORMAT_RGB888);

    draw_grid(res, BOARDSIZE);
    for(size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++) {
        
    }
}


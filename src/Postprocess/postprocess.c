#include "postprocess.h"

SDL_Surface *postprocess(int *grid, int *solved) {
    SDL_Surface *res = load_image(TEMPLATE);

    for(size_t i = 0; i < BOARDSIZE * BOARDSIZE; i++)
        add_number(res,
                   i % BOARDSIZE,
                   i / BOARDSIZE,
                   solved[i],
                   grid);

    return res;
}


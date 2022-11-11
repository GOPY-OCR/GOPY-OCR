#include "resize.h"

void resize(SDL_Surface **base) {
    SDL_Surface *dest = SDL_CreateRGBSurface(
            (*base)->flags,
            NEW_SIZE,
            NEW_SIZE,
            (*base)->format->BitsPerPixel,
            (*base)->format->Rmask,
            (*base)->format->Gmask,
            (*base)->format->Bmask,
            (*base)->format->Amask
            );

    SDL_Rect drect = { 0, 0, NEW_SIZE, NEW_SIZE };

    if (SDL_BlitScaled(*base, NULL, dest, &drect) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    SDL_FreeSurface(*base);
    *base = dest;
}


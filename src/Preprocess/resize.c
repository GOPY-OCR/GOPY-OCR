#include "resize.h"

void resize(SDL_Surface **base) {
    int width = NEW_SIZE;
    int height = (float) NEW_SIZE / (float) (*base)->w * (*base)->h;
    SDL_Surface *dest = SDL_CreateRGBSurface(
            (*base)->flags,
            width,
            height,
            (*base)->format->BitsPerPixel,
            (*base)->format->Rmask,
            (*base)->format->Gmask,
            (*base)->format->Bmask,
            (*base)->format->Amask
            );

    SDL_Rect drect = { 0, 0, width, height };

    if (SDL_BlitScaled(*base, NULL, dest, &drect) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());
    
    SDL_FreeSurface(*base);
    *base = dest;
}


#include "binarize.h"

void binarize(SDL_Surface *base) {
    Uint32 *pixels = base->pixels;
    int len = base->w * base->h;
    for (size_t i = 0; i < len; i++)
        pixels[i] = ((Uint8) pixels[i]) >= THRESHOLD ? 0xFFFFFF : 0;
}


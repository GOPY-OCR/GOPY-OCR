#include "binarize.h"

void binarize(SDL_Surface *base, int threshold) {
    Uint32 *pixels = base->pixels;
    size_t len = base->w * base->h;
    for (size_t i = 0; i < len; i++)
        pixels[i] = ((Uint8) pixels[i]) >= threshold ? 0 : 0xFFFFFF;
}


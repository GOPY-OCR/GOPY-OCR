#include "brightness.h"

// img1 and img2 must differ only by their pixel colors
void divide_images(SDL_Surface *numerator, SDL_Surface *denominator) {
    if (SDL_LockSurface(numerator)!= 0)
        errx(1, "%s", SDL_GetError());

    if (SDL_LockSurface(denominator)!= 0)
        errx(1, "%s", SDL_GetError());

    Uint32 *num_pixels = numerator->pixels;
    Uint32 *den_pixels = denominator->pixels;
    int len = numerator->w * numerator->h;
    for (size_t i = 0; i < len; i++) {
        float n_tmp = num_pixels[i] & 0xFF;
        float d_tmp = den_pixels[i] & 0xFF;
        Uint8 res = n_tmp / d_tmp * 0xFF;
        num_pixels[i] = res + (res << 8) + (res << 16) + (res << 24);
    }

    SDL_UnlockSurface(numerator);
    SDL_UnlockSurface(denominator);
}

void correct_brightness(SDL_Surface *base) {
    SDL_Surface *white = closing(base);
    divide_images(base, white);
    SDL_FreeSurface(white);
}




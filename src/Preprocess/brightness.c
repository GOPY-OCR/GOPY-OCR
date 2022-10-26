#include "brightness.h"

// img1 and img2 must differ only by their pixel colors
SDL_Surface *divide_images(SDL_Surface *numerator, SDL_Surface *denominator) {
    SDL_Surface *res = new_blank_surface(numerator);
    SDL_LockSurface(numerator);
    SDL_LockSurface(denominator);
    SDL_LockSurface(res);
    Uint32 *res_pixels = res->pixels;
    Uint32 *num_pixels = numerator->pixels;
    Uint32 *den_pixels = denominator->pixels;
    size_t len = res->w * res->h;
    printf("%s", SDL_GetPixelFormatName(res->format));
    for (size_t i = 0; i < len; i++) {
        float n_tmp = num_pixels[i] & 0xFF;
        float d_tmp = den_pixels[i] & 0xFF;
        Uint8 res = n_tmp / d_tmp * 0xFF;
        res_pixels[i] = res + (res << 8) + (res << 16) + (res << 24);
    }

    SDL_UnlockSurface(numerator);
    SDL_UnlockSurface(denominator);
    SDL_UnlockSurface(res);
    return res;
}

SDL_Surface *correct_brightness(SDL_Surface *base) {
    SDL_Surface *white = closing(base);

    SDL_Surface *res = divide_images(base, white);

    SDL_FreeSurface(white);
   
    return res;
}




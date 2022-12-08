#include "binarize.h"

void binarize(SDL_Surface *base, int threshold) {
    Uint32 *pixels = base->pixels;
    size_t len = base->w * base->h;
    for (size_t i = 0; i < len; i++)
        pixels[i] = ((Uint8) pixels[i]) >= threshold ? 0 : 0xFFFFFF;
}

// algorithm from https://www.researchgate.net/publication/220494200_Adaptive_Thresholding_using_the_Integral_Image
void adaptative(SDL_Surface **base){
    SDL_Surface *src = *base;
    SDL_Surface *dst = SDL_CreateRGBSurface(SDL_SWSURFACE, src->w, src->h, 32, 0, 0, 0, 0);
    matrice *integral = matrice_new(src->w, src->h);
    

    for (int x = 0; x < src->w; x++){
        int sum = 0;
        for (int y = 0; y < src->h; y++){
            sum += getpixelgray(src, x, y);
            
            assert(sum > 0);
            
            if(x == 0){
                matrice_set(integral, x, y, (double) sum);
            }
            else {
                double upper = matrice_get(integral, x - 1, y);
                matrice_set(integral, x, y, upper + (double) sum);
            }
        }
    }
    

    for (int x = 0; x < src->w; x++){
        for (int y = 0; y < src->h; y++){
            int x1 = i
        }
    }
}


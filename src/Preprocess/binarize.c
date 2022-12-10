#include "binarize.h"

void binarize(SDL_Surface *base, int threshold) {
    Uint32 *pixels = base->pixels;
    size_t len = base->w * base->h;
    for (size_t i = 0; i < len; i++)
        pixels[i] = ((Uint8) pixels[i]) >= threshold ? 0 : 0xFFFFFF;
}

// algorithm from https://www.researchgate.net/publication/220494200_Adaptive_Thresholding_using_the_Integral_Image
void adaptative_binarize(SDL_Surface *base){
    const double t = 0.35;

    matrice *integral = matrice_new(base->w, base->h);

    int half_s = max(base->w, base->h) / 16;
    int count;
    unsigned int sum;
    

    for (int x = 0; x < base->w; x++){
        sum = 0;
        for (int y = 0; y < base->h; y++){
            sum += getpixelgray(base, x, y);
            
            if(x == 0){
                matrice_set(integral, x, y, (double) sum);
            }
            else {
                double right = matrice_get(integral, x - 1, y);
                matrice_set(integral, x, y, right + (double) sum);
            }
        }
    }
    

    for (int x = 0; x < base->w; x++){
        for (int y = 0; y < base->h; y++){
            int x1 = max(x - half_s, 1);
            int x2 = min(x + half_s, base->w - 1);
            int y1 = max(y - half_s, 1);
            int y2 = min(y + half_s, base->h - 1);

            count = (x2 - x1) * (y2 - y1);

            sum = matrice_get(integral, x2, y2) 
                - matrice_get(integral, x1, y2 - 1)
                - matrice_get(integral, x2 - 1, y1)
                + matrice_get(integral, x1, y1);

            int local_threshold = sum * (1.0 - t) / count;
            int pixel = getpixelgray(base, x, y);

            putpixel(base, x, y, pixel > local_threshold ? 0 : 0xFFFFFF);
        }
    }

    matrice_free(integral);
}

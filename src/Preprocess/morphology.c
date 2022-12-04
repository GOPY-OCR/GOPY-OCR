#include "morphology.h"
#define SIZE_SIDE_FILTER 20


Uint32 max_color_pixels(SDL_Surface *surface, int x, int y) {
    Uint32 *cur_max = getpixel(surface, x, y);
    if (cur_max == NULL)
        errx(1, "Preprocess - max_color_pixels: Can't find the given pixel");

    x -= SIZE_SIDE_FILTER / 2;
    y -= SIZE_SIDE_FILTER / 2;

    for (size_t i = 0; i < SIZE_SIDE_FILTER * SIZE_SIDE_FILTER; i++) {
        //if (FILTER[i] == 0)
        //    continue;

        Uint32 *cur = getpixel(surface, x + i % SIZE_SIDE_FILTER, 
                                            y + i / SIZE_SIDE_FILTER);
        if (cur != NULL && *cur > *cur_max)
            cur_max = cur;
    }

    return *cur_max;
}

Uint32 min_color_pixels(SDL_Surface *surface, int x, int y) {
    Uint32 *cur_min = getpixel(surface, x, y);
    if (cur_min == NULL)
        errx(1, "Preprocess - min_color_pixels: Can't find the given pixel");

    x -= SIZE_SIDE_FILTER / 2;
    y -= SIZE_SIDE_FILTER / 2;

    for (size_t i = 0; i < SIZE_SIDE_FILTER * SIZE_SIDE_FILTER; i++) {
        //if (FILTER[i] == 0)
        //    continue;

        Uint32 *cur = getpixel(surface, x + i % SIZE_SIDE_FILTER, 
                                            y + i / SIZE_SIDE_FILTER);
        if (cur != NULL && *cur < *cur_min)
            cur_min = cur;
    }

    return *cur_min;
}

SDL_Surface *dilation(SDL_Surface *base) {
    SDL_Surface *result = new_blank_surface(base);

    Uint32 *result_pixels = result->pixels;
    unsigned int len = base->w * base->h;

    for (size_t i = 0; i < len; i++) {
        result_pixels[i] = max_color_pixels(base,
                                            i % base->w,
                                            i / base->w);
    }

    return result;
}

SDL_Surface *erosion(SDL_Surface *base) {
    SDL_Surface *result = new_blank_surface(base);

    Uint32 *result_pixels = result->pixels;
    unsigned int len = base->w * base->h;

    for (size_t i = 0; i < len; i++) {
        result_pixels[i] = min_color_pixels(base,
                                            i % base->w,
                                            i / base->w);
    }

    return result;
}

SDL_Surface *closing(SDL_Surface *base) {
    SDL_Surface *dilated = dilation(base);
    SDL_Surface *erosed = erosion(dilated);
    SDL_FreeSurface(dilated);
    return erosed;
}

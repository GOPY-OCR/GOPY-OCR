#include "noise.h"

Uint8 *safe_get_pixel(SDL_Surface *surface, int x, int y) {
    if(x < 0 || x >= surface->w || y < 0 || y >= surface->h){
        return NULL;
    }

    int bpp = surface->format->BytesPerPixel; // = 4
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    return p;
}

Uint8 max_color_pixels(SDL_Surface *surface, int x, int y) {
    Uint8 cur_max = safe_get_pixel(surface, x, y);
    if (cur_max == NULL)
        errx(1, "Preprocess - max_color_pixels: Can't find the given pixel");

    x -= SIZE_SIDE_FILTER;
    y -= SIZE_SIDE_FILTER;

    for (size_t i; i < SIZE_SIDE_FILTER * SIZE_SIDE_FILTER; i++) {
        if (FILTER[i] == 0)
            continue;

        Uint8 cur = safe_get_pixel(surface, x + i % SIZE_SIDE_FILTER, 
                                            y + i / SIZE_SIDE_FILTER);
        if (cur != NULL && *cur > cur_max)
            cur_max = *cur;
    }

    return cur_max;
}

Uint8 min_color_pixels(SDL_Surface *surface, int x, int y) {
    Uint8 cur_min = safe_get_pixel(surface, x, y);
    if (cur_min == NULL)
        errx(1, "Preprocess - min_color_pixels: Can't find the given pixel");

    x -= SIZE_SIDE_FILTER;
    y -= SIZE_SIDE_FILTER;

    for (size_t i; i < SIZE_FILTER; i++) {
        if (FILTER[i] == 0)
            continue;

        Uint8 cur = safe_get_pixel(surface, x + i % SIZE_SIDE_FILTER, 
                                            y + i / SIZE_SIDE_FILTER);
        if (cur != NULL && *cur > cur_min)
            cur_min = *cur;
    }

    return cur_min;
}


#include "resize.h"

void resize(SDL_Surface **base, int new_size) {
    int width = new_size;
    int height = (float) new_size / (float) (*base)->w * (*base)->h;
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

void remove_black_borders(SDL_Surface **base) {
    int width = (*base)->w;
    int height = (*base)->h;
    SDL_Surface *src = *base;
    SDL_Surface *dest = SDL_CreateRGBSurface(
            src->flags,
            width,
            height,
            src->format->BitsPerPixel,
            src->format->Rmask,
            src->format->Gmask,
            src->format->Bmask,
            src->format->Amask
            );
    
    // yes, the coordinates are inverted
    // they are changed in the loop
    Point top_left = { src->w, src->h };
    Point bottom_right = { 0, 0 };

    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            if (is_pixel_white(src, x, y)) {
                if (x < top_left.x)
                    top_left.x = x;
                if (y < top_left.y)
                    top_left.y = y;
                if (x > bottom_right.x)
                    bottom_right.x = x;
                if (y > bottom_right.y)
                    bottom_right.y = y;
            }
        }
    }

    top_left.x = max(0, top_left.x - 1);
    top_left.y = max(0, top_left.y - 1);
    bottom_right.x = min(width - 1, bottom_right.x + 1);
    bottom_right.y = min(height - 1, bottom_right.y + 1);

    // make it a square
    int size = bottom_right.x - top_left.x;
    if (bottom_right.y - top_left.y > size)
        size = bottom_right.y - top_left.y;

    SDL_Rect drect = { top_left.x, top_left.y, size, size };

    if (SDL_BlitScaled(src, &drect, dest, NULL) != 0)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_FreeSurface(*base);
    *base = dest;
}

void neural_network_resize(SDL_Surface *splitted[81]) {
    SDL_Rect drect = { 0, 0, NN_SIZE, NN_SIZE };

    for (size_t i = 0; i < 81; i++) {
        // crop image, to fit digit
        remove_black_borders(&splitted[i]);


        SDL_Surface *dest = SDL_CreateRGBSurface(
                (splitted[i])->flags,
                NN_SIZE,
                NN_SIZE,
                (splitted[i])->format->BitsPerPixel,
                (splitted[i])->format->Rmask,
                (splitted[i])->format->Gmask,
                (splitted[i])->format->Bmask,
                (splitted[i])->format->Amask
                );

        if (SDL_BlitScaled(splitted[i], NULL, dest, &drect) != 0)
            errx(EXIT_FAILURE, "%s", SDL_GetError());
        
        SDL_FreeSurface(splitted[i]);
        splitted[i] = dest;
    }
}

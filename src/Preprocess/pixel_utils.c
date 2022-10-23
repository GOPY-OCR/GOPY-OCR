#include "pixel_utils.h"

// image should be locked
int is_pixel_white(SDL_Surface *image, int x, int y){
    Uint32 *pixel = getpixel(image, x, y);

    if(pixel == NULL){
        return 0;
    }

    Uint8 r, g, b;
    SDL_GetRGB(*pixel, image->format, &r, &g, &b);

    return !(r==0 && g==0 && b==0);
}

Uint32 *getpixel(SDL_Surface *surface, int x, int y){
    if(x < 0 || x >= surface->w || y < 0 || y >= surface->h){
        return NULL;
    }

    int bpp = surface->format->BytesPerPixel; // = 4
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    return p;
}

void putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel){
    Uint32 *target_pixel = getpixel(surface, x, y);
    *target_pixel = pixel;
}

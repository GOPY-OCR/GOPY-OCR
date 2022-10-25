#include "utils.h"

SDL_Surface *new_blank_surface(SDL_Surface *base) {
    SDL_Surface* dest_surface = SDL_CreateRGBSurface(
            base->flags,
            base->w,
            base->h,
            base->format->BitsPerPixel,
            base->format->Rmask,
            base->format->Gmask,
            base->format->Bmask,
            base->format->Amask
            );

    return dest_surface;
}

SDL_Surface* load_image(const char* path)
{
    SDL_Surface* s = IMG_Load(path);
    if (s == NULL)
        errx(EXIT_FAILURE, "%s", SDL_GetError());

    SDL_Surface *res = SDL_ConvertSurfaceFormat(s, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(s);

    return res;
}

void save_image(SDL_Surface *surface, const char *path) {
    IMG_SavePNG(surface, path);
}

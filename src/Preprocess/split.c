#include "split.h"

SDL_Surface* crop_surface(SDL_Surface* grid, int x, int y, 
                          int width, int height)
{
    SDL_Rect src_rect = {x, y, height, width};
    SDL_Surface* dest_surface = SDL_CreateRGBSurface(
            grid->flags,
            width,
            height,
            grid->format->BitsPerPixel,
            grid->format->Rmask,
            grid->format->Gmask,
            grid->format->Bmask,
            grid->format->Amask
            );

    SDL_BlitSurface(grid, &src_rect, dest_surface, NULL);

    return dest_surface;
}



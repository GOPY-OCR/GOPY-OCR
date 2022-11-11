#include "split.h"

SDL_Surface* crop_surface(SDL_Surface* grid, int x, int y, 
                          int width, int height)
{
    SDL_Rect src_rect = {x, y, width, height};
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

SDL_Surface **split_sudoku(SDL_Surface* grid)
{
    SDL_Surface *splitted = calloc(81, sizeof(SDL_Surface *));
    int h_step = grid->h / 9;
    int w_step = grid->w / 9;

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9;j++)
            splitted[i * 9 + j] = crop_surface(
                    grid, j * w_step, i * h_step, w_step, h_step);
}

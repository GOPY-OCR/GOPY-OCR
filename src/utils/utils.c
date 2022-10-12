#include "utils.h"

// Loads an image in a surface.
// The format of the surface is SDL_PIXELFORMAT_RGB888.
//
// path: Path of the image.
SDL_Surface *load_image(const char *path) {
    // !TODO
    SDL_Surface *surface = IMG_Load(path);
    SDL_Surface *converted =
        SDL_ConvertSurfaceFormat(surface, SDL_PIXELFORMAT_RGB888, 0);
    SDL_FreeSurface(surface);

    //     if (converted == NULL)
    //     errx(1, "Could not load the image: %s", IMG_GetError());

    return converted;
    return NULL;
}

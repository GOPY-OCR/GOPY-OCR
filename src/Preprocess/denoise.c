#include "denoise.h"

#define DENOISE_FF_CONNECTIVITY 2
#define DIGIT_WHITE_PIXELS_THRESHOLD 0.03

void clear_if_empty(SDL_Surface **surface) {
    // count white pixels
    int white_pixels = 0;
    int pixels = (*surface)->w * (*surface)->h;
    for (int i = 0; i < (*surface)->w; i++) {
        for (int j = 0; j < (*surface)->h; j++) {
            white_pixels += is_pixel_white(*surface, i, j);
        }
    }

    // if the number of white pixels is less than the threshold, clear the surface
    if (white_pixels < DIGIT_WHITE_PIXELS_THRESHOLD * pixels) {
        SDL_FreeSurface(*surface);
        *surface = SDL_CreateRGBSurface(0, 0, 0, 32, 0, 0, 0, 0);
    }
}

void neural_network_denoise(SDL_Surface **cells)
{
    for (int i = 0; i < 81; i++){
        SDL_Surface *denoised = extract_max_component(cells[i], DENOISE_FF_CONNECTIVITY, 0);
        SDL_FreeSurface(cells[i]);
        cells[i] = denoised;

        clear_if_empty(&cells[i]);
    }
}

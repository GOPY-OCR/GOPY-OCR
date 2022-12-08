#include "denoise.h"

void neural_network_denoise(SDL_Surface **cells)
{
    for (int i = 0; i < 81; i++){
        SDL_Surface *denoised = extract_max_component(cells[i], 1, 0);
        SDL_FreeSurface(cells[i]);
        cells[i] = denoised;
    }
}

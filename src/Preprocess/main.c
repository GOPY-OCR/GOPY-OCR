#include <SDL2/SDL.h>
#include "sdl_utils.h"
#include "hough_transform.h"
#include "flood_fill.h"
#include "debug_utils.h"
#include "grid_detection.h"
#include "perspective_correction.h"
#include "resize.h"
#include "brightness.h"
#include "split.h"

int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    resize(&image);

    printf("Correcting perspective...\n");

    SDL_Surface *corrected = perspective_correction(image, &grid);

    printf("Saving images...\n");

    save_image(image, "output.png");
    save_image(corrected, "corrected.png");

    SDL_Surface *splitted[81] = {NULL};
    split_sudoku(image, splitted);
    neural_network_resize(splitted);

    save_image(splitted[0], "test.png");

    for (size_t i = 0; i < 81; i++)
        SDL_FreeSurface(splitted[i]);
    SDL_FreeSurface(image);

    return 0; 
}

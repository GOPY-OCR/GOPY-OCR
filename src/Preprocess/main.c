#include "sdl_utils.h"
#include "hough_transform.h"
#include "flood_fill.h"
#include "debug_utils.h"
#include <SDL2/SDL.h>

int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    Quad grid = grid_detection(image, 1);

    save_image(image, "output.png");

    return 0; 
}

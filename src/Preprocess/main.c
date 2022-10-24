#include "utils.h"
#include "hough_transform.h"
#include "flood_fill.h"
#include <SDL2/SDL.h>


int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    int angle = detect_grid_rotation(image);
    printf("Detected angle: %d\n", angle);

    return 0; 
}

#include "utils.h"
#include "hough_transform.h"
#include "flood_fill.h"
#include <SDL2/SDL.h>


int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    Line *lines = find_image_lines(image, 15, 1);

    int angle = detect_grid_rotation(lines);

    printf("predicted angle: %d\n", angle);

    save_image(image, "output.png");

    return 0; 
}

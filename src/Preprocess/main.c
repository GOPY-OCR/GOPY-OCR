#include "grid_detection.h"
#include "utils.h"
#include <SDL2/SDL.h>


int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    SDL_Surface *principal_component = principal_component_analysis(image, 3);

    save_image(principal_component, "principal_component.png");

    return 0; 
}

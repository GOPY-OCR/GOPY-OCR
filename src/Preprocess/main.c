#include <SDL2/SDL.h>
#include "resize.h"

int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    SDL_Surface *test = new_blank_surface(image);
    save_image(test, "put.png");
    resize(&image);

    save_image(image, "output.png");

    SDL_FreeSurface(image);

    return 0; 
}

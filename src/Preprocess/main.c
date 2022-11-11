#include <SDL2/SDL.h>
#include "resize.h"
#include "brightness.h"

int main(int argc, char **argv) {
    SDL_Surface *image = load_image(argv[1]);

    resize(&image);

    save_image(image, "output.png");

    SDL_FreeSurface(image);

    return 0; 
}

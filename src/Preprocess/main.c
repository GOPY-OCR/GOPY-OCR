#include "preprocessors.h"

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <filename>", argv[0]);
    return EXIT_FAILURE;
  }

  SDL_Surface *image = load_image(argv[1]);

  return EXIT_SUCCESS;
}

#include "utils.h"

Test(utils, test_load_image) {
    for (int i = 1; i <= 6; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/cdc/%d.jpeg", i);
        SDL_Surface *im = load_image(filename);
        
        cr_assert(im != NULL, "Image %d is NULL", i);
    }

    for (int i = 1; i <= 2; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/binary/%d.png", i);
        SDL_Surface *im = load_image(filename);
        
        cr_assert(im != NULL, "Image %d is NULL", i);
    }
}

Test(utils, test_save_image) {
    for (int i = 1; i <= 6; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/cdc/%d.jpeg", i);
        SDL_Surface *im = load_image(filename);

        sprintf(filename, "../_build/tests/UtilsTests/TEST_utils_cdc_%d.png", i);

        save_image(im, filename);
    }

    for (int i = 1; i <= 2; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/binary/%d.png", i);
        SDL_Surface *im = load_image(filename);

        sprintf(filename, "../_build/tests/UtilsTests/TEST_utils_binary_%d.png", i);

        save_image(im, filename);

        cr_assert(load_image(filename) != NULL, "Failed to load previously saved image %s is NULL", filename);
    }
}

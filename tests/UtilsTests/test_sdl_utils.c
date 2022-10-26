#include "sdl_utils.h"

// there are 6 images, but only test with one because it takes too long
#define CDC_NUM_TESTS 1
#define BINARY_NUM_TESTS 1

Test(utils, test_load_image) {
    for (int i = 1; i <= CDC_NUM_TESTS; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/cdc/%d.png", i);
        SDL_Surface *im = load_image(filename);
        
        cr_assert(im != NULL, "Image %d is NULL", i);
    }

    for (int i = 1; i <= BINARY_NUM_TESTS; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/binary/%d.png", i);
        SDL_Surface *im = load_image(filename);
        
        cr_assert(im != NULL, "Image %d is NULL", i);
    }
}

Test(utils, test_save_image) {
    for (int i = 1; i <= CDC_NUM_TESTS; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/cdc/%d.png", i);
        SDL_Surface *im = load_image(filename);

        sprintf(filename, "../_build/tests/UtilsTests/TEST_utils_cdc_%d.png", i);

        save_image(im, filename);
    }

    for (int i = 1; i <= BINARY_NUM_TESTS; i++) {
        char *filename = calloc(100, sizeof(char));
        sprintf(filename, "images/binary/%d.png", i);
        SDL_Surface *im = load_image(filename);

        sprintf(filename, "../_build/tests/UtilsTests/TEST_utils_binary_%d.png", i);

        save_image(im, filename);

        cr_assert(load_image(filename) != NULL, "Failed to load previously saved image %s is NULL", filename);
    }
}

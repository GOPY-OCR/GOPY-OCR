#include "preprocess.h"

/* 
 * this function will execute the whole preprocess. 
 * It will execute the following steps:
 * 1.  Load the image as a SDL_Surface
 * 2.  Resize the image to speed up the next functions
 * 3.  Grayscale
 * 4.  Noise reduction + contrasts correction
 * 5.  Binarization
 * 6.  Automatic rotation
 * 7.  Grid detection
 * 8.  Perspective correction of the image
 * 9.  Split the image in 81 small images
 * 10. Resize the image to 28x28 for the neural network
 */
SDL_Surface **preprocess(const char *filename) {
    // 1.  Load the image as a SDL_Surface
    SDL_Surface *image = load_image(filename);

    // 2.  Resize the image to speed up the next functions
    resize(&image, NEW_SIZE);

    // 3.  Grayscale
    surface_to_grayscale(image);

    // 4.  Noise reduction + contrasts correction
    correct_brightness(image);

    // 5.  Binarization
    adaptative_binarize(image);

    // 6.  Automatic rotation
    automatic_rot(&image);

    // 7.  Grid detection
    Quad coords = grid_detection(image, 0, 1);

    // 8.  Perspective correction of the image
    perspective_correction(&image, &coords);

    // 9.  Split the image in 81 small images
    SDL_Surface **splitted = split_sudoku(image);

    // 10. Denoise neural network images
    denoise_cells(splitted);

    // 11. Resize the image to 28x28 for the neural network
    neural_network_resize(splitted);

    return splitted;
}


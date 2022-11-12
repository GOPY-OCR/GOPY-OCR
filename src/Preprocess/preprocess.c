#include "preprocess.h"

/* 
 * this function will execute the whole preprocess. 
 * It will execute the following steps:
 * 1.  Load the image as a SDL_Surface
 * 2.  Resize the image to speed up the next functions
 * 3.  Grayscale
 * 4.  Noise reduction + contrasts correction
 * 5.  Binarization
 * 6.  Interpolation des images pas droites
 * 7.  Grid detection
 * 8.  Automatic rotation
 * 9.  Crop the image
 * 10. Split the image in 81 small images
 * 11. Resize the image to 28x28 for the neural network
 */
SDL_Surface **preprocess(const char *filename) {
    // 1.  Load the image as a SDL_Surface
    SDL_Surface *image = load_image(filename);

    // 2.  Resize the image to speed up the next functions
    resize(&image);


    // 3.  Grayscale
    surface_to_grayscale(image);

    // 4.  Noise reduction + contrasts correction
    correct_brightness(image);

    // 5.  Binarization
    binarize(image);
    
    // 6.  Interpolation des images pas droites
    
    // 7.  Grid detection
    Quad coords = grid_detection(image, 0);
    
    // 8.  Automatic rotation
    automatic_rot(&image);
    
    // 9.  Crop the image
    
    // 10. Split the image in 81 small images
    SDL_Surface **splitted = split_sudoku(image);
    
    // 11. Resize the image to 28x28 for the neural network
    neural_network_resize(splitted);

    return splitted;
}


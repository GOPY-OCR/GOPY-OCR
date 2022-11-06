#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "grid_detection.h"
#include "array.h"
#include "matrice.h"
#include "maths.h"
#include "pixel_utils.h"
#include "point.h"
#include "geometry.h"
#include "debug_utils.h"


// Finds the lines in the image and returns
// the predicted angle of the grid based on 
// the median angle of the image lines
// Only work with angles between -45 and 45 degrees
//
// note: the returned angle is the inverse of the
//       angle of what we want to rotate the image
int detect_grid_rotation(Line *lines);


// Applies the Hough transform algorithm to the given image
//
// Parameters:
// - image: the source image
// - nb_lines: the number of lines to look for
// - draw_lines: if draw_lines is set, the source image will be modified
// 
// returns: a Rect containing the detected sudoku grid
Line *find_image_lines(SDL_Surface *image, int nb_lines, int draw_lines);


// Draws the hough transform space
// on a matrice
//
// returns: the accumulator matrix
matrice *create_hough_space_matrice(SDL_Surface *image, 
        array *thetas, 
        array *rhos, 
        float d,
        float drho);


// finds the top nb_lines peaks in the accumulator matrix.
// lines are represented by a point in the hough space
// Point->x is the rho index and Point->y is the theta index
//
// cancel_radius: the radius around a peak where other peaks will be cancelled
//                this is used to avoid detecting the same line multiple times
//
// returns: an array of points representing the lines
Point *find_peaks(matrice *accumulator, int nb_lines, int cancel_radius_rho, int cancel_radius_theta);


// Draws the lines found by the Hough transform
// on the given image
void draw_hough_lines_on_image(SDL_Surface *image, 
                               Point *lines, 
                               int nb_lines,
                               array *thetas, 
                               array *rhos, 
                               float d);


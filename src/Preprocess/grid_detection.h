#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"
#include "image_rotation.h"
#include "pixel_utils.h"
#include "geometry.h"
#include "hough_transform.h"
#include "flood_fill.h"
#include "array_sort.h"
#include "debug_utils.h"

// Detects the grid in the image
// The input image must be correctly rotated
Rect grid_detection(SDL_Surface *image, int draw_grid);

// Extracts the grid from the image
SDL_Surface *extract_grid(SDL_Surface *image, Point *intersections, int nb_intersections);

// calculates the areas of the rectangles
// and tries to find which one are part of the grid
// by looking for the median rectangle area, and 
// selecting the nb_rects closest to it that don't 
// overlap
Rect *filter_grid_rects(Rect *rects, int rects_count, int searched_rects_count);

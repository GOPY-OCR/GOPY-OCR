#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include "geometry.h"
#include "pixel_utils.h"
#include "matrice.h"

// this is called a bilinear quadrilateral transformation
SDL_Surface* perspective_correction(SDL_Surface *src, Quad *grid);

Point get_perspective_point(Point src, Quad *grid, int width, int height);

#include <SDL.h>
#include <SDL_image.h>
#include <assert.h>
#include "geometry.h"
#include "pixel_utils.h"

SDL_Surface* perspective_correction(SDL_Surface *src, Quad *grid);

Point get_perspective_point(Point src, Quad *grid, int width, int height);

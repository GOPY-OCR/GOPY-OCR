#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"


void grid_detection(SDL_Surface *image, int *x1, int *y1, int *x2, int *y2);

SDL_Surface *principal_component_analysis(SDL_Surface *image, int connectivity);
int is_connected(SDL_Surface *component, int x, int y, int connectivity);

int *project(SDL_Surface *image, int axis);

// aka écart type
float standard_deviation(int *xs, int size);

Uint32 *getpixel(SDL_Surface *surface, int x, int y);
int is_pixel_white(SDL_Surface *image, int x, int y);

// image: max convex component output
// returns the angle at which the image is rotated
// in degrees
int automatic_image_rotation(SDL_Surface *image);

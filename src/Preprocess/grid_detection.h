#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "utils.h"
#include "queue.h"


void grid_detection(SDL_Surface *image, int *x1, int *y1, int *x2, int *y2);

// Returns an image containing only
// the largest shape of connected pixels
// in the input image
#define MAX_COMPONENTS 100
SDL_Surface *principal_component_analysis(SDL_Surface *image, int connectivity);

// Returns true if the pixel at (x, y) is connected
// to a component via a path in the image
// 
// connectivity: number of pixels to check around the pixel
int is_connected(SDL_Surface *component, SDL_Surface *image, int x, int y, int connectivity);

int *project(SDL_Surface *image, int axis);

// aka écart type
float standard_deviation(int *xs, int size);

// returns a pointer to the pixel
// at (x, y) in the image surface
// or NULL if the pixel is out of bounds
Uint32 *getpixel(SDL_Surface *surface, int x, int y);
int is_pixel_white(SDL_Surface *image, int x, int y);

// image: max convex component output
// returns the angle at which the image is rotated
// in degrees
int automatic_image_rotation(SDL_Surface *image);

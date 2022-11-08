#include "rotation.h"

SDL_Surface *manual_rot(SDL_Surface* image, double angle)
{
    return rotozoomSurface(image, angle,1.0,1);
}

SDL_Surface *auto_rot(SDL_Surface *image) {
    double angle = grid_rotation_detection(image);
    return manual_rot(image, angle);
}

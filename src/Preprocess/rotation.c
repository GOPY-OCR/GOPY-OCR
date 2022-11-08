#include "rotation.h"

SDL_Surface *manual_rot(SDL_Surface* image, double angle)
{
    return rotozoomSurface(image, angle,1.0,1);


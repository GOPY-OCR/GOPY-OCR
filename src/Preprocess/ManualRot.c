#include "ManualRot.h"

SDL_Surface *SimpleRot(SDL_Surface* image, double angle)
{
    return rotozoomSurface(image, angle,1.0,1);
}

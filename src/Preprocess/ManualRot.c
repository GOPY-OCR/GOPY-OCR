#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>
void SimpleRot(SDL_Surface* image, double angle)
{
 rotozoomSurface(image, angle,1.0,1);
}

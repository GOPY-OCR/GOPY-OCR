#include <SDL2/SDL.h>
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include <SDL2/SDL_GFX.h>

SDL_Surface SimpleRot(SDL_Surface *image, double angle)
{
  SDL_Surface end = rotozoomSurface(*image, angle,1.0,1);
  return end;
}

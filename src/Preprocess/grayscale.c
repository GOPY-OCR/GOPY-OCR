#include <err.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat* format)
{
 Uint8 r, g, b;
 SDL_GetRGB(pixel_color, format, &r, &g, &b);
 Uint32 average = 0.3*r + 0.59*g + 0.11*b;
 r = average;
 g = average;
 b = average;
 Uint32 color = SDL_MapRGB(format,r,g,b);
 return color;
	 
}

void surface_to_grayscale(SDL_Surface* surface)
{
	Uint32* pixels = surface->pixels;
	int len = surface->w * surface->h;
	SDL_PixelFormat* format = surface->format;
	SDL_LockSurface(surface);
	for(int i; i<len; i++)
	{
		pixels[i] = pixel_to_grayscale(pixels[i],format);
	}
	SDL_UnlockSurface(surface);
}



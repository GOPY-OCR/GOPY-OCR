#include "preprocessors.h"


// Saves an image to a file.
//
// path: Path of the image.
// surface: Surface to save.
void save_image(const char *path, SDL_Surface *surface) {
  // !TODO
}

// Converts a colored pixel into grayscale.
//
// pixel_color: Color of the pixel to convert in the RGB format.
// format: Format of the pixel used by the surface.
Uint32 pixel_to_grayscale(Uint32 pixel_color, SDL_PixelFormat *format) {
  // !TODO
  //  Uint8 r, g, b;
  //  SDL_GetRGB(pixel_color, format, &r, &g, &b);
  //
  //  Uint32 average = 0.3 * r + 0.59 * g + 0.11 * b;
  //
  //  r = average;
  //  g = average;
  //  b = average;
  //
  //  return SDL_MapRGB(format, r, g, b);
  return 0;
}

void surface_to_grayscale(SDL_Surface *surface) {
  // !TODO
  //  Uint32 *pixels = surface->pixels;
  //  int len = surface->w * surface->h;
  //  SDL_PixelFormat *format = surface->format;
  //
  //  SDL_LockSurface(surface);
  //
  //  for (int i = 0; i < len; i++)
  //    pixels[i] = pixel_to_grayscale(pixels[i], format);
  //
  //  SDL_UnlockSurface(surface);
}

// Rotates a surface by given angle.
//
// surface: Surface to rotate.
// angle: Angle of rotation in degrees.
void surface_rotate(SDL_Surface *surface, int angle) {

  // !TODO
}

// Flips a surface
// surface: Surface to flip.
// flip: Flip mode.
void surface_flip(SDL_Surface *surface, int flip_mode) {

  // !TODO
}

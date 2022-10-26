#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "point.h"
#include "pixel_utils.h"

#define DEBUG_SDL_COLOR (SDL_Color){255, 0, 0, 255}

void draw_line_width(SDL_Surface *image, Line line, SDL_Color color, int width);
void draw_line(SDL_Surface *image, Line line, SDL_Color color);

void draw_rect(SDL_Surface *image, Rect rect, SDL_Color color);

void draw_quad(SDL_Surface *image, Quad quad, SDL_Color color, int line_width);

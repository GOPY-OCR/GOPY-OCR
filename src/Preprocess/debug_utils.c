#include "debug_utils.h"


void draw_line(SDL_Surface *image, Line line, SDL_Color color){
    // algorithm found on https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
    int dx = abs(line.p2.x - line.p1.x);
    int sx = line.p1.x < line.p2.x ? 1 : -1;
    int dy = -abs(line.p2.y - line.p1.y);
    int sy = line.p1.y < line.p2.y ? 1 : -1;
    int err = dx + dy;
    int e2;
    Uint32 pixel = SDL_MapRGBA(image->format, color.r, color.g, color.b, color.a);

    while (!(line.p1.x == line.p2.x && line.p1.y == line.p2.y)){
        if (line.p1.x >= 0 && line.p1.x < image->w && line.p1.y >= 0 && line.p1.y < image->h){
            putpixel(image, line.p1.x, line.p1.y, pixel);
        }
        e2 = 2 * err;
        if (e2 >= dy){
            err += dy;
            line.p1.x += sx;
        }
        if (e2 <= dx){
            err += dx;
            line.p1.y += sy;
        }
    }
    // modified the algorithm a bit to not have a while(1) loop
    // and instead draw the last pixel outside the loop
    if (line.p1.x >= 0 && line.p1.x < image->w && line.p1.y >= 0 && line.p1.y < image->h){
        putpixel(image, line.p1.x, line.p1.y, pixel);
    }
}

void draw_rect(SDL_Surface *image, Rect rect, SDL_Color color){
    draw_line(image, (Line){rect.p1, (Point){rect.p2.x, rect.p1.y}}, color);
    draw_line(image, (Line){rect.p1, (Point){rect.p1.x, rect.p2.y}}, color);
    draw_line(image, (Line){rect.p2, (Point){rect.p2.x, rect.p1.y}}, color);
    draw_line(image, (Line){rect.p2, (Point){rect.p1.x, rect.p2.y}}, color);
}

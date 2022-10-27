#include "flood_fill.h"

#define INITIAL_FILL_CAPACITY 1000
int flood_fill(SDL_Surface *image, Point point, Uint32 color, int cancel_fill, SDL_Surface *dest) {
    queue *q = queue_create();  // queue of points
    int filled = 0;             // number of pixels filled

    int fill_capacity = INITIAL_FILL_CAPACITY;
    // this array is used to keep track of which pixels have been filled
    Uint32 **filled_pixels = malloc(sizeof(Uint32 *) * fill_capacity);
    
    // copy the given point, because it will be detroyed after
    Point *p = malloc(sizeof(Point));  
    *p = (Point) {point.x, point.y}; 
    queue_enqueue(q, p);

    SDL_LockSurface(image);
    if (dest != NULL) {
        SDL_LockSurface(dest);
    }

    int cr, cg, cb;
    SDL_GetRGB(color, image->format, &cr, &cg, &cb);
    int is_color_white = cr > 128 && cg > 128 && cb > 128;
    
    while(!queue_is_empty(q)) {
        Point *p = queue_dequeue(q);
        int inbounds = p->x >= 0 && p->x < image->w && p->y >= 0 && p->y < image->h;
        if (inbounds && is_pixel_white(image, p->x, p->y) != is_color_white) {
            Uint32 *pixel = getpixel(image, p->x, p->y);
            if (filled == fill_capacity) {
                fill_capacity *= 2;
                filled_pixels = realloc(filled_pixels, sizeof(Uint32 *) * fill_capacity);
            }
            if (dest != NULL) {
                putpixel(dest, p->x, p->y, *pixel);
            }

            filled_pixels[filled] = pixel;
            *pixel = color;
            filled++;

            Point *p1 = malloc(sizeof(Point));
            *p1 = (Point){p->x + 1, p->y};
            queue_enqueue(q, p1);

            Point *p2 = malloc(sizeof(Point));
            *p2 = (Point){p->x - 1, p->y};
            queue_enqueue(q, p2);

            Point *p3 = malloc(sizeof(Point));
            *p3 = (Point){p->x, p->y + 1};
            queue_enqueue(q, p3);

            Point *p4 = malloc(sizeof(Point));
            *p4 = (Point){p->x, p->y - 1};
            queue_enqueue(q, p4);
        }
        free(p);
    }

    SDL_UnlockSurface(image);
    if (dest != NULL) {
        SDL_UnlockSurface(dest);
    }

    // white if black, black if white
    Uint32 inverse_color = color == SDL_MapRGB(image->format, 0, 0, 0) ? 
        SDL_MapRGB(image->format, 255, 255, 255) : SDL_MapRGB(image->format, 0, 0, 0);


    if (cancel_fill) {
        for (int i = 0; i < filled; i++) {
            *filled_pixels[i] = inverse_color;
        }
    }

    queue_free(q);
    free(filled_pixels);

    return filled;
}

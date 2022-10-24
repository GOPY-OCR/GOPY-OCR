#include "flood_fill.h"

int flood_fill(SDL_Surface *image, Point point, Uint32 color) {
    queue *q = queue_create();  // queue of points
    int filled = 0;             // number of pixels filled
    
    // copy the given point, because it will be detroyed after
    Point *p = malloc(sizeof(Point));  
    *p = (Point) {point.x, point.y}; 
    queue_enqueue(q, p);
    
    while(!queue_is_empty(q)) {
        Point *p = queue_dequeue(q);
        int inbounds = p->x >= 0 && p->x < image->w && p->y >= 0 && p->y < image->h;
        if (inbounds && *getpixel(image, p->x, p->y) != color) {
            putpixel(image, p->x, p->y, color);
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

    queue_free(q);

    return filled;
}

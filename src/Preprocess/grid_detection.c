#include "grid_detection.h"

// number of lines to detect
#define NB_LINES 20
#define NB_GRID_RECTANGLES 81
Rect grid_detection(SDL_Surface *image, int draw_grid){
    Line *image_lines = find_image_lines(image, NB_LINES, 1);
    return;

    int formed_rects_count = 0;
    Rect *formed_rects = find_rects(image_lines, NB_LINES, &formed_rects_count);

    Rect *grid_rects = filter_grid_rects(formed_rects, formed_rects_count, NB_GRID_RECTANGLES);

    if (draw_grid)
        for (int i = 0; i < NB_GRID_RECTANGLES; i++)
            draw_rect(image, grid_rects[i], DEBUG_SDL_COLOR);

    // the grid rectangle goes from the top left of the first rectangle to the bottom right of the last rectangle
    Rect grid_rect = (Rect){
        (Point){grid_rects[0].p1.x, grid_rects[0].p1.y},
        (Point){grid_rects[NB_GRID_RECTANGLES - 1].p2.x, grid_rects[NB_GRID_RECTANGLES - 1].p2.y}};

    grid_rect = (Rect){(Point){0, 0}, (Point){image->w, image->h}}; // temp

    free(formed_rects);
    //free(grid_rects);

    return grid_rect;
}

int compare_rects_area(const void *a, const void *b){
    Rect *rect_a = (Rect *)a;
    Rect *rect_b = (Rect *)b;

    int area_a = Rect_Area(*rect_a);
    int area_b = Rect_Area(*rect_b);

    return area_a - area_b;
}

#define MAX_SQUARE_RATIO 1.5
Rect *filter_grid_rects(Rect *rects, int rects_count, int searched_rects_count){
    Rect *sorted_rects = malloc(sizeof(Rect) * rects_count);
    memcpy(sorted_rects, rects, sizeof(Rect) * rects_count);

    // sort the rectangles by their area
    qsort(sorted_rects, rects_count, sizeof(Rect), compare_rects_area);

    // filter out non square rectangles
    Rect *squares = malloc(sizeof(Rect) * rects_count);
    int squares_count = 0;
    for (int i = 0; i < rects_count; i++)
    {
        Rect rect = sorted_rects[i];
        float ratio = (float)(rect.p2.x - rect.p1.x) / (float)(rect.p2.y - rect.p1.y);
        if (ratio < MAX_SQUARE_RATIO && ratio > 1 / MAX_SQUARE_RATIO)
        {
            squares[squares_count] = rect;
            squares_count++;
        }
    }

    // filter out colliding rectangles
    Rect *filtered_rects = malloc(sizeof(Rect) * squares_count);
    int filtered_rects_count = 0;
    for (int i = 0; i < squares_count; i++)
    {
        Rect rect = squares[i];
        int collides = 0;
        for (int j = 0; j < filtered_rects_count; j++)
        {
            if (rect.p1.x >= filtered_rects[j].p1.x && rect.p1.x <= filtered_rects[j].p2.x &&
                rect.p1.y >= filtered_rects[j].p1.y && rect.p1.y <= filtered_rects[j].p2.y)
            {
                collides = 1;
                break;
            }
        }
        if (!collides)
        {
            filtered_rects[filtered_rects_count] = rect;
            filtered_rects_count++;
        }
    }

    return filtered_rects + (filtered_rects_count - searched_rects_count);
}

#include "grid_detection.h"

#define GRID_FLOOD_FILL_CONNECTIVITY 2

Quad grid_detection(SDL_Surface *image, int draw_grid, int remove_grid) {
    SDL_Surface *extracted_grid = extract_max_component(image, GRID_FLOOD_FILL_CONNECTIVITY, remove_grid);

    Quad grid_quad = find_white_coners(extracted_grid);

    if(draw_grid){
        draw_quad(image, grid_quad, DEBUG_SDL_COLOR, 3);
    }

    SDL_FreeSurface(extracted_grid);

    return grid_quad;
}

int grid_rotation_detection(SDL_Surface *image){
    SDL_Surface *extracted_grid = extract_max_component(image, 2, 0);

    Line *image_lines = find_image_lines(extracted_grid, 10, 0);

    int rotation = detect_grid_rotation(image_lines);

    return -rotation;
}


Quad find_white_coners(SDL_Surface *extracted_grid){
    Quad result = (Quad) {(Point) {0, 0}, (Point) {0, 0}, (Point) {0, 0}, (Point) {0, 0}};

    SDL_LockSurface(extracted_grid);

    for (int y = 0; y < extracted_grid->h; y++){
        for (int x = 0; x < extracted_grid->w; x++){
            if (is_pixel_white(extracted_grid, x, y)){
                if (result.p1.x == 0 || x < result.p1.x - (y - result.p1.y)){
                    result.p1.x = x;
                    result.p1.y = y;
                }

                if (result.p2.x == 0 || x > result.p2.x + (y - result.p2.y)){
                    result.p2.x = x;
                    result.p2.y = y;
                }

                if (y > result.p3.y + (x - result.p3.x)){
                    result.p3.x = x;
                    result.p3.y = y;
                }

                if (y > result.p4.y - (x - result.p4.x)){
                    result.p4.x = x;
                    result.p4.y = y;
                }
            }
        }
    }

    SDL_UnlockSurface(extracted_grid);

    return result;
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
        double ratio = (double)(rect.p2.x - rect.p1.x) / (double)(rect.p2.y - rect.p1.y);
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

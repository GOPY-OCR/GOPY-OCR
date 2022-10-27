#include "grid_detection.h"

Quad grid_detection(SDL_Surface *image, int draw_grid){
    SDL_Surface *extracted_grid = extract_grid(image);

    Quad grid_quad = find_white_coners(extracted_grid);

    if(draw_grid){
        draw_quad(image, grid_quad, DEBUG_SDL_COLOR, 3);
    }

    return grid_quad;
}

int grid_rotation_detection(SDL_Surface *image){
    SDL_Surface *extracted_grid = extract_grid(image);

    Line *image_lines = find_image_lines(extracted_grid, 10, 0);

    int rotation = detect_grid_rotation(image_lines);

    return rotation;
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


SDL_Surface *extract_grid(SDL_Surface *image){
    int areas_capacity = 100;
    int *areas = malloc(sizeof(int) * areas_capacity);
    Point *areas_origin = malloc(sizeof(Point) * areas_capacity);
    int nb_areas = 0;


    Uint32 black = SDL_MapRGB(image->format, 0, 0, 0);
    
    SDL_Surface *copy = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(image, NULL, copy, NULL);

    for (int x = 0; x < image->w; x++) {
        for (int y = 0; y < image->h; y++) {
            if (!is_pixel_white(copy, x, y)) {
                continue;
            }

            if (nb_areas == areas_capacity) {
                areas_capacity *= 2;
                areas = realloc(areas, sizeof(int) * areas_capacity);
                areas_origin = realloc(areas_origin, sizeof(Point) * areas_capacity);
            }

            areas_origin[nb_areas] = (Point) {x, y};
            areas[nb_areas] = flood_fill(copy, areas_origin[nb_areas], black, 0, NULL);
            nb_areas++;
        }
    }

    SDL_FreeSurface(copy);

    int max_area_index = 0;
    for (int i = 0; i < nb_areas; i++) {
        if (areas[i] > areas[max_area_index]) {
            max_area_index = i;
        }
    }

    SDL_Surface *extracted_grid = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);

    // where we found the largest white connected area,
    // we copy it to a new surface
    flood_fill(image, areas_origin[max_area_index], black, 1, extracted_grid);

    free(areas);
    free(areas_origin);

    return extracted_grid;
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

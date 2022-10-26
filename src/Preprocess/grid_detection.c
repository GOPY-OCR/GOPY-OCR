#include "grid_detection.h"

// number of lines to detect
#define NB_LINES 20
#define NB_GRID_RECTANGLES 81
Rect grid_detection(SDL_Surface *image, int draw_grid){
    Line *image_lines = find_image_lines(image, NB_LINES, 0);
    int nb_intersections = 0;
    Point *intersections = find_intersections(image_lines, NB_LINES, &nb_intersections);

    SDL_Surface *extracted_grid = extract_grid(image);

    save_image(extracted_grid, "extracted_grid.png");

    Rect grid_rect = (Rect) {(Point) {0, 0}, (Point) {0, 0}};
    return grid_rect;
}


int grid_rotation_detection(SDL_Surface *image){
    SDL_Surface *extracted_grid = extract_grid(image);

    Line *image_lines = find_image_lines(extracted_grid, 10, 0);

    int rotation = detect_grid_rotation(image_lines);

    return rotation;
}

SDL_Surface *extract_grid(SDL_Surface *image){
    int areas_capacity = 100;
    int *areas = malloc(sizeof(int) * areas_capacity);
    Point *areas_origin = malloc(sizeof(Point) * areas_capacity);
    size_t nb_areas = 0;


    Uint32 black = SDL_MapRGB(image->format, 0, 0, 0);
    
    SDL_Surface *copy = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);
    SDL_BlitSurface(image, NULL, copy, NULL);

    for (size_t x = 0; x < image->w; x++) {
        for (size_t y = 0; y < image->h; y++) {
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

    size_t max_area_index = 0;
    for (size_t i = 0; i < nb_areas; i++) {
        if (areas[i] > areas[max_area_index]) {
            max_area_index = i;
        }
    }

    SDL_Surface *extracted_grid = SDL_CreateRGBSurface(0, image->w, image->h, 32, 0, 0, 0, 0);

    // where we found the largest white connected area,
    // we copy it to a new surface
    flood_fill(image, areas_origin[max_area_index], black, 0, extracted_grid);

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

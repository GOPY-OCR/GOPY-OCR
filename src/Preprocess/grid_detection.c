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

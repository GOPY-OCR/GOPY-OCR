#include "max_component.h"

SDL_Surface *extract_max_component(SDL_Surface *image, int flood_fill_connectivity, int remove){
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
            areas[nb_areas] = flood_fill(copy, areas_origin[nb_areas], black, 0, NULL, flood_fill_connectivity);
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
    flood_fill(image, areas_origin[max_area_index], black, !remove, extracted_grid, flood_fill_connectivity);

    free(areas);
    free(areas_origin);

    return extracted_grid;
}

#include "grid_detection.h"
#include "utils.h"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <criterion/parameterized.h>
#include <criterion/new/assert.h>

struct grid_detection_params {
    char *input_file;
    int x1lower, x1upper, y1lower, y1upper;
    int x2lower, x2upper, y2lower, y2upper;
};

char *cr_strdup(const char *str){
    char *ptr = cr_malloc(strlen(str) + 1);
    if (ptr)
        strcpy(ptr, str);
    return ptr;
}

ParameterizedTestParameters(grid_detection, test_grid_detection) {
    const size_t nb_samples = 2;
    struct grid_detection_params *params = cr_malloc(sizeof(struct grid_detection_params) * nb_samples);

    params[0] = (struct grid_detection_params) {
        .input_file = cr_strdup("images/binary/1.png"),
        .x1lower = 59, .x1upper = 90,
        .y1lower = 71, .y1upper = 103,
        .x2lower = 503, .x2upper = 535,
        .y2lower = 504, .y2upper = 536,
    };

    params[1] = (struct grid_detection_params) {
        .input_file = cr_strdup("images/binary/2.png"),
        .x1lower = 46, .x1upper = 66,
        .y1lower = 55, .y1upper = 75,
        .x2lower = 379, .x2upper = 399,
        .y2lower = 380, .y2upper = 400,
    };
    

    return cr_make_param_array(struct grid_detection_params, params, nb_samples);
}

ParameterizedTest(struct grid_detection_params *params, grid_detection, test_grid_detection) {
    SDL_Surface *image = load_image(params->input_file);

    int x1, y1, x2, y2;
    grid_detection(image, &x1, &y1, &x2, &y2);

    cr_assert(
            x1 >= params->x1lower && 
            x1 <= params->x1upper && 
            y1 >= params->y1lower && 
            y1 <= params->y1upper, 
            "first grid corner is missplaced on image %s", params->input_file);

    cr_assert(
            x2 >= params->x2lower && 
            x2 <= params->x2upper && 
            y2 >= params->y2lower && 
            y2 <= params->y2upper, 
            "second grid corner is missplaced on image %s", params->input_file);
}

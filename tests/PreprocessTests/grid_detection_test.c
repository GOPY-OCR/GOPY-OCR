#include "grid_detection.h"
#include "utils.h"
#include "point.h"
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

    Rect predicted_rect = grid_detection(image, 0);

    cr_assert(
            predicted_rect.p1.x >= params->x1lower &&
            predicted_rect.p1.x <= params->x1upper &&
            predicted_rect.p1.y >= params->y1lower &&
            predicted_rect.p1.y <= params->y1upper,
            "first grid corner is missplaced on image %s", params->input_file);

    cr_assert(
            predicted_rect.p2.x >= params->x2lower &&
            predicted_rect.p2.x <= params->x2upper &&
            predicted_rect.p2.y >= params->y2lower &&
            predicted_rect.p2.y <= params->y2upper,
            "second grid corner is missplaced on image %s", params->input_file);
}

SDL_Surface *binary1, *binary2;
void setup() {
    binary1 = load_image("images/binary/1.png");
    binary2 = load_image("images/binary/2.png");
}


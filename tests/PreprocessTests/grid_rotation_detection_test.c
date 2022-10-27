#include "hough_transform.h"
#include "maths.h"
#include <criterion/parameterized.h>

#define ANGLE_RANGE 40
#define ANGLE_STEP 10
#define MAXIMUM_OFFSET 3
struct grid_rotation_detection_params {
    int angle;
    char *filename;
};

#define GRID_ROTATION_TEST_CASES 24
ParameterizedTestParameters(grid_detection, grid_rotation_test){
    struct grid_rotation_detection_params *params = cr_malloc(sizeof(struct grid_rotation_detection_params) * GRID_ROTATION_TEST_CASES);
    
    const int nb_files = 3;
    const char filenames[] = "images/binary/%d_rotated(%d).png";
    int test_num = 0;
    
    for(int i = 1; i <= nb_files; i++){
        for(int angle = -ANGLE_RANGE; angle <= ANGLE_RANGE; angle+= ANGLE_STEP){
            if (angle == 0) continue;

            if (test_num >= GRID_ROTATION_TEST_CASES) break;

            char *filename = cr_malloc(sizeof(char) * 200);
            sprintf(filename, filenames, i, angle);

            params[test_num].filename = filename;
            params[test_num].angle = angle;
            test_num++;
        }
    }

    return cr_make_param_array(struct grid_rotation_detection_params, params, GRID_ROTATION_TEST_CASES);
}


ParameterizedTest(struct grid_rotation_detection_params *params, grid_detection, grid_rotation_test){
    SDL_Surface* image = load_image(params->filename);
    Line *lines = find_image_lines(image, 15, 0);
    int angle_detected = detect_grid_rotation(lines);
    int angle_expected = params->angle;

    int offset = intabs(angle_detected - angle_expected);

    cr_assert(offset <= MAXIMUM_OFFSET, 
            "Failed to detect grid rotation for image %s. Angle detected: %d, angle expected: %d, offset: %d",
            params->filename, angle_detected, angle_expected, offset);

    SDL_FreeSurface(image);
}

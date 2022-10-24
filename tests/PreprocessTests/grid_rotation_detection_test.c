#include "hough_transform.h"
#include "maths.h"

#define ANGLE_RANGE 40
#define ANGLE_STEP 10
#define MAXIMUM_OFFSET 3
#define TEST_NUM_LIMIT 4 // we have 24 test cases, but it takes too long to run all of them
Test(grid_detection, grid_rotation_test){
    // TODO: transform this to a parameterized test case (they will run in parallel) and run all 24 test cases
    int nb_files = 3;
    char filenames[] = "images/binary/%d_rotated(%d).png";
    int test_num = 0;
        
    for(int i = 1; i <= nb_files; i++){
        for(int angle = -ANGLE_RANGE; angle <= ANGLE_RANGE; angle+= ANGLE_STEP){
            if (angle == 0) continue;

            if(test_num++ > TEST_NUM_LIMIT) break;

            char filename[100];
            sprintf(filename, filenames, i, angle);
            SDL_Surface* image = load_image(filename);

            int angle_detected = detect_grid_rotation(image);
            int angle_expected = angle;

            int offset = intabs(angle_detected - angle_expected);

            cr_assert(offset <= MAXIMUM_OFFSET, "Angle detected: %d, angle expected: %d, offset: %d", 
                    angle_detected, angle_expected, offset);

            SDL_FreeSurface(image);
        }
    }
}

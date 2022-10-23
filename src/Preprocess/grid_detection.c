#include "grid_detection.h"

void grid_detection(SDL_Surface *image, int *x1, int *y1, int *x2, int *y2){
    *x1 = 0;
    *y1 = 0;
    *x2 = 0;
    *y2 = 0;

    int angle = automatic_image_rotation(image);

    //SDL_Surface *rotated_image = image_rotate(max_component, angle);
}

int *project(SDL_Surface *image, int axis){
    int size = axis == 0 ? image->w : image->h;

    int *projection = malloc(size * sizeof(int));

    for(int i = 0; i < size; i++){
        projection[i] = 0;
    }

    for(int i = 0; i < image->w; i++){
        for(int j = 0; j < image->h; j++){
            if(is_pixel_white(image, i, j)){
                projection[axis == 0 ? i : j]++;
            }
        }
    }

    return projection;
}

#define STEP_SIZE 1 // 1° steps
#define MAX_ANGLE 45 // 45° maximum angle
#define STEP_COUNT (MAX_ANGLE / STEP_SIZE)
int automatic_image_rotation(SDL_Surface *image){
    int angle = 0;
    float angle_score = evaluate_rotation(image, angle);
    float new_score;
    for(int i = 0; i < STEP_COUNT; i++){
        if((new_score = 
                evaluate_rotation(image, angle + STEP_SIZE)) > angle_score){

            angle_score = new_score;
            angle += STEP_SIZE;
        }
        else if((new_score = 
                    evaluate_rotation(image, angle - STEP_SIZE)) > angle_score){
            angle_score = new_score;
            angle -= STEP_SIZE;
        }
        else{
            break;
        }
    }

    return angle;
}

// higher values are better, it means that the grid lines
// are aligned with the x and y axis
float evaluate_rotation(SDL_Surface *image, int angle){
    //SDL_Surface *rotated_image = image_rotate(image, angle);
    SDL_Surface *rotated_image = image;

    int *projection_x = project(rotated_image, 0);
    int *projection_y = project(rotated_image, 1);

    float std_x = standard_deviation(projection_x, rotated_image->w);
    float std_y = standard_deviation(projection_y, rotated_image->h);

    free(projection_x);
    free(projection_y);
    SDL_FreeSurface(rotated_image);

    return std_x + std_y;
}


float floatabs(float x){return x > 0? x : -x;}

float standard_deviation(int *xs, int size){
    if (size < 2) return 0;

    float mean = 0;

    for (int i = 0; i < size; i++){
        mean += xs[i];
    }

    mean /= size;

    float deviation_sum = 0;

    for (int i = 0; i < size; i++){
        deviation_sum += floatabs(xs[i] - mean);
    }

    return deviation_sum / size;
}

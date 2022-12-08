#ifndef ANIMA_STEPS_H
#define ANIMA_STEPS_H
#include <stdio.h>
#include <stdlib.h>

#define NB_STEPS 10
#define NB_PRE_STEPS 8
typedef Anima_Steps {
    int nb_steps; // 11 for now
    int nb_pre_steps; // 
    int cur_step; // 0-7 for preprocess steps
                  // 8 for detected grid
                  // 9 for postprocess step
    SDL_Surface **preprocess_states; // 8 Steps (grid_detection with red lines +
                                     // no splitted grid bc it is useless)
    int *detected;
    int *solved;
    SDL_Surface *post;
} Anima_Steps;

#endif



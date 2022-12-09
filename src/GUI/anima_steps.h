#ifndef ANIMA_STEPS_H
#define ANIMA_STEPS_H
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>

#define NB_STEPS 9
typedef struct Anima_Steps {
    int nb_steps;
    int cur_step; // 0-7 for preprocess steps
                  // 8 for detected grid
                  // 9 for postprocess step
    SDL_Surface **steps; 
    int *detected;
    int *solved;
} Anima_Steps;

#endif



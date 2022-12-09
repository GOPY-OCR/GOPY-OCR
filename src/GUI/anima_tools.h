#ifndef ANIMA_TOOLS_H
#define ANIMA_TOOLS_H
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "../Preprocess/preprocess.h"
#include "../NeuralNetwork/neural_network.h"
#include "../Solver/grid.h"
#include "../Solver/solver.h"
#include "../Postprocess/postprocess.h"
#include "sdl_utils.h"
#include "glob_struct.h"
#include "anima_steps.h"
#include "gui-utils.h"

void dialog_error(GtkWindow *window, GtkMessageType type, char *msg);
void gtk_image_set_from_sdl_surface(GtkImage *image, SDL_Surface *surface);
SDL_Surface *copy_surface(SDL_Surface *base);
void compute_all_steps(Glob_GUI *glob);

#endif



#pragma once
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "../Preprocess/preprocess.h"
#include "../NeuralNetwork/neural_network.h"
#include "../Solver/grid.h"
#include "../Solver/solver.h"
#include "sdl_utils.h"
#include "glob_struct.h"
#include "gui-utils.h"

void anima_init(Glob_GUI *glob);
G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data);
G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data);
void gtk_image_set_from_sdl_surface(GtkImage *image, SDL_Surface *surface);
void update_image(GtkImage *image, SDL_Surface *new_surface);
G_MODULE_EXPORT void on_StartButton_clicked(GtkButton *button, gpointer user_data);


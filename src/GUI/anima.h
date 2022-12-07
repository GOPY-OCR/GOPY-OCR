#pragma once
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "sdl_utils.h"
#include "glob_struct.h"
#include "gui-utils.h"
#include "../Preprocess/preprocess.c"
#include "../Solver/solver.c"
#include "../Postprocess/postprocess.c"

void anima_init(Glob_GUI *glob);
G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data);
G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data);
GtkWidget *gtk_image_new_from_sdl_surface(SDL_Surface *surface);
void update_image(GtkImage *image, SDL_Surface *new_surface);
G_MODULE_EXPORT void on_StartButton_clicked(GtkButton *button, gpointer user_data);


#pragma once
#include <gtk/gtk.h>
#include "glob_struct.h"
#include "gui-utils.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
void anima_init(Glob_GUI *glob);
G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data);
G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data);


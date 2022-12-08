#pragma once
#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string.h>
#include "sdl_utils.h"
#include "glob_struct.h"
#include "anima_steps.h"
#include "anima_tools.h"
#include "gui-utils.h"

void anima_init(Glob_GUI *glob);
G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data);
G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data);


#pragma once
#include "pages.h"
#include "glob_struct.h"

void page_1_init(Glob_GUI *glob);

G_MODULE_EXPORT void on_CancelButton1_clicked(GtkButton *button, gpointer user_data);
G_MODULE_EXPORT void on_Continue1_clicked(GtkButton *button, gpointer user_data);

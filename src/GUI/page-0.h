#pragma once
#include "pages.h"
#include "gui-utils.h"
#include "glob_struct.h"

void page_0_init(Glob_GUI *glob);

G_MODULE_EXPORT void on_ButtonLoad_clicked(GtkButton *Button, gpointer user_data);

void clear_image(Glob_GUI *glob);

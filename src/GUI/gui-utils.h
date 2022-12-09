#pragma once
#include <gtk/gtk.h>
#include "glob_struct.h"

void init_gui_utils(Glob_GUI *glob);
void switch_page(Glob_GUI *glob, int page);
void next_page(Glob_GUI *glob);
void prev_page(Glob_GUI *glob);

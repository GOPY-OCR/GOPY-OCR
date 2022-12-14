#pragma once
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <gtk/gtk.h>
#include <math.h>
#include <ctype.h>
#include "sdl_utils.h"
#include "gui-utils.h"
#include "pages.h"
#include "glob_struct.h"

#define GUI_GLADE "assets/GUI/GUI-project.glade"

int GUI(int argc, char* argv[]);

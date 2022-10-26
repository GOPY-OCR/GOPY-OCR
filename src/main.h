#ifndef MAIN_H
#define MAIN_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <err.h>
#include "sdl_utils.h"

// Grayscale part
#include "Preprocess/grayscale.h"

// Binarization part
#include "Preprocess/binarize.h"

// Brightness / contrast / noise part
#include "Preprocess/brightness.h"

// Detect grid part
#include "Preprocess/hough_transform.h"
#include "Preprocess/flood_fill.h"
#include "Preprocess/debug_utils.h"




#endif



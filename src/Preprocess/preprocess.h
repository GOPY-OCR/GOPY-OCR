#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include "sdl_utils.h" // Load the image
#include "resize.h"
#include "grayscale.h"
#include "brightness.h"
#include "binarize.h"
#include "perspective_correction.h"
#include "grid_detection.h"
#include "rotation.h"
#include "resize.h"
#include "split.h"
#include "params.h"

SDL_Surface **preprocess(const char *filename);

#endif



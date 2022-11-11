#ifndef PREPROCESS_H
#define PREPROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include "sdl_utils.h" // Load the image
#include "resize.h"
#include "grayscale.h"
#include "brightness.h"
#include "binarization.h"
// Include here the interpolation part
#include "grid_detection.h"
#include "rotation.h"
// Include here the cropping
#include "split.h"

SDL_Surface **preprocess(const char *filename);

#endif



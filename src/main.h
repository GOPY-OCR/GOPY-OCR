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

// Rotation part
#include "Preprocess/rotation.h"

// Detect grid part
#include "Preprocess/hough_transform.h"
#include "Preprocess/flood_fill.h"
#include "Preprocess/debug_utils.h"

// Perspective correction part
#include "Preprocess/perspective_correction.h"

// Cut part
#include "Preprocess/split.h"

// Preprocess
#include "Preprocess/preprocess.h"

// Solver part
#include "Solver/grid.h"
#include "Solver/solver.h"

// Neural Network part
#include "NeuralNetwork/xor.h"

// Postprocess
#include "Postprocess/postprocess.h"
#include "Solver/grid.h"

#endif



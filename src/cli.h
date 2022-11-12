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

// Cut part
#include "Preprocess/split.h"

// Solver part
#include "Solver/grid.h"
#include "Solver/solver.h"

// Neural Network part
#include "NeuralNetwork/xor.h"

void exit_help(int error);
char *format_final_name(char *name, char *add);
int cli(int argc, char *argv[]);

#endif



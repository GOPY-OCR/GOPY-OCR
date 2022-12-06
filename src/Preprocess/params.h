#pragma once
#include <string.h>

typedef struct {
    int ff_c;
    int b_th;
} Params;

Params get_params(const char *filename);

#pragma once

#include "matrice_type.h"
#include "matrice.h"
#include <pthread.h>

#define THREADS_COUNT 4

void matrice_dot_mthreaded(matrice *m1, matrice *m2, matrice *r);

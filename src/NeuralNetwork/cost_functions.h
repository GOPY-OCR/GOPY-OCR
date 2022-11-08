#pragma once
#include "maths.h"
#include "matrice.h"


typedef struct{
    // z: activation
    // a: output
    // y: target
    matrice* (*fn)(matrice* /*a*/, matrice* /*y*/);
    matrice* (*delta)(matrice* /*z*/, matrice* /*a*/, matrice* /*y*/);
    int id; // used for serialization and deserialization of the network
} CostFunction;

#define cross_entropy_cost (CostFunction){cross_entropy, cross_entropy_delta, 0}
// mse stands for mean squared error
#define mse_cost (CostFunction){mse, mse_delta, 1}

matrice* cross_entropy(matrice* a, matrice* y);
matrice* cross_entropy_delta(matrice* z, matrice* a, matrice* y);

matrice* mse(matrice* a, matrice* y);
matrice* mse_delta(matrice* z, matrice* a, matrice* y);

#define COST_FUNCTIONS (CostFunction[]){cross_entropy_cost, mse_cost}

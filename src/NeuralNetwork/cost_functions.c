#include "cost_functions.h"



matrice* cross_entropy(matrice *a, matrice *y){
    // not needed for now
    return NULL; //TODO
}

matrice* cross_entropy_delta(matrice *z, matrice *a, matrice *y){
    return matrice_sub(a, y);
}


matrice* mse(matrice *a, matrice *y){
    // not needed for now
    return NULL; //TODO
}

matrice* mse_delta(matrice *z, matrice *a, matrice *y){
    matrice *sig = matrice_clone(z);
    matrice_map(sig, sigmoid_prime);
    matrice *sub = matrice_sub(a, y);
    matrice *res = matrice_mul(sub, sig);
    matrice_free(sub);
    matrice_free(sig);
    return res;
}

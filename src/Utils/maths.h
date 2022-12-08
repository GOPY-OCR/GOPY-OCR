#pragma once
#include <math.h>

#define max(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a > _b ? _a : _b; })

#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
        __typeof__ (b) _b = (b); \
        _a < _b ? _a : _b; })

double sigmoid(double x);
double sigmoid_prime(double x);
double doubleabs(double x);

double degree_to_radian(double degree);

double cos_degree(double degree);
double sin_degree(double degree);


int intabs(int x);

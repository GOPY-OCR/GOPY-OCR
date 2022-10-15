#include "math.h"

double sigmoid(double x) { return 1 / (1 + exp(-x)); }

double sigmoid_prime(double x) {
    double s = sigmoid(x);
    return s * (1 - s);
}

double doubleabs(double x) { return x < 0 ? -x : x; }

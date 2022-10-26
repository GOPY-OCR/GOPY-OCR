#include "maths.h"

double sigmoid(double x) { 
    return 1 / (1 + exp(-x)); 
}

double sigmoid_prime(double x) {
    double s = sigmoid(x);
    return s * (1 - s);
}

double doubleabs(double x) { 
    return x < 0 ? -x : x; 
}

double degree_to_radian(double degree){
    return degree * M_PI / 180;
}

double cos_degree(double degree){
    return cos(degree_to_radian(degree));
}
double sin_degree(double degree){
    return sin(degree_to_radian(degree));
}


int intabs(int x) { 
    return x < 0 ? -x : x; 
}

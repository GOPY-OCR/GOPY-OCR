#include "maths.h"

float sigmoid(float x) { 
    return 1 / (1 + exp(-x)); 
}

float sigmoid_prime(float x) {
    float s = sigmoid(x);
    return s * (1 - s);
}

float floatabs(float x) { 
    return x < 0 ? -x : x; 
}

float degree_to_radian(float degree){
    return degree * M_PI / 180;
}

float cos_degree(float degree){
    return cos(degree_to_radian(degree));
}
float sin_degree(float degree){
    return sin(degree_to_radian(degree));
}


int intabs(int x) { 
    return x < 0 ? -x : x; 
}

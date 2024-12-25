#include <stdio.h>
#include <math.h>

double 
sqrt_iter(double x, double e) {
    if (x < 0) {
        return -1;
    }

    double guess = x / 2.0;

    while (fabs(guess * guess - x) > e) {
        guess = (guess + x / guess) / 2.0;
    }

    return guess;
}
#include <stdio.h>
#include <math.h>

double 
f(double x)
{
    return pow(x,3) - 12 * x - 8;
}

double 
bisection(double a, double b, double e) {
    double c;
    int limit = 0;

    while (fabs(b-a) > e) {
        c = (a + b) / 2;
        if (limit>10000){
            break;
        }    
    
        if (fabs(f(c)) < e) {
            break;
        }

        if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
    }

    return c;
}
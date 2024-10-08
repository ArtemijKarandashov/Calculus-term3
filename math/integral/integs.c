#include <stdio.h>
#include <math.h>
#include "integs.h"

double func (double x){
    return x*x;
}

double integ_left_parts(float a, float b, int n){
    double h = (b-a)/n;
    double x = a;
    double res = 0;
    for (int k=0;k<=n-1;k++){
        res = res + func(x);
        x = a + k*h;
    }
    return res*h;
}

double integ_right_parts(float a, float b, int n){
    double h = (b-a)/n;
    double x = a;
    double res = 0;
    for (int k=1;k<=n;k++){
        res = res + func(x);
        x = a + k*h;
    }
    return res*h;
}

double integ_trapeze(float a, float b, int n){
    double h = (b-a)/n;
    double x1 = a;
    double x2 = a;
    double res = 0;
    for (int k=1;k<=n;k++){
        x1 = a + k*h;
        x2 = a + (k-1)*h;
        res = res + (func(x2)+func(x1))/2;
    }
    return res*h;
}

double integ_parabola(float a, float b, int n){
    double h = (b-a)/n;
    double sum1 = 0;
    double sum2 = 0;
    double x = a;
    for (int k = 2; k<=n-2; k = k + 2){
        x = a + h*k;
        sum2 = sum2 + func(x);
    }
    x = a;
    for (int k = 1; k<=n-1; k = k + 2){
        x = a + h*k;
        sum1 = sum1 + func(x);
    }

    return h/3 * (func(a) + func(b) + 4 * sum1 + 2 * sum2);
}
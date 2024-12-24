#include "IntegFunc.h"
#include <math.h>

double
func(double x)
{   
    double a = 5;
    //double r = 6377;
    //double R = 60.27*r;
    //double g = 9.8*12960;
    //return sqrt(x*R/(2*r*r*g*(R-x)));
    return pow(a/2 * ( exp(x/a) + exp((-1)*x/a)),2);
    //return x*x;
}

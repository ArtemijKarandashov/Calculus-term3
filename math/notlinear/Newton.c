#include <stdio.h>
#include <math.h>

double 
df(double x)
{
    return 3*x*x - 12; //Производная x^3 - 12x - 8
}

double 
newton( double a, 
        double b, 
        double e)
{
    if (f(a)*f(b) > 0){
        return 0;
    }

    double x1;
    double x0;
    
    do{
        x1 = x0 - f(x0) / df(x0);
        if (fabs(x1-x0)<e){
            break;
        }
        x0 = x1;
    }while (fabs(x1-x0) < e);

    return x0;
}
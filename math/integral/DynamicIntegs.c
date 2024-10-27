#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "DynamicIntegs.h"
#include "IntegFunc.h"

double
integ_dynamic_slow( double a, 
                    double b, 
                    double E)
{ 
    double  differ  = 1;
    double  n       = ceil((a - b) / pow(E, 0.5));;
    double  h       = (a-b) / n;
    double  value   = 0, 
            log_1   = 0, 
            log_2   = 0;

    while (differ > E)
    {
        value = 0;
        for (double i = a; i <= b-h; i+=h)
        {
            value += func(i);
        }

        log_2   = value * h;
        differ  = fabs(log_2 - log_1);

        log_1   = log_2;
        h /= 2;
    }

    return log_2;
}

double
integ_dynamic_fast( double a, 
                    double b, 
                    double E)
{ 
    double  differ  = 1;
    double  n       = ceil((a - b) / pow(E, 0.5));;
    double  value   = 0, 
            log_1   = 0, 
            log_2   = 0;

    double  h_s     = 0;
    double  h_v     = (a - b) / n;
    double  h_d     = h_v;

    while (differ > E)
    {
        for (double i = a + h_s; i <= b - h_d - h_s; i+=h_d)
        {
            value += func(i);
        }

        log_2   = value * h_v;
        differ  = fabs(log_2 - log_1);

        log_1   = log_2;

        h_d     = h_v;
        h_s     = h_v/2;
        h_v     /= 2;
        
    }
    return log_2;
}
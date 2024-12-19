#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "DynamicIntegs.h"

double
integ_dynamic_slow( double a, 
                    double b, 
                    double E)
{ 
    int counter     = 0;
    double  differ  = 1;
    int  n          = ceil((a - b) / pow(E, 0.5));
    double  h       = (a-b) / n;
    double  arr_x[n];
    double  arr_y[n];
    double  x;
    double  value   = 0, 
            log_1   = 0, 
            log_2   = 0;

    while (differ > E)
    {
        value = 0;
        for (double i = a; i <= b-h; i+=h)
        {
            x = i;
            value += func(i);
        }

        log_2   = value * h;

        arr_x[counter] = x;
        arr_y[counter] = log_2;
        differ  = fabs(log_2 - log_1);

        log_1   = log_2;
        h /= 2;
    }

    save_integ_data(n,arr_x,arr_y);
    save_integ_csv(n,arr_x,arr_y);
    return log_2;
}

double
integ_dynamic_fast( double a, 
                    double b, 
                    double E)
{   
    int counter     = 0;
    double  differ  = 1;
    int     n       = ceil((a - b) / pow(E, 0.5));
    double  arr_x[n];
    double  arr_y[n];
    double  x;
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
            x = i;
            value += func(x);
        }

        log_2   = value * h_v;
        differ  = fabs(log_2 - log_1);

        arr_x[counter] = x;
        arr_y[counter] = log_2;

        log_1   = log_2;

        h_d     = h_v;
        h_s     = h_v/2;
        h_v     /= 2;
        
    }
    
    
    save_integ_data(n,arr_x,arr_y);
    save_integ_csv(n,arr_x,arr_y);
    return log_2;
}
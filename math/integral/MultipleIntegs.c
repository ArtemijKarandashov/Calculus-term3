#include "MultipleIntegs.h"
#include <math.h>

double 
multiple_func(  double  x,
                double  y)
{
    return sin(x+y);
}


double
multiple_integ( double  a,
                double  b,
                double  c,
                double  d,
                int     n_x,
                int     n_y)
{
    double arr_x[n_x];
    double arr_y[n_y];

    double h_x = (b-a)/n_x;
    double h_y = (d-c)/n_y;

    double s_x = 0;
    double s_y = 0;

    double i_x = 0;
    double i_y = 0;

    for (double k=a; k <=b-h_x;k+=h_x)
    {
        s_y = 0;
        for (double l = c;l<=d-h_y;l+=h_y)
        {
            s_y = s_y + fabs(multiple_func(k,l));
        }
        i_y = s_y * h_y;
        s_x += i_y;
    }

    i_x = h_x * s_x;

    //save_multi_integ_data(n_x,arr_x,arr_y);
    return i_x;
}
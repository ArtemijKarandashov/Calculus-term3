#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include"Runge.h"

double 
runge_kutt( double  a, 
            double  b,
            int     n, 
            double  x0, 
            double  y0) 
{

    double arr_x[n];
    double arr_y[n];
    double arr_f[n];
    
    double x = x0;
    double y = y0;

    double h = (b - a) / n;
    
    for (int i = 0; i<n; i++)
    {
        double k1 = d_func(x,y);
        double k2 = d_func((x + h/2),(y + h*k1/2));
        double k3 = d_func((x + h/2),(y + h*k2/2));
        double k4 = d_func((x + h),(y + h*k3));
        
        printf("%d\t %lf\t %lf\t %lf\t\n",i+1,x,y,k1);
        arr_x[i] = x;
        arr_y[i] = y;
        arr_f[i] = k1;

        y = y + (h/6)*(k1+2*k2+2*k3+k4);
        x = x + h;
    }

    save_diff_data(n,arr_x,arr_y,arr_f);
    save_diff_csv(n,arr_x,arr_y,arr_f);
    return arr_y[n-1];
}
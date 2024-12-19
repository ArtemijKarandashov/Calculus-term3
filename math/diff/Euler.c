#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include"Euler.h"

double 
euler(double a, 
      double b, 
      int    n, 
      double x0, 
      double y0)
{
    double arr_x[n];
    double arr_y[n];
    double arr_f[n];


    double h = (b - a) / n;
    double x = x0;
    double y = y0;
    
    for (int i = 0; i < n; i++){
        double f = d_func(x,y); 

        printf("%d\t %lf\t %lf\t %lf\t\n",i+1,x,y,f);

        arr_x[i] = x;
        arr_y[i] = y;
        arr_f[i] = f;

        y = y + h * f;
        x = x + h;
    }

    save_diff_data(n,arr_x,arr_y,arr_f);
    save_diff_csv(n,arr_x,arr_y,arr_f);
    return arr_y[n-1];
}
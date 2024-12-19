#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include"EulerSys.h"

double dx_func(double x, double z)
{
    return -2*x + 5*z;
}

double dy_func(double x, double y, double z, double t)
{
    return sin(t-1)*x-y+3*z;
}

double dz_func(double x, double z)
{
    return -x + 2*z;
}

EulerSystemAns euler_system(double a, double b, double h, double x0, double y0, double z0)
{   
    int counter = 0;
    int arr_len = fabs(b-a)/h;

    printf("%d\n",arr_len);

    double arr_x[arr_len];
    double arr_y[arr_len];
    double arr_z[arr_len];
    double arr_t[arr_len];

    double x = x0;
    double y = y0;
    double z = z0;

    for (double t = a; t < b-h; t+=h){
        double x_temp = x;
        double y_temp = y;
        double z_temp = z; 

        x += h * dx_func(x_temp,z_temp);
        y += h * dy_func(x_temp,y_temp,z_temp,t);
        z += h * dz_func(x_temp,z_temp);
        
        arr_x[counter] = x;
        arr_y[counter] = y;
        arr_z[counter] = z;
        arr_t[counter] = t;

        printf("t:%lf\t, x=%lf\t, y=%lf\t, z=%lf\t\n",t,x,y,z);
        counter++;
    }

    EulerSystemAns res;
    res.x = x;
    res.y = y;
    res.z = z;

    save_diff_sys_csv(counter,arr_x,arr_y,arr_z,arr_t);
    return res;
}
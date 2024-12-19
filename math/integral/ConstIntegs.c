#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ConstIntegs.h"

double integ_left_parts(double a, double b, int n){

    int counter = 0;    
    double arr_x[n];
    double arr_y[n];

    double h = (b-a)/n;  
    double x = a; 
    double res = 0; 
    for (double k=a;k<=b-h;k+=h){ 
        res = res + func(x);
        
        arr_x[counter] = x;
        arr_y[counter] = res*h;

        x = k;

        counter++;
    }

    save_integ_data(n,arr_x,arr_y);
    save_integ_csv(n,arr_x,arr_y);
    return res*h;
}

double integ_right_parts(double a, double b, int n){

    int counter = 0;    
    double arr_x[n];
    double arr_y[n];

    double h = (b-a)/n;
    double x = a;
    double res = 0;
    for (double k=a+h;k<=b;k+=h){
        res = res + func(x);

        arr_x[counter] = x;
        arr_y[counter] = res*h;

        printf("%lf\t %lf\n",x,res*h);
        x = k;
        counter++;
    }

    save_integ_data(n,arr_x,arr_y);
    save_integ_csv(n,arr_x,arr_y);
    return res*h;
}

double integ_trapeze(double a, double b, int n){

    int counter = 0;    
    double arr_x[n];
    double arr_y[n];

    double h = (b-a)/n;
    double x1 = a+h;
    double x2 = a;
    double res = 0;
    for (double k=a+h;k<=b;k+=h){
        x1 =  k;
        x2 = (k-h);
        res = res + (func(x2)+func(x1))/2;
        arr_x[counter] = x2;
        arr_y[counter] = res*h;

        counter++;
    }

    save_integ_data(n,arr_x,arr_y);
    save_integ_csv(n,arr_x,arr_y);
    return res*h;
}

double integ_parabola(double a, double b, int n){

    int counter = 0;    
    double arr_x[n];
    double arr_y[n];

    double h = (b-a)/n;
    double sum1 = 0;
    double sum2 = 0;
    double x = a;
    double res;
    for (double k = a+2*h; k<=b-2*h; k = k + 2*h){
        x = k;
        sum2 = sum2 + func(x);

        arr_x[counter] = x;
        arr_y[counter] = res*h;

        counter++;
    }
    x = a;
    for (double k = a+h; k<=b-h; k = k + 2*h){
        x = k;
        sum1 = sum1 + func(x);

        arr_x[counter] = x;
        arr_y[counter] = res*h;

        counter++;
    }

    res = h/3 * (func(a) + func(b) + 4 * sum1 + 2 * sum2);

    save_integ_data(n,arr_x,arr_y);
    save_integ_csv(n,arr_x,arr_y);
    return res;
}

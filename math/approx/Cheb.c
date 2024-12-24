#include<stdlib.h>
#include<stdio.h>
#include<math.h>

double 
chebyshev_exp(double x, double e){
    double S = 1;
    double Uk = 1;
    int k = 1;

    while (fabs(Uk) > e){
        Uk *= x/k;
        S  += Uk;
        k++;
    }
    return S;
}

double
chebyshev_sin(double x, double e){
    double  Uk  = x; 
    double  S   = x;
    int     k   = 1;

    while (fabs(Uk) > e){
        Uk *= (-1)*x*x/(2*k*(2*k+1));
        S += Uk;
        k++;
    }
    return S;
}

double
chebyshev_inv_sqrt(double x, double e){
    if (x<0) return -1;
    
    double val = x;
    double val_prev = 0;

    while (fabs((val_prev - val)/(val*val_prev))>e){
        val_prev = val;
        val = 0.5 * (val + x/val);
    }

    return 1/val;
}
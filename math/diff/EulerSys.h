#ifndef EULERSYS
#define EULERSYS

typedef struct EulerSystemAns{
    double x;
    double y;
    double z;
}EulerSystemAns;

EulerSystemAns euler_system(double a, double b, double h, double x0, double y0, double z0);

#endif
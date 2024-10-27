#ifndef DYNAMIC_INTEG
#define DYNAMIC_INTEG

#include <stdlib.h> 
#include <stdio.h>
#include <math.h>
#include "IntegFunc.h"

double integ_dynamic_slow( double a, double b, double E);
double integ_dynamic_fast( double a, double b, double E);

#endif
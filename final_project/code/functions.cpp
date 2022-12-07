#include <iostream>
#include <math.h>

//This file will have the equations for dxdt and dydt
//0.11 = r, 0.0000000012 = f0, 0.012 = m, 3.91x10^3 = X0
//I am using these parameters now to try and replicate paper
//These values come from mouse 1 in a table on the paper
//Maybe try other values?

double dxdt(double a, double b, double r, double f0) {
    double value = (r - (f0 * (a+b))) * a;
    return value;
}

double dydt(double a, double b, double f0, double m) {
    double value = (f0 * (a+b) * a) - (m*b);
    return value;
}

double dcdt(double a, double b, double c, double f0, double m, double m2, double r2) {
    double value = (r2 - (f0 * (a + b))) * a - (m*b) - (m2*c);
    return value;
}



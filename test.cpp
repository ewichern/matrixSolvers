#include "rootSolvers.h"
#include <iostream>
#include <iomanip>
#include <cmath>

double f (double x)
{
    return (powf(x, 3.0) + 4.0);
}


int main (int argc, char **argv)
{
    double lower = -10.0;
    double upper = 10.0;
    double errLim = 0.00001;
    int numIterations = 0;

    double root = rootSolvers::bisection(&f, lower, upper, numIterations, errLim);
    std::cout << std::setprecision(17) << std::fixed << root << std::endl;
    return 1;
}

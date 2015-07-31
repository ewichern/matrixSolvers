//#include "rootSolvers.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "matrixGenerator.h"
#include "rootSolvers.h"

typedef denseMatrix<double> matrix;

double v (double t)
{
	double u = 2000.0; // m/s
	double m_0 = 150000.0; // kg
	double q = 2500.0; // kg/s
	double v_0 = 750.0; // m/s
	double g = 9.81; // m/s^2

	return (u * log (m_0 / (m_0 - (q * t))) - (g * t) - v_0);
}

double v_check (double t)
{
	double u = 2000.0; // m/s
	double m_0 = 150000.0; // kg
	double q = 2500.0; // kg/s
	double g = 9.81; // m/s^2

	return (u * log (m_0 / (m_0 - (q * t))) - (g * t));
}

double f (double x)
{
    return (powf(x, 2.0) - ((47.0 / 36.0) * x) + (21.0 / 36.0));
}

double f_prime (double x)
{
	return ((2.0 * x) - (47.0 / 36.0));
}


int main (int argc, char **argv)
{
/*    
    int size = 1000;
    matrix test(size, size);
    matrix testB(size, 1, 2.0);
    //std::cerr << test.numrows() << " " << test.numcols() << std::endl;
    //std::cerr << testB.numrows() << " " << testB.numcols() << std::endl;
    test.eye();
    std::ofstream output ("midterm.dat");
    MatrixGenerator::writeMatrixToFile(output, test, testB);
*/
//	double x = 11.0;
	int numIterations = 0;
	double errLimit = 0.00001;
	double lower = 10;
	double upper = 50;

	double t = rootSolvers::falsePosition(v, lower, upper, numIterations, errLimit);

	double v_test = v_check(t);

	std::cout << t << std::endl;
	std::cout << v_test << std::endl;
    return 1;
}

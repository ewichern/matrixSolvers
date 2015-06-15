//#include "rootSolvers.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>

#include "matrixGenerator.h"
#include "rootSolvers.h"
#include "polynomial.h"

typedef denseMatrix<double> matrix;

double f_6 (double x)
{
	return (x + log (x));
}

int main (int argc, char **argv)
{
	int numIterations = 0;
	double errLimit = 0.00001;
	double lower = 0.1;
	double upper = 1;

	
	std::cout << "f(x) = x + ln(x)\n";
	std::cout << "Question 6 - Bisection\n";
	double solution = rootSolvers::bisection(f_6, lower, upper, numIterations, errLimit);
	std::cout << "Iterations: " << numIterations << std::endl;
	std::cout << "Root: " << solution << std::endl << std::endl;

	numIterations = 0;

	std::cout << "Question 7 - Regula-falsi\n";
	solution = rootSolvers::falsePosition(f_6, lower, upper, numIterations, errLimit);
	std::cout << "Iterations: " << numIterations << std::endl;
	std::cout << "Root: " << solution << std::endl << std::endl;

	numIterations = 0;

	std::cout << "Question 8 - Newton's method on a Polynomial Object\n";

//	std::vector<double> coeffs {1, 2, -9, -2, 8};
	std::vector<double> coeffs {8, -2, -9, 2, 1};
	polynomial poly(coeffs);

	std::cout << poly << "\n";
	double guess = -10.0;
	std::cout << "initial guess: " << guess << "\n";

	solution = rootSolvers::newton(poly, guess, numIterations, errLimit);
	std::cout << "Iterations: " << numIterations << std::endl;
	std::cout << "Root: " << solution << std::endl << std::endl;
/*
	guess = -2.0;
	std::cout << "initial guess: " << guess << "\n";

	solution = rootSolvers::newton(poly, guess, numIterations, errLimit);
	std::cout << "Iterations: " << numIterations << std::endl;
	std::cout << "Root: " << solution << std::endl;
*/
    return 1;
}

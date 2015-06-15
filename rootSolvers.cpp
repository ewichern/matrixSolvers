/*
 * rootSolvers.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "rootSolvers.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>

/*
 * Bracketing root solver using bisection method
 *
 * Takes a function pointer (*f) for the function to be solved, expects
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the solution as a double.
 *
 * @param *f	double(*_)(double) function pointer to the function for which we want to find a root
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double rootSolvers::bisection(double (*f)(double), double lower, double upper,
		int& numIterations, double errLimit)
{
	double root = upper;
	numIterations = 0;

	double f_l = f(lower);
	double f_r = f(root);

	while ((fabs(f_r)) > errLimit)
	{
//		double root_old = root;
		root = (lower + upper) / 2.0;
		f_r = f(root);
		++numIterations;

		std::cout << "It: " << numIterations << "\n";
		std::cout << "root: " << root << "\n";

		double test = f_l * f_r;
		if (test < 0.0)
		{
			upper = root;
		}
		else if (test > 0.0)
		{
			lower = root;
			f_l = f_r;
		}
	}
	return root;
}

const polynomial* polyObj;
const polynomial* polyObj2;

/*
 * Wrapper for pointer to member function
 *
 * @param x		double input for function evalutation using member evaluateAt(double)
 * @return double	returns f(x)
 */
double polyEval(double x)
{
	double f_x = polyObj->evaluateAt(x);
	return f_x;
}

/*
 * Wrapper for pointer to member function
 *
 * @param x		double input for function evalutation using member evaluateAt(double)
 * @return double	returns f(x)
 */
double polyEval2(double x)
{
	double f_x = polyObj2->evaluateAt(x);
	return f_x;
}

/*
 * Bracketing root solver using bisection method
 *
 * Takes a polynomial expression to be solved, expects
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the solution as a double.
 *
 * @param poly 		const polynomial expression to be solved
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double rootSolvers::bisection(const polynomial poly, double lower, double upper,
		int& numIterations, double errLimit)
{
	// set global pointer to our polynomial object
	polyObj = &poly;

	// create a function pointer to the wrapper function
	double (*f)(double)= polyEval;

	// call the normal bisection solver with our new function pointer
	double root = rootSolvers::bisection(f, lower, upper, numIterations,
			errLimit);

	return root;
}

/*
 * Bracketing root solver using False-Position method
 *
 * Takes a polynomial expression to be solved, expects
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the solution as a double.
 *
 * @param poly 		const polynomial expression to be solved
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double rootSolvers::falsePosition(const polynomial poly, double lower,
		double upper, int& numIterations, double errLimit)
{
	// set global pointer to our polynomial object
	polyObj = &poly;

	// create a function pointer to the wrapper function
	double (*f)(double)= polyEval;

	// call the normal bisection solver with our new function pointer
	double root = rootSolvers::falsePosition(f, lower, upper, numIterations,
			errLimit);

	return root;
}

/*
 * Bracketing root solver using False-Position method
 *
 * Takes a function pointer (*f) for the function to be solved, expects
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the solution as a double.
 *
 * @param *f	double(*_)(double) function pointer to the function for which we want to find a root
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double rootSolvers::falsePosition(double (*f)(double), double lower,
		double upper, int& numIterations, double errLimit)
{
	double root = upper;
	numIterations = 0;
	double err = 1.0;
	int upperStaleCounter = 0;
	int lowerStaleCounter = 0;

	double f_l = f(lower);
	double f_u = f(upper);
	double f_r = f(root);

//	while ((fabs(f_r)) > errLimit)

	while (err > errLimit)
	{
		double root_old = root;
		root = (upper - ((f_u * (lower - upper)) / (f_l - f_u)));
		f_r = f(root);
		++numIterations;

		std::cout << "It: " << numIterations << "\n";
		std::cout << "root: " << root << "\n";

		if (root != 0.0)
		{
			err = relErr(root, root_old);
		}

		double test = f_l * f_r;
		if (test < 0.0)
		{
			upper = root;
			f_u = f_r;
			upperStaleCounter = 0;
			lowerStaleCounter++;
			if (lowerStaleCounter >= 2)
			{
				f_l = f_l / 2.0;
			}
		}
		else if (test > 0.0)
		{
			lower = root;
			f_l = f_r;
			lowerStaleCounter = 0;
			upperStaleCounter++;
			if (upperStaleCounter >= 2)
			{
				f_u = f_u / 2.0;
			}
		}
		else
			err = 0.0;
	}
	return root;
}

/*
 * Open Newton-Raphson method root solver
 *
 * Takes a polynomial expression to be solved, expects
 * an inital guess for the root x_0, and the error tolerance.
 * Returns the solution.
 *
 * @param poly 		const polynomial expression to be solved
 * @param root_guess 	double with an initial guess for the root as a starting condition
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double rootSolvers::newton(const polynomial poly, double root_guess,
		int& numIterations, double errLimit)
{
	polynomial firstDerivative = poly;
	firstDerivative.derivative();

	// set global pointer to our polynomial object
	polyObj = &poly;
	polyObj2 = &firstDerivative;

	// create a function pointer to the wrapper function
	double (*f)(double) = polyEval;
	double (*f_prime)(double) = polyEval2;

	// call the normal newton solver with our new function pointer
	double root = rootSolvers::newton(f, f_prime, root_guess, numIterations,
			errLimit);

	return root;
}

/*
 * Open Newton-Raphson method root solver
 *
 * Takes a function pointer (*f) for the function to be solved, expects
 * an inital guess for the root x_0, and the error tolerance.
 * Returns the solution.
 *
 * @param *f	double(*_)(double) function pointer to the function for which we want to find a root
 * @param root		double with initial guess for the root location
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double rootSolvers::newton(double (*f)(double), double (*f_prime)(double),
		double root, int& numIterations, double errLimit)
{
	numIterations = 0;
	double err = 1.0;

	while ((err > errLimit) && (numIterations < 10000))
	{
		double r_old = root;
		double slope_tangent = f_prime(r_old);

		std::cout << "It: " << numIterations << "\n";
		std::cout << "root: " << root << "\n";
//		std::cout << "Slope at r_old: " << slope_tangent << "\n";

		if (relErr(0.0, slope_tangent) < 0.000001)
		{
			throw std::runtime_error(
					"slope_tangent == 0, Newton method failed.");
		}
		root = (r_old - (f(r_old) / f_prime(r_old)));
		numIterations++;
		if (root != 0.0)
		{
			err = relErr(root, r_old);
		}
	}
	double solution_check = f(root);

	if ((relErr(0.0, solution_check) > 0.01) || (numIterations == 100000))
	{
		throw std::runtime_error("No convergence, Newton method failed.");
	}

	return root;
}

/*
 * Relative error function
 *
 * Uses a modified relative error formula to compensate for potential zero
 * (or very very small) values.
 *
 * @param value1	double - one value for relative error computation
 * @param value2	double - second value for relative error computation
 * @return double	Relative error between the two values
 */
double rootSolvers::relErr(double value1, double value2)
{
	value1 = fabs(value1);
	value2 = fabs(value2);

	if ((value1 == 0) || (value2 == 0))
	{
		return ((fabs(value1 - value2)) / (1 + (fmax(value1, value2))));
	}
	else
		return (2.0 * (fabs((value1 - value2) / (value1 + value2))));
}

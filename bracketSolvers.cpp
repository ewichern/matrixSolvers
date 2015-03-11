/*
 * bracketSolvers.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "bracketSolvers.h"
#include <math.h>

/*
 * Bracketing root solver using bisection method
 *
 * Takes a function pointer (*f) for the function to be solved, expects
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the number of iterations required to find a solution.
 *
 * @param *f	double(*_)(double) function pointer to the function for which we want to find a root
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param err		double reference used to return the actual error of this solution
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double bracketSolvers::bisection(double (*f)(double), double lower,
		double upper, int& numIterations, double& err, double errLimit)
{
	double root = upper;
	err = 999.0;
	numIterations = 0;

	double f_l = f(lower);

	while (err > errLimit)
	{
		double root_old = root;
		root = (lower + upper) / 2;
		double f_r = f(root);
		++numIterations;
		if (root != 0)
		{
			err = relErr (root, root_old);
		}
		double test = f_l * f_r;
		if (test < 0)
		{
			upper = root;
		}
		else if (test > 0)
		{
			lower = root;
			f_l = f_r;
		}
		else
		{
			err = 0;
		}
	}
	return root;
}

double bracketSolvers::relErr(double value1, double value2)
{
	double err = 100.0;
	err = fabs(((value1 - value2) / value1) * 100.0);
	return err;
}

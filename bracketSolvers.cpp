/*
 * bracketSolvers.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "bracketSolvers.h"
#include <cmath>

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
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double bracketSolvers::bisection(double (*f)(double), double lower,
		double upper, int& numIterations, double errLimit)
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

/*
 * Bracketing root solver using False-Position method
 *
 * Takes a function pointer (*f) for the function to be solved, expects
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the number of iterations required to find a solution.
 *
 * @param *f	double(*_)(double) function pointer to the function for which we want to find a root
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double bracketSolvers::falsePosition(double (*f)(double), double lower,
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


double bracketSolvers::relErr(double value1, double value2)
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

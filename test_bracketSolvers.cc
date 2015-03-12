/*
 * test_bracketSolvers.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include "bracketSolvers.h"
#include <cmath>
#include <iomanip>

class bracketSolverTests: public ::testing::Test
{
public:

	bracketSolverTests()
	{

	}

	virtual ~bracketSolverTests()
	{

	}

	/*
	 * f(x) = (2x - 5)
	 *
	 * root = 5/2 (2.5)
	 */
	const double f1solution = 2.5;
	static double f1(double x)
	{
		return (2.0 * x - 5.0);
	}

	/*
	 * f(x) = (x - 3)(4x + 7)
	 * 4x^2 - 5x - 21
	 *
	 * roots = 3, -7/4 (-1.75)
	 */
	const double f2solutionA = 3.0;
	const double f2solutionB = (-7.0 / 4.0);
	static double f2(double x)
	{
		return (4.0 * powf(x, 2.0) - 5.0 * x - 21.0);
	}

	/*
	 * Adding this one to test what happens if a "root" is zero.
	 * f(x) = x
	 *
	 * root = 0
	 */
	const double f3solution = 0.0;
	static double f3(double x)
	{
		return x;
	}
};

TEST_F (bracketSolverTests, bisection1)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = bracketSolvers::bisection(&f1, lower, upper, numIterations,
			errLim);
	double err = bracketSolvers::relErr(f1solution, root);

	std::cerr << "Root for f1: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (bracketSolverTests, bisection2)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = bracketSolvers::bisection(&f2, lower, upper, numIterations,
			errLim);
	double err = bracketSolvers::relErr(f2solutionA, root);

	std::cerr << "Root 1 for f2: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);

	lower = -10.0;
	upper = 0.0;
	numIterations = 0;

	root = bracketSolvers::bisection(&f2, lower, upper, numIterations,
			errLim);
	err = bracketSolvers::relErr(f2solutionB, root);

	std::cerr << "Root 2 for f2: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (bracketSolverTests, bisection3)
{
	double lower = -4.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = bracketSolvers::bisection(&f3, lower, upper, numIterations, errLim);
	double err = bracketSolvers::relErr(root, f3solution);

	std::cerr << "Root for f3: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (bracketSolverTests, falsePosition1)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = bracketSolvers::falsePosition(&f2, lower, upper, numIterations,
			errLim);
	double err = bracketSolvers::relErr(f2solutionA, root);

	std::cerr << "Root 1 for f2: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with False-position method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);

	lower = -10.0;
	upper = 0.0;
	numIterations = 0;

	root = bracketSolvers::falsePosition(&f2, lower, upper, numIterations,
			errLim);
	err = bracketSolvers::relErr(f2solutionB, root);

	std::cerr << "Root 2 for f2: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with False-position method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (bracketSolverTests, falsePosition2)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = bracketSolvers::falsePosition(&f1, lower, upper, numIterations,
			errLim);
	double err = bracketSolvers::relErr(f1solution, root);

	std::cerr << "Root for f1: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations << " iterations with False-position method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}



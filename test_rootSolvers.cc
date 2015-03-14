/*
 * test_rootSolvers.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include "rootSolvers.h"
#include <cmath>
#include <iomanip>

class rootSolverTests: public ::testing::Test
{
public:

	rootSolverTests()
	{

	}

	virtual ~rootSolverTests()
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
	 * 1st dervative of f2, using to test newton's method
	 */
	static double f2_prime(double x)
	{
		return ((8.0 * x) - 5.0);
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

TEST_F (rootSolverTests, bisection1)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::bisection(&f1, lower, upper, numIterations,
			errLim);
	double err = rootSolvers::relErr(f1solution, root);

	std::cerr << "Root for f1: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (rootSolverTests, bisection2)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::bisection(&f2, lower, upper, numIterations,
			errLim);
	double err = rootSolvers::relErr(f2solutionA, root);

	std::cerr << "Root 1 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);

	lower = -10.0;
	upper = 0.0;
	numIterations = 0;

	root = rootSolvers::bisection(&f2, lower, upper, numIterations, errLim);
	err = rootSolvers::relErr(f2solutionB, root);

	std::cerr << "Root 2 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (rootSolverTests, bisection3)
{
	double lower = -4.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::bisection(&f3, lower, upper, numIterations,
			errLim);
	double err = rootSolvers::relErr(root, f3solution);

	std::cerr << "Root for f3: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Bisection method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (rootSolverTests, falsePosition1)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::falsePosition(&f2, lower, upper, numIterations,
			errLim);
	double err = rootSolvers::relErr(f2solutionA, root);

	std::cerr << "Root 1 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with False-position method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);

	lower = -10.0;
	upper = 0.0;
	numIterations = 0;

	root = rootSolvers::falsePosition(&f2, lower, upper, numIterations, errLim);
	err = rootSolvers::relErr(f2solutionB, root);

	std::cerr << "Root 2 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with False-position method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (rootSolverTests, falsePosition2)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::falsePosition(&f1, lower, upper, numIterations,
			errLim);
	double err = rootSolvers::relErr(f1solution, root);

	std::cerr << "Root for f1: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with False-position method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (rootSolverTests, newton1)
{
	double root_guess = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::newton(&f2, &f2_prime, root_guess, numIterations,
			errLim);
	double err = rootSolvers::relErr(f2solutionA, root);

	std::cerr << "Root 1 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Newton method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);

	root_guess = -5.0;
	numIterations = 0;

	root = rootSolvers::newton(&f2, &f2_prime, root_guess, numIterations, errLim);
	err = rootSolvers::relErr(f2solutionB, root);

	std::cerr << "Root 2 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Newton method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

/*
TEST_F (rootSolverTests, newton2)
{
	double lower = 0.0;
	double upper = 9.0;

	double errLim = 0.00001;
	int numIterations = 0;

	double root = rootSolvers::newton(&f1, lower, upper, numIterations, errLim);
	double err = rootSolvers::relErr(f1solution, root);

	std::cerr << "Root for f1: " << std::fixed << std::setprecision(17) << root
			<< std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Newton method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}
*/

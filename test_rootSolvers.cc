/*
 * test_rootSolvers.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include "gtest/gtest-spi.h"
#include "rootSolvers.h"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <sstream>

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

	/*
	 * x(x+1)(x-1)
	 * roots at 1, -1.
	 * f'(x) = 0 at x = -3^(-1/2) and x = 3^(-1/2)
	 */
	const double f4solutionA = 1.0;
	const double f4solutionB = -1.0;
	static double f4(double x)
	{
		return (powf(x, 3.0) - x);
	}

	static double f4_prime(double x)
	{
		return ((3.0 * powf(x, 2.0)) - 1);
	}

	/*
	 * f(x) = x^2 + 2
	 * No real roots
	 * f'(x) = 2x
	 */
	static double f5(double x)
	{
		return (powf(x, 2.0) + 2.0);
	}
	static double f5_prime(double x)
	{
		return (2.0 * x);
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

	root = rootSolvers::newton(&f2, &f2_prime, root_guess, numIterations,
			errLim);
	err = rootSolvers::relErr(f2solutionB, root);

	std::cerr << "Root 2 for f2: " << std::fixed << std::setprecision(17)
			<< root << std::endl;
	std::cerr << "Solved in " << numIterations
			<< " iterations with Newton method." << std::endl;
	std::cerr << "Relative error is " << err << "." << std::endl << std::endl;

	EXPECT_LE(err, errLim);
}

TEST_F (rootSolverTests, newtonExceptionTest)
{
	double root_guess = 0.0;

	double errLim = 0.00001;
	int numIterations = 0;

	/*
	 * First one should throw on "zero" iterations because f5'(0) = 0
	 */
	EXPECT_THROW(
	{
		rootSolvers::newton(&f5, &f5_prime, root_guess, numIterations, errLim)
		;
	}, std::runtime_error);
	std::cerr << "Solved in " << numIterations
			<< " iterations with Newton method." << std::endl;

	/*
	 * This one oscilates and hits the iteration limit,
	 * so throws the "does not converge" exception
	 */
	root_guess = 3.0;
	EXPECT_THROW(
	{
		rootSolvers::newton(&f5, &f5_prime, root_guess, numIterations, errLim)
		;
	}, std::runtime_error);
	std::cerr << "Solved in " << numIterations
			<< " iterations with Newton method." << std::endl;
}

TEST_F (rootSolverTests, defaultConstructor)
{
	rootSolvers testRS;

	EXPECT_EQ(0, testRS.size());
}

TEST_F (rootSolverTests, constructor)
{
	std::vector<double> numbers {3, 0, 2, 1};
//	std::cerr << "rootSolvers constructor - numbers.size(): " << numbers.size() << std::endl;

	rootSolvers poly(numbers);
//	std::cerr << "rootSolvers constructor - poly.size() (after construction): " << poly.size() << std::endl;
	std::cerr << poly;

	EXPECT_EQ(4, poly.size());

	std::vector<double> numbers1 {3, 0, -2, 1};

	rootSolvers poly1(numbers1);
	std::cerr << poly1;

	EXPECT_EQ(4, poly1.size());

	rootSolvers poly2(poly1);
	std::cerr << poly2;

	EXPECT_EQ(4, poly2.size());
}

TEST_F (rootSolverTests, assignment)
{
	std::string expected = "x^3 + 2x + 3\n";
	std::vector<double> numbers {3, 2, 0, 1};
	rootSolvers poly(numbers);
	rootSolvers poly1;

	EXPECT_EQ(4, poly.size());
	EXPECT_EQ(0, poly1.size());

	poly1 = poly;

	std::ostringstream testOutput;
	testOutput << poly1;

	std::string actual = testOutput.str();

	EXPECT_EQ(expected, actual);
}

TEST_F (rootSolverTests, evaluate)
{
	// expected = "x^3 + 2x + 3";
	std::vector<double> numbers {3, 2, 0, 1};
	rootSolvers poly(numbers);

	double x = 1;
	double expectedF_x = 6;
	double f_x = poly.evaluatePolynomialAt(x);

	EXPECT_EQ(expectedF_x, f_x);

	x = 2;
	expectedF_x = 15;
	f_x = poly.evaluatePolynomialAt(x);

	EXPECT_EQ(expectedF_x, f_x);

	x = 0;
	expectedF_x = 3;
	f_x = poly.evaluatePolynomialAt(x);

	EXPECT_EQ(expectedF_x, f_x);

	x = -3;
	expectedF_x = -30;
	f_x = poly.evaluatePolynomialAt(x);

	EXPECT_EQ(expectedF_x, f_x);

	std::vector<double> numbers1 {3, 0, -2, 1};

	rootSolvers poly1(numbers1);
	std::cerr << poly1;

	EXPECT_EQ(4, poly1.size());

	x = -3;
	expectedF_x = -42;
	f_x = poly1.evaluatePolynomialAt(x);

	EXPECT_EQ(expectedF_x, f_x);
}

TEST_F (rootSolverTests, polyDerivative)
{
	// expected = "x^3 + 2x + 3";
	std::vector<double> numbers {3, 2, 0, 1};
	rootSolvers poly(numbers);

	poly.derivative();

	std::cout << poly;
}

TEST_F (rootSolverTests, equality)
{
	std::vector<double> numbers {3, 2, 0, 1};
	rootSolvers poly(numbers);
	rootSolvers poly1;

	EXPECT_FALSE(poly == poly1);

	poly1 = poly;

	std::ostringstream expected, actual;
	expected << poly;
	actual << poly1;

	EXPECT_EQ(expected.str(), actual.str());
	EXPECT_TRUE(poly == poly1);
	std::cerr << poly;
	std::cerr << poly1;
}

TEST_F (rootSolverTests, polynomialPrint)
{
	std::string expected = "x^3 + 2x + 3\n";
	std::vector<double> numbers {3, 2, 0, 1};
	rootSolvers poly(numbers);

	std::ostringstream testOutput;
	testOutput << poly;

	std::string actual = testOutput.str();

	EXPECT_EQ(expected, actual);
	std::cout << "Polynomial print test: " << poly;
}

TEST_F (rootSolverTests, solveBisect)
{
	// 4x^2 - 5x - 21
	// roots at 3, -1.75
	double rootSolution1 = 3.0;
	double rootSolution2 = -1.75;
	std::vector<double> numbers {-21, -5, 4};
	rootSolvers poly(numbers);

	double lower = 0.0;
	double upper = 10.0;
	int numIterations =0;
	double errLimit = 0.0001;

	double root1 = poly.solveBisect(lower, upper, numIterations, errLimit);
	std::cerr << "Root1 from new solveBisect implementation: " << root1 << std::endl;
	std::cerr << "solved in " << numIterations << " iterations" << std::endl;

	double err = rootSolvers::relErr(root1, rootSolution1);
	std::cerr << "Rel. error from new solveBisect implementation: " << err << std::endl;

	EXPECT_LE(err, errLimit);

	lower = -10.0;
	upper = 0.0;
	numIterations = 0;

	double root2 = poly.solveBisect(lower, upper, numIterations, errLimit);
	std::cerr << "Root2 from new solveBisect implementation: " << root2 << std::endl;
	std::cerr << "solved in " << numIterations << " iterations" << std::endl;

	err = rootSolvers::relErr(root2, rootSolution2);
	std::cerr << "Rel. error from new solveBisect implementation: " << err << std::endl;

	EXPECT_LE(err, errLimit);
}

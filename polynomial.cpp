/*
 * polynomial.cpp
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#include "polynomial.h"
#include "rootSolvers.h"
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>

polynomial::polynomial()
{
}

// Assuming that polynomial degree = coeffs.size() - 1
// and that there will be 0s in coeffs vector if a particular term has a power
// or coefficient of 0.

polynomial::polynomial(std::vector<double> coeffs)
{
//	std::cerr << "Coeffs.size(): " << coeffs.size() << std::endl;

	int degree = 0;
//	for (int i = 0; i < coefficients.size(); ++i)
	for (std::vector<double>::iterator loc = coeffs.begin();
			loc != coeffs.end(); ++loc)
	{
		monomial element(*loc, degree);
		coefficients.push_back(element);
		degree++;
	}
//	std::cerr << "coefficients.size() (inside constructor): " << coefficients.size()
//			<< std::endl;
}

polynomial::polynomial(const polynomial& right) :
		coefficients(right.coefficients)
{
}

polynomial::~polynomial()
{
}

polynomial& polynomial::operator=(const polynomial& right)
{
	if (!(*this == right))
	{
		coefficients = right.coefficients;
	}
	return *this;
}

bool polynomial::operator==(const polynomial& right)
{
	std::ostringstream leftSS, rightSS;
	print(leftSS);
	rightSS << right;

	return (leftSS.str() == rightSS.str());
}

int polynomial::size() const
{
	return coefficients.size();
}

double polynomial::evaluateAt(double x) const
{
	double f_x = 0;
	std::vector<monomial>::const_reverse_iterator loc;
	for (loc = coefficients.rbegin(); loc != coefficients.rend(); ++loc)
	{
		f_x += (loc->getCoefficient() * powf(x, (double) (loc->getExponent())));
	}
	return f_x;
}

void polynomial::derivative()
{
	std::vector<monomial>::reverse_iterator loc;
	for (loc = coefficients.rbegin(); loc != coefficients.rend(); ++loc)
	{
		loc->monoDerivative();
	}
}

std::ostream& polynomial::print(std::ostream& output) const
{
	if (coefficients.size() != 0)
	{
		output << *(coefficients.rbegin());
		std::vector<monomial>::const_reverse_iterator loc;
		for (loc = coefficients.rbegin() + 1; loc != coefficients.rend(); ++loc)
		{
			std::ostringstream testStream;
			testStream << *loc;
			if (testStream.str() != "")
			{
				output << " + " << *loc;
			}
		}
	}
	return output;
}

std::ostream& operator<<(std::ostream& output, polynomial poly)
{
	poly.print(output);
	return output;
}

polynomial* polyWrapperObject;

/*
 * Wrapper for pointer to member function
 *
 * @param x		double input for function evalutation using member evaluateAt(double)
 * @return double	returns f(x)
 */
double polyEvalWrapper(double x)
{
	double f_x = polyWrapperObject->evaluateAt(x);
	return f_x;
}

/*
 * Wrapper for bisection rootSolver for polynomial objects
 *
 * USE rootsolvers::bisection(polynomial, double, double, int, double); INSTEAD
 * THIS METHOD IS DEPRECATED -- GOING TO KEEP ALL OF THE SOLVERS OVERLOADED
 * IN ROOTSOLVERS.H/CPP
 * inital guesses for upper and lower bounds, and the error tolerance.
 * Returns the solution as a double.
 *
 * @param lower		double with the initial lower bracket
 * @param upper		double with the initial upper bracket
 * @param numIterations		int reference to count and pass back the number of iterations required to solve this problem
 * @param errLimit	double providing the error tolerance
 * @return double	return the root solution within the bracket
 */
double polynomial::solveBisect(double lower, double upper, int& numIterations,
		double errLimit)
{
	polyWrapperObject = this;
	double root = rootSolvers::bisection(&polyEvalWrapper, lower, upper,
			numIterations, errLimit);
	return root;
}

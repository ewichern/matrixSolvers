/*
 * rootSolvers.h
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#ifndef ROOTSOLVERS_H_
#define ROOTSOLVERS_H_

#include "monomial.h"
#include <vector>
#include <iostream>

typedef monomial monomial;

/*
 *
 */
class rootSolvers
{
public:

	rootSolvers();
	rootSolvers(std::vector<double>);
	rootSolvers(const rootSolvers&);
	virtual ~rootSolvers();

	rootSolvers& operator=(const rootSolvers&);
	bool operator==(const rootSolvers&);
	double evaluatePolynomialAt(double) const;
	void derivative();

	int size() const;
	friend std::ostream& operator<<(std::ostream& output, const rootSolvers);

	////////////////////////////////////////////////////////////////////////
	// Begin solver functions
	///////////////////////////////////////////////////////////////////////

	double solveBisect(double, double, int&, double);

	static double bisection(double (*functionPtr)(double), double, double, int&,
			double);
	static double falsePosition(double (*functionPtr)(double), double, double,
			int&, double);
	static double newton(double (*functionPtr)(double),
			double (*functionPtr2)(double), double, int&, double);
	static double relErr(double, double);

private:
	std::vector<monomial> polynomial;

	std::ostream& print(std::ostream&) const;
};

#endif /* ROOTSOLVERS_H_ */

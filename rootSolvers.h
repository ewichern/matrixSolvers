/*
 * rootSolvers.h
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#ifndef ROOTSOLVERS_H_
#define ROOTSOLVERS_H_

/*
 *
 */
class rootSolvers
{
public:

	static double bisection(double (*functionPtr)(double), double, double, int&,
			double);
	static double falsePosition(double (*functionPtr)(double), double, double,
			int&, double);
	static double newton(double (*functionPtr)(double),
			double (*functionPtr2)(double), double, int&, double);
	static double relErr(double, double);
};

#endif /* ROOTSOLVERS_H_ */
/*
 * bracketSolvers.h
 *
 *  Created on: Mar 11, 2015
 *      Author: erik
 */

#ifndef BRACKETSOLVERS_H_
#define BRACKETSOLVERS_H_

/*
 *
 */
class bracketSolvers
{
public:

	static double bisection(double (*functionPtr)(double), double, double, int&, double);
	static double falsePosition(double (*functionPtr)(double), double, double, int&, double);
	static double relErr(double, double);
};

#endif /* BRACKETSOLVERS_H_ */

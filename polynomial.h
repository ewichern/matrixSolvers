/*
 * polynomial.h
 *
 *  Created on: Apr 3, 2015
 *      Author: erik
 */

#ifndef POLYNOMIAL_H_
#define POLYNOMIAL_H_

#include "monomial.h"
#include <vector>
#include <iostream>

/*
 *
 */
class polynomial
{
public:
	polynomial();
	polynomial (std::vector<double>);
	polynomial(const polynomial&);
	virtual ~polynomial();

	polynomial& operator=(const polynomial&);
	bool operator==(const polynomial&);
	double evaluateAt(double) const;
	void derivative();

	int size() const;
	friend std::ostream& operator<<(std::ostream& output, const polynomial);

	////////////////////////////////////////////////////////////////////////
	// Begin solver functions
	////////////////////////////////////////////////////////////////////////

	double solveBisect(double, double, int&, double);

private:
	std::vector<monomial> coefficients;
	std::ostream& print(std::ostream&) const;

};

#endif /* POLYNOMIAL_H_ */

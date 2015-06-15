/*
 * monomial.h
 *
 *  Created on: Mar 15, 2015
 *      Author: erik
 */

#ifndef MONOMIAL_H_
#define MONOMIAL_H_

#include <iostream>

/*
 *
 */
class monomial
{
public:
	monomial();
	monomial(double, int);
	monomial(const monomial&);
	virtual ~monomial();

	double getCoefficient() const
	{
		return coefficient;
	};
	int getExponent() const
	{
		return exponent;
	};

	void setMonomial(const double coeff, const int exp);

	/*
	void setCoefficient(const double coeff)
	{
		coefficient = coeff;
	};
	void setExponent(const int exp)
	{
		exponent = exp;
	};
	*/

	bool operator==(const monomial& right) const;
	monomial& operator=(const monomial& right);

	void monoDerivative();
	friend std::ostream& operator<<(std::ostream& output, const monomial& m);

//	std::ostream& print(std::ostream&) const;

private:
	double coefficient;
	int exponent;
};

#endif /* MONOMIAL_H_ */

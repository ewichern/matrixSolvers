/*
 * monomial.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: erik
 */

#include "monomial.h"

monomial::monomial() :
		coefficient(0), exponent(0)
{
}

monomial::monomial(double coeff, const int exp) :
		coefficient(coeff), exponent(exp)
{
}

monomial::monomial(const monomial& right) :
		coefficient(right.coefficient), exponent(right.exponent)
{
}

monomial::~monomial()
{
}

bool monomial::operator==(const monomial& right) const
{
	if ((this->coefficient == right.coefficient)
			&& (this->exponent == right.exponent))
	{
		return true;
	}
	else
		return false;
}

monomial& monomial::operator=(const monomial& right)
{
	if (!(*this == right))
	{
		this->coefficient = right.coefficient;
		this->exponent = right.exponent;
	}
	return *this;
}

void monomial::derivative()
{
	/*
	 if ((coefficient != 0) && (exponent == 0))
	 {
	 coefficient = 0;
	 exponent = 0;
	 }
	 */

	coefficient = coefficient * exponent;
	exponent = exponent - 1;
}

std::ostream& operator<< (std::ostream& output, const monomial& m)
{
	if (m.getCoefficient() != 0)
		{
			if (m.getCoefficient() < 0)
			{
				output << "(" << m.getCoefficient() << ")";
			}
			else
			{
				output << m.getCoefficient();
			}

			if (m.getExponent() != 0)
			{
				output << "x^" << m.getExponent();
			}
		}
		return output;

//	return output << m.print(output);
};

/*
std::ostream& monomial::print(std::ostream& output) const
{
	if (coefficient != 0)
	{
		if (coefficient < 0)
		{
			output << "(" << coefficient << ")";
		}
		else
		{
			output << coefficient;
		}

		if (exponent != 0)
		{
			output << "x^" << exponent;
		}
	}
	return output;
}
*/

/*
 * monomial.cpp
 *
 *  Created on: Mar 15, 2015
 *      Author: erik
 */

#include "monomial.h"

/*
 * Default constructor
 * sets both private data members equal to zero
 *
 * @return monomial		returns the newly constructed monomial object
 */
monomial::monomial() :
		coefficient(0), exponent(0)
{
}

/*
 * Constructor
 *
 * @param coeff		double saved as coefficient data member
 * @param exp		int saved as exponent data member
 * @return monomial		returns the newly constructed monomial object
 */
monomial::monomial(double coeff, const int exp) :
		coefficient(coeff), exponent(exp)
{
}

/*
 * Copy constructor
 *
 * @param right		monomial const reference to the monomial object to be copied
 * @return monomial		returns the newly constructed monomial object
 */
monomial::monomial(const monomial& right) :
		coefficient(right.coefficient), exponent(right.exponent)
{
}

/*
 * Destructor
 * Data members are primitives, so nothing should be necessary here.
 */
monomial::~monomial()
{
}

/*
 * Equality operator
 * Returns true if the private data members of right are identical to the
 * values in *this
 *
 * @param right		monomial const reference to the monomial object to be compared to *this
 * @return bool		true/1 if equal, false/0 if unequal
 */
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

/*
 * Assignment operator
 * Checks that *this and right are not the same object. If not, copies private
 * data members from right to the same variables in *this.
 *
 * @param right		monomial const reference to the monomial object to be copied
 * @return monomial		returns a reference to *this
 */
monomial& monomial::operator=(const monomial& right)
{
	if (!(*this == right))
	{
		this->coefficient = right.coefficient;
		this->exponent = right.exponent;
	}
	return *this;
}

/*
 * Finds the derivative of this term
 * These are assumed to be individual simple polynomial terms, so to find the
 * derivative:
 * coefficient = coefficient * exponent;
 * exponent = exponent - 1;
 *
 * Should not need to be checked for >, <, or == to 0, because once the coeff
 * is zero, the whole term will continue to evaluate to zero, and coefficient
 * will remain zero if finding higher order derivatives.
 *
 * @return void
 */
void monomial::monoDerivative()
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

/*
 * Overwrites data members with new values
 *
 * @param coeff		double saved as coefficient data member
 * @param exp		int saved as exponent data member
 * @return void
 */
void monomial::setMonomial(const double coeff, const int exp)
{
	coefficient = coeff;
	exponent = exp;
}

/*
 * Output stream operator
 * Takes the intended output stream and the monomial to be printed (so that
 * it is accepted as an rvalue) as paramters.
 *
 * @param output	std::ostream reference to the desired output stream
 * @param m			monomial const reference (rvalue) to the monomial to be printed
 * @return std::ostream		reference to the output stream so that operators can be chained together
 */
std::ostream& operator<<(std::ostream& output, const monomial& m)
{
	if (m.getCoefficient() != 0)
	{
		if (m.getCoefficient() < 0)
		{
			output << "(" << m.getCoefficient() << ")";
		}
		else if (m.getCoefficient() == 1)
		{
		}
		else
		{
			output << m.getCoefficient();
		}

		switch (m.getExponent())
		{
		case 1:
			output << "x";
			break;
		case 0:
			break;
		default:
			output << "x^" << m.getExponent();
			break;
		}

		/*
		 if (m.getExponent() != 0)
		 {
		 output << "x^" << m.getExponent();
		 }
		 */
	}
	return output;
}

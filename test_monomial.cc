/*
 * test_monomial.cc
 *
 *  Created on: Mar 15, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include "monomial.h"
#include <iostream>
#include <sstream>
#include <string>

class monomialTests: public ::testing::Test
{
public:

	monomialTests()
	{

	}

	virtual ~monomialTests()
	{

	}
};

TEST_F (monomialTests, defaultConstructor)
{
	monomial testDefault;

	EXPECT_EQ(0, testDefault.getCoefficient());
	EXPECT_EQ(0, testDefault.getExponent());
}

TEST_F (monomialTests, constructor)
{
	monomial testMonomial(5, 2);

	EXPECT_EQ(5, testMonomial.getCoefficient());
	EXPECT_EQ(2, testMonomial.getExponent());
}

TEST_F (monomialTests, copyConstructor)
{
	monomial testMonomial(5, 2);

	EXPECT_EQ(5, testMonomial.getCoefficient());
	EXPECT_EQ(2, testMonomial.getExponent());

	monomial testCopy(testMonomial);
	EXPECT_EQ(5, testCopy.getCoefficient());
	EXPECT_EQ(2, testCopy.getExponent());
}

TEST_F (monomialTests, assignment)
{
	monomial testMonomial(5, 2);

	EXPECT_EQ(5, testMonomial.getCoefficient());
	EXPECT_EQ(2, testMonomial.getExponent());

	monomial testCopy;
	EXPECT_EQ(0, testCopy.getCoefficient());
	EXPECT_EQ(0, testCopy.getExponent());

	testCopy = testMonomial;
	EXPECT_EQ(5, testCopy.getCoefficient());
	EXPECT_EQ(2, testCopy.getExponent());
}

TEST_F (monomialTests, equality)
{
	monomial testMonomial(5, 2);

	EXPECT_EQ(5, testMonomial.getCoefficient());
	EXPECT_EQ(2, testMonomial.getExponent());

	monomial testCopy;
	EXPECT_EQ(0, testCopy.getCoefficient());
	EXPECT_EQ(0, testCopy.getExponent());

	EXPECT_FALSE(testMonomial == testCopy);

	testCopy = testMonomial;
	EXPECT_EQ(5, testCopy.getCoefficient());
	EXPECT_EQ(2, testCopy.getExponent());

	EXPECT_TRUE(testMonomial == testCopy);
}

TEST_F (monomialTests, setMonomial)
{
	monomial testMonomial(5, 2);

	EXPECT_EQ(5, testMonomial.getCoefficient());
	EXPECT_EQ(2, testMonomial.getExponent());

	testMonomial.setMonomial(6.5, 3);

	EXPECT_EQ(6.5, testMonomial.getCoefficient());
	EXPECT_EQ(3, testMonomial.getExponent());
}

TEST_F (monomialTests, monoDerivative)
{
	monomial testMonomial(5, 2);

	EXPECT_EQ(5, testMonomial.getCoefficient());
	EXPECT_EQ(2, testMonomial.getExponent());

	testMonomial.monoDerivative();

	EXPECT_EQ(10, testMonomial.getCoefficient());
	EXPECT_EQ(1, testMonomial.getExponent());

	testMonomial.monoDerivative();

	EXPECT_EQ(10, testMonomial.getCoefficient());
	EXPECT_EQ(0, testMonomial.getExponent());

	testMonomial.monoDerivative();

	EXPECT_EQ(0, testMonomial.getCoefficient());
	EXPECT_EQ(-1, testMonomial.getExponent());

	testMonomial.monoDerivative();

	EXPECT_EQ(0, testMonomial.getCoefficient());
	EXPECT_EQ(-2, testMonomial.getExponent());

	testMonomial.setMonomial(3.5, -1);

	EXPECT_EQ(3.5, testMonomial.getCoefficient());
	EXPECT_EQ(-1, testMonomial.getExponent());

	testMonomial.monoDerivative();

	EXPECT_EQ(-3.5, testMonomial.getCoefficient());
	EXPECT_EQ(-2, testMonomial.getExponent());
}

TEST_F (monomialTests, print)
{
	std::string expected("5x^2\n");
	monomial testMonomial(5,2);
	std::cerr << "Monomial print test getCoefficient(): " << testMonomial.getCoefficient() << std::endl;
	std::cerr << "Monomial print test getExponent(): " << testMonomial.getExponent() << std::endl;

	std::ostringstream testOutput;

	testOutput << testMonomial << std::endl;
	std::cerr << testMonomial << std::endl;

	std::string actual = testOutput.str();

	EXPECT_EQ(expected, actual);
}

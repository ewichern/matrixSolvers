/*
 * test_rootDriverFunction.cc
 *
 *  Created on: Feb 7, 2015
 *      Author: erik
 */

#include <streambuf>
#include <ctime>
#include <iostream>
#include <sstream>

#include "gtest/gtest.h"

#include "rootDriverFunctions.cpp"

using namespace std;

class rootDriverFunctionTests: public ::testing::Test
{
public:

	rootDriverFunctionTests()
	{

	}

	virtual ~rootDriverFunctionTests()
	{

	}

};

TEST_F (rootDriverFunctionTests, printRootMenuOptions)
{
	int menuOutput = 999;

	stringstream input("20 \n 4");
	menuOutput = printRootMenuOptions(input);
	EXPECT_EQ(4, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str("-414 \n 3");
	menuOutput = printRootMenuOptions(input);
	EXPECT_EQ(3, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str("asdf;aadsf -01234=5 \n 2");
	menuOutput = printRootMenuOptions(input);
	EXPECT_EQ(2, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str("9999 \n 1");
	menuOutput = printRootMenuOptions(input);
	EXPECT_EQ(1, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

}

/*
 * @param is istream&
 * @return is std::vector<double> with the data to create a new polynomial
 */
TEST_F (rootDriverFunctionTests, getExpression)
{
	std::vector<double> expected1
	{ -21, -5, 4 };
	std::stringstream input1("-21 -5 4 end");

	std::vector<double> expected2
	{ 100, -10, 1, 444, 0 };
	std::stringstream input2("100 -10 1 444 0 end");

	std::vector<double> actual1 = getExpression(input1);
	std::vector<double> actual2 = getExpression(input2);

	auto itActual = actual1.begin();
	for (auto itExpected = expected1.begin(); itExpected != expected1.end(); ++itExpected)
	{
		std::cerr << "expected1: " << *itExpected << "\n";
		std::cerr << "actual1: " << *itActual << "\n";
		EXPECT_EQ(*itExpected, *itActual);
		++itActual;
	}
	itActual = actual2.begin();
	for (auto itExpected = expected2.begin(); itExpected != expected2.end(); ++itExpected)
	{
		std::cerr << "expected2: " << *itExpected << "\n";
		std::cerr << "actual2: " << *itActual << "\n";
		EXPECT_EQ(*itExpected, *itActual);
		++itActual;
	}

}

TEST_F (rootDriverFunctionTests, getBrackets)
{
	double lower = 0;
	double upper = 0;

	std::stringstream input1("-33 50 \n");
	double expectedLower1 = -33;
	double expectedUpper1 = 50;

	getBrackets(lower, upper, input1);

	EXPECT_EQ(expectedLower1, lower);
	EXPECT_EQ(expectedUpper1, upper);

	std::stringstream invalidInputFirst("5 -10 \n -99 99");

	double expectedLowerAfterInvalid = -99;
	double expectedUpperAfterInvalid = 99;

	getBrackets(lower, upper, invalidInputFirst);

	EXPECT_EQ(expectedLowerAfterInvalid, lower);
	EXPECT_EQ(expectedUpperAfterInvalid, upper);

}

TEST_F (rootDriverFunctionTests, getRootGuess)
{
//TODO write test
}

TEST_F (rootDriverFunctionTests, getRootSolverName)
{
//TODO write test
}

TEST_F (rootDriverFunctionTests, executeRootSolver)
{
//TODO write test
}

/*
 * test_rootDriverFunction.cc
 *
 *  Created on: Feb 7, 2015
 *      Author: erik
 */

#include <streambuf>
#include <ctime>

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

TEST_F (rootDriverFunctionTests, getExpression)
{
	//TODO write test
}

TEST_F (rootDriverFunctionTests, getBrackets)
{
	//TODO write test
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

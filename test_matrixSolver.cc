/*
 * test_matrixSolver.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: erik
 */

#include "sparseMatrix.h"
#include "matrixGenerator.h"
#include "IterativeSolvers.h"
#include <streambuf>
#include <ctime>

#include "gtest/gtest.h"

#include "matrixSolver.cpp"

using namespace std;

class matrixSolverTests: public ::testing::Test
{
public:

	matrixSolverTests()
	{

	}

	virtual ~matrixSolverTests()
	{

	}

};

TEST_F (matrixSolverTests, printMenuOptions)
{
	int menuOutput = 999;

	stringstream input("0 \n 4");
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(4, menuOutput);
	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str("-414 \n 3");
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(3, menuOutput);
	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str("asdf;aadsf -01234=5 \n 2");
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(2, menuOutput);
	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str("9999 \n 1");
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(1, menuOutput);
	std::cerr << "menuOutput: " << menuOutput << endl;

}

TEST_F (matrixSolverTests, getFilename)
{
	string output = "";

	stringstream input("googleTestGetFilename");
	output = getFilename(input);

	EXPECT_EQ("googleTestGetFilename", output);
}

TEST_F (matrixSolverTests, getFilenameRoot)
{
	string output = "";

	stringstream input("googleTestGetFilename");
	output = getFilenameRoot(input);

	EXPECT_EQ("googleTestGetFilename", output);
}

TEST_F (matrixSolverTests, getInputFilename)
{
	string output = "";

	stringstream input("googleTestGetFilename");
	output = getInputFilename(input);

	EXPECT_EQ("googleTestGetFilename", output);
}

TEST_F (matrixSolverTests, generateMatrixDataFiles)
{
	int m = 6, n = 6;
	string filenameInput = "googleTestGeneratorFilename";

	string filenameOutput = "";
	stringstream input;

	input << m << " " << n << " \n " << filenameInput;
	filenameOutput = generateMatrixDataFiles(input);

	ifstream fileTest(filenameOutput + "_Ab.dat");

	EXPECT_TRUE(fileTest.is_open());
	EXPECT_EQ(filenameInput, filenameOutput);

	matrix A, b;

	MatrixGenerator::readMatrixFromFile(fileTest, A, b);

	tuple<int, int> aSize (A.numrows(), A.numcols());
	tuple<int, int> bSize (b.numrows(), b.numcols());
	tuple<int, int> aExpected (m, n);
	tuple<int, int> bExpected (n, 1);

	EXPECT_TRUE (aExpected == aSize);
	EXPECT_TRUE (bExpected == bSize);

}

TEST_F (matrixSolverTests, executeIterativeSolver)
{

	int m = 6, n = 6;
	string filenameInput = "jacobiTest";

	string filenameOutput = "";
	stringstream input;

	input << m << " " << n << " \n " << filenameInput;
	filenameOutput = generateMatrixDataFiles(input);

	ifstream fileTest(filenameOutput + "_Ab.dat");

	EXPECT_TRUE(fileTest.is_open());
	EXPECT_EQ(filenameInput, filenameOutput);

	matrix A, x, b;

	MatrixGenerator::readMatrixFromFile(fileTest, A, b);

	tuple<int, int> aSize (A.numrows(), A.numcols());
	tuple<int, int> bSize (b.numrows(), b.numcols());
	tuple<int, int> aExpected (m, n);
	tuple<int, int> bExpected (n, 1);

	EXPECT_TRUE (aExpected == aSize);
	EXPECT_TRUE (bExpected == bSize);

	int numIterations = -1;

	numIterations = executeIterativeSolver(0, A, x, b);

	EXPECT_NE (-1, numIterations);

}



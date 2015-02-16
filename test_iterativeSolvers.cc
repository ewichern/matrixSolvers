/*
 * test_iterativeSolvers.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#include "IterativeSolvers.h"

#include "gtest/gtest.h"
#include <fstream>
#include <exception>
#include <random>
#include <string>

#include "sparseMatrix.h"
#include "matrixGenerator.h"

typedef sparseMatrix<double> matrix;

using namespace std;

class iterativeSolverTests: public ::testing::Test
{
public:
	matrix A1, b1, x1, A2, b2, x2;

	iterativeSolverTests()
	{

		string testFile1 = "sampleData1";

		ifstream a1b1input(testFile1 + "Ab.dat");
		ifstream x1input(testFile1 + "x.dat");

		MatrixGenerator::readMatrixFromFile(a1b1input, A1, b1);
		a1b1input.close();

		MatrixGenerator::readMatrixFromFile(x1input, x1);
		x1input.close();

		string testFile2 = "sampleData2";

		ifstream a2b2input(testFile2 + "Ab.dat");
		ifstream x2input(testFile2 + "x.dat");

		MatrixGenerator::readMatrixFromFile(a2b2input, A2, b2);
		a2b2input.close();

		MatrixGenerator::readMatrixFromFile(x2input, x2);
		x2input.close();

	}

	virtual ~iterativeSolverTests()
	{

	}

};

TEST_F (iterativeSolverTests, jacobiSolver1)
{
	matrix x1test(A1.numcols(), 1, 0.1);
	IterativeSolvers::jacobiSolver(A1, x1test, b1);

	double errLimit = 0.000001;
	double err1 = relError(x1test, x1);
	cerr << "Calculated relative error: " << endl << err1 << endl;

	EXPECT_LT(err1, errLimit);

}

TEST_F (iterativeSolverTests, jacobiSolver2)
{
	matrix x2test(A2.numcols(), 1, 0.1);
	IterativeSolvers::jacobiSolver(A2, x2test, b2);

	double errLimit = 0.000001;
	double err2 = relError(x2test, x2);
	cerr << "Calculated relative error: " << endl << err2 << endl;

	EXPECT_LT(err2, errLimit);

}

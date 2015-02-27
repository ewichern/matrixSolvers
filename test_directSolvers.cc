/*
 * test_directSolvers.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#include "directSolvers.h"

#include "gtest/gtest.h"
#include <fstream>
#include <exception>
#include <random>
#include <string>

#include "denseMatrix.h"
#include "matrixGenerator.h"

typedef denseMatrix<double> matrix;

using namespace std;

class directSolverTests: public ::testing::Test
{
public:
	matrix A1, b1, x1, A2, b2, x2;

	directSolverTests()
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

	virtual ~directSolverTests()
	{

	}

};

TEST_F (directSolverTests, findPivot)
{
	int pivot = -1;

	pivot = directSolvers::findPivot(A2, 0);
	EXPECT_EQ(0, pivot);

	pivot = directSolvers::findPivot(A2, 1);
	EXPECT_EQ(1, pivot);

	pivot = directSolvers::findPivot(A2, 2);
	EXPECT_EQ(2, pivot);

	pivot = directSolvers::findPivot(A2, 3);
	EXPECT_EQ(3, pivot);
}

/**
TEST_F (iterativeSolverTests, jacobi1)
{
	matrix x1test(A1.numcols(), 1, 1.0);
	int numIterations = IterativeSolvers::jacobi(A1, x1test, b1);

	double errLimit = 0.00005;
	double err1 = relError(x1test, x1);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err1 << endl;

	EXPECT_LT(err1, errLimit);

}
*/


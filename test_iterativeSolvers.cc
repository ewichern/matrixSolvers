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

#include "denseMatrix.h"
#include "augMatrix.h"
#include "matrixGenerator.h"

typedef denseMatrix<double> matrix;

using namespace std;

class iterativeSolverTests: public ::testing::Test
{
public:
	matrix A1, b1, x1, A2, b2, x2;

	iterativeSolverTests()
	{
		string testFile1 = "sampleData1";
		string testFile2 = "sampleData2";

		std::ifstream aOneInput(testFile1 + "A.dat");
		std::ifstream xOneInput(testFile1 + "x.dat");
		std::ifstream bOneInput(testFile1 + "B.dat");
		std::ifstream aTwoInput(testFile2 + "A.dat");
		std::ifstream xTwoInput(testFile2 + "x.dat");
		std::ifstream bTwoInput(testFile2 + "B.dat");

		A1.setDenseMatrix(aOneInput);
		aOneInput.close();
		b1.setDenseMatrix(bOneInput);
		x1.setDenseMatrix(xOneInput);

		A2.setDenseMatrix(aTwoInput);
		aTwoInput.close();
		b2.setDenseMatrix(bTwoInput);
		x2.setDenseMatrix(xTwoInput);

		xOneInput.close();
		bOneInput.close();
		xTwoInput.close();
		bTwoInput.close();

	}

	virtual ~iterativeSolverTests()
	{

	}

};

TEST_F (iterativeSolverTests, jacobi1)
{
	matrix x1test(A1.numcols(), 1, 1.0);
	int numIterations = IterativeSolvers::jacobi(A1, x1test, b1);

	double errLimit = 0.00001;
	double err1 = relError(x1test, x1);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err1 << endl;

	EXPECT_LT(err1, errLimit);

}

TEST_F (iterativeSolverTests, jacobi2)
{
	matrix x2test(A2.numcols(), 1, 1.0);
	int numIterations = IterativeSolvers::jacobi(A2, x2test, b2);

	double errLimit = 0.00001;
	double err2 = relError(x2test, x2);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err2 << endl;

	EXPECT_LT(err2, errLimit);

}

TEST_F (iterativeSolverTests, gaussSeidel1)
{
	matrix x1test(A1.numcols(), 1, 1.0);
	int numIterations = IterativeSolvers::gaussSeidel(A1, x1test, b1);

	double errLimit = 0.00001;
	double err1 = relError(x1test, x1);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err1 << endl;

	EXPECT_LT(err1, errLimit);

}

TEST_F (iterativeSolverTests, gaussSeidel2)
{
	matrix x2test(A2.numcols(), 1, 1.0);
	int numIterations = IterativeSolvers::gaussSeidel(A2, x2test, b2);

	double errLimit = 0.00001;
	double err2 = relError(x2test, x2);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err2 << endl;

	EXPECT_LT(err2, errLimit);

}

TEST_F (iterativeSolverTests, successiveOverRelaxing)
{
	matrix x1test(A1.numcols(), 1, 1.0);

	double omega = 1.05;

	int numIterations = IterativeSolvers::successiveOverRelaxing(omega, A1, x1test, b1);

	double errLimit = 0.00001;
	double err1 = relError(x1test, x1);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err1 << endl;

	EXPECT_LT(err1, errLimit);

}

TEST_F (iterativeSolverTests, successiveOverRelaxing2)
{
	matrix x2test(A2.numcols(), 1, 1.0);

	double omega = 0.9;


	int numIterations = IterativeSolvers::successiveOverRelaxing(omega, A2, x2test, b2);

	double errLimit = 0.00001;
	double err2 = relError(x2test, x2);
	cerr << "numIterations: " << numIterations << endl;
	cerr << "Calculated relative error: " << endl << err2 << endl;

	EXPECT_LT(err2, errLimit);

}


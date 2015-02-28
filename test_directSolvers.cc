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

TEST_F (directSolverTests, gaussianElimination)
{
	matrix x2test(A2.numrows(), 1, 1.0);
	directSolvers::gaussianElimination(A2, x2test, b2);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.000001;
	double err1 = relError(x2test, x2);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, gaussianElimination2)
{
	matrix morrisA, morrisX, morrisB;

	ifstream morrisSample("SAMPLEdata.txt");
	ifstream morrisSol("SAMPLEsol.txt");

	MatrixGenerator::readMatrixFromFile(morrisSample, morrisA, morrisB);
	MatrixGenerator::readMatrixFromFile(morrisSol, morrisX);

	matrix morrisXtest(morrisA.numrows(), 1);

	directSolvers::gaussianElimination(morrisA, morrisXtest, morrisB);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.00001;
	double err1 = relError(morrisX, morrisXtest);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}


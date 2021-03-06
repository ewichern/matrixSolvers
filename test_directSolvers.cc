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
	const char* data1AB = "testData/sampleData1Ab.dat";
	const char* data1x = "testData/sampleData1x.dat";
	const char* data2AB = "testData/sampleData2Ab.dat";
	const char* data2x = "testData/sampleData2x.dat";
	const char* identity = "testData/eye.dat";
	const char* identityTimes2 = "testData/eyeTimes2.dat";
	const char* morrisData = "testData/SAMPLEdata.txt";
	const char* morrisXsol = "testData/SAMPLEsol.txt";


	directSolverTests()
	{

		ifstream a1b1input(data1AB);
		ifstream x1input(data1x);

		MatrixGenerator::readMatrixFromFile(a1b1input, A1, b1);
		a1b1input.close();

		MatrixGenerator::readMatrixFromFile(x1input, x1);
		x1input.close();

		ifstream a2b2input(data2AB);
		ifstream x2input(data2x);

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

	ifstream morrisSample(morrisData);
	ifstream morrisSol(morrisXsol);

	MatrixGenerator::readMatrixFromFile(morrisSample, morrisA, morrisB);
	MatrixGenerator::readMatrixFromFile(morrisSol, morrisX);
	morrisSample.close();
	morrisSol.close();

	matrix morrisXtest(morrisA.numrows(), 1);

	directSolvers::gaussianElimination(morrisA, morrisXtest, morrisB);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.00001;
	double err1 = relError(morrisX, morrisXtest);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, LUdecomposition)
{
	matrix x1test(A1.numrows(), 1, 1.0);
	directSolvers::LUdecomposition(A1, x1test, b1);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.000001;
	double err1 = relError(x1test, x1);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, LUdecomposition1)
{
	matrix x2test(A2.numrows(), 1, 1.0);
	directSolvers::LUdecomposition(A2, x2test, b2);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.000001;
	double err1 = relError(x2test, x2);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, LUdecomposition2)
{
	matrix morrisA, morrisX, morrisB;

	ifstream morrisSample(morrisData);
	ifstream morrisSol(morrisXsol);

	MatrixGenerator::readMatrixFromFile(morrisSample, morrisA, morrisB);
	MatrixGenerator::readMatrixFromFile(morrisSol, morrisX);
	morrisSample.close();
	morrisSol.close();

	matrix morrisXtest(morrisA.numrows(), 1);

	directSolvers::LUdecomposition(morrisA, morrisXtest, morrisB);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.00001;
	double err1 = relError(morrisX, morrisXtest);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

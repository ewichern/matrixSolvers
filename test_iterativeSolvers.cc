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
#include "matrixGenerator.h"

typedef denseMatrix<double> matrix;

using namespace std;

class iterativeSolverTests: public ::testing::Test
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
	const char* unitTest = "testData/unitTest.dat";
	string filenameRoot = "testData/unitTest";

	iterativeSolverTests()
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


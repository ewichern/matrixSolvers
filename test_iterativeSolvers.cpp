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
	matrix A1, b1, x1;

	iterativeSolverTests()
	{

		string testFile = "sampleData1";

		ifstream a1b1input(testFile+"Ab.dat");
		ifstream x1input(testFile+"x.dat");

		MatrixGenerator::readMatrixFromFile(a1b1input, A1, b1);
		a1b1input.close();

		MatrixGenerator::readMatrixFromFile(x1input, x1);
		x1input.close();

	}

	virtual ~iterativeSolverTests()
	{

	}

};

TEST_F (iterativeSolverTests, jacobiSolver)
{
	matrix x1test = IterativeSolvers::jacobiSolver(A1, b1);

	double errLimit = 0.00001;
	double err = relError(x1test, x1);
	cerr << "Calculated relative error: " << endl << err << endl;

	EXPECT_LT(err, errLimit);
}

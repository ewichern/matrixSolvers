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
#include "augMatrix.h"
#include "matrixGenerator.h"

typedef denseMatrix<double> matrix;

using namespace std;

class directSolverTests: public ::testing::Test {
public:
	matrix A1, b1, x1, A2, b2, x2;

	directSolverTests() {
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

	virtual ~directSolverTests() {

	}

};

TEST_F (directSolverTests, findPivot) {
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

TEST_F (directSolverTests, gaussianElimination) {
	matrix x2test(A2.numrows(), 1, 1.0);
	directSolvers::gaussianElimination(A2, x2test, b2);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.000001;
	double err1 = x2.relError(x2test);
//	double err1 = relError(x2test, x2);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, gaussianElimination2) {
//	matrix morrisA, morrisX, morrisB;
	augMatrix morris;
	matrix morrisX;

	ifstream morrisSample("SAMPLEdata.txt");
	ifstream morrisSol("SAMPLEsol.txt");

//	MatrixGenerator::readMatrixFromFile(morrisSample, morrisA, morrisB);
//	MatrixGenerator::readMatrixFromFile(morrisSol, morrisX);
	morris.setAugMatrix(morrisSample);
	morrisX.setDenseMatrix(morrisSol);

	matrix morrisXtest(morris.numrows(), 1);

	matrix morrisA = morris.getA();
	matrix morrisB = morris.getB();

	directSolvers::gaussianElimination(morrisA, morrisXtest, morrisB);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.00001;
	double err1 = morrisX.relError(morrisXtest);
//	double err1 = relError(morrisX, morrisXtest);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, LUdecomposition) {
	matrix x1test(A1.numrows(), 1, 1.0);
	directSolvers::LUdecomposition(A1, x1test, b1);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.000001;
	double err1 = x1.relError(x1test);
//	double err1 = relError(x1test, x1);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, LUdecomposition1) {
	matrix x2test(A2.numrows(), 1, 1.0);
	directSolvers::LUdecomposition(A2, x2test, b2);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.000001;
	double err1 = x2.relError(x2test);
//	double err1 = relError(x2test, x2);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

TEST_F (directSolverTests, LUdecomposition2) {
//	matrix morrisA, morrisX, morrisB;
	augMatrix morris;
	matrix morrisX;

	ifstream morrisSample("SAMPLEdata.txt");
	ifstream morrisSol("SAMPLEsol.txt");

//	MatrixGenerator::readMatrixFromFile(morrisSample, morrisA, morrisB);
//	MatrixGenerator::readMatrixFromFile(morrisSol, morrisX);
	morris.setAugMatrix(morrisSample);
	morrisX.setDenseMatrix(morrisSol);

	matrix morrisXtest(morris.numrows(), 1);

	matrix morrisA = morris.getA();
	matrix morrisB = morris.getB();

	directSolvers::LUdecomposition(morrisA, morrisXtest, morrisB);

//	EXPECT_TRUE(x2 == x2test);
	double errLimit = 0.00001;
	double err1 = morrisX.relError(morrisXtest);
//	double err1 = relError(morrisX, morrisXtest);
	cerr << "Calculated relative error: " << endl << err1 << endl;
	EXPECT_LT(err1, errLimit);
}

/*
 * test_matrixGenerator.cc
 *
 *  Created on: Jan 21, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include <fstream>
#include <exception>
#include <random>
#include <string>

#include "denseMatrix.h"
#include "matrixGenerator.h"

typedef denseMatrix<double> matrix;

using namespace std;

class matrixGeneratorTests: public ::testing::Test
{
public:
	matrix A1, b1;

	matrixGeneratorTests()
	{

	}

	virtual ~matrixGeneratorTests()
	{

	}

};

TEST_F (matrixGeneratorTests, constructor)
{

}

TEST_F (matrixGeneratorTests, randomFillMatrix)
{
	// TODO I'm in the middle of rewriting the matrixGenerator class
	// should only contain randomFillMatrix and generateSamples
	// class has a data structure now to hold all the parameters that
	// were being passed

	matrix mat1 = matrix(3, 3, 0.0);
	matrix mat2 = matrix(3, 3, 0.0);

	EXPECT_EQ(mat1, mat2);

	MatrixGenerator matGen;




}
/*
TEST_F (matrixGeneratorTests, generateSamples)
{

	string filenameRoot = "unitTest";


	MatrixGenerator::generateSamples<distribType>(6, 6, filenameRoot);

	matrix A1test, x1test, b1test, b1calc;

	ifstream input1(filenameRoot + "_Ab.dat");
	MatrixGenerator::readMatrixFromFile(input1, A1test, b1test);
	input1.close();

	ifstream input2(filenameRoot + "_x.dat");
	MatrixGenerator::readMatrixFromFile(input2, x1test);
	input2.close();

	b1calc = A1test * x1test;

//	std::cerr << "b1test: " << endl << b1test;
//	std::cerr << "b1calc: " << endl	<< b1calc;

	double errLimit = 0.00001;
	double err = relError(b1test, b1calc);
//	cerr << "Calculated relative error: " << err << endl;

	EXPECT_LT(err, errLimit);

	//EXPECT_EQ(b1test, b1calc);
}
*/

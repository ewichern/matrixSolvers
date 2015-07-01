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

class matrixGeneratorTests: public ::testing::Test {
public:
	matrix A1, b1;

	matrixGeneratorTests() {

	}

	virtual ~matrixGeneratorTests() {

	}

};

TEST_F (matrixGeneratorTests, constructor) {
	string filename = "sampleData1Ab.dat";
	std::ifstream input(filename);

	augMatrix mat(input);
	MatrixGenerator matGen1;
	MatrixGenerator matGen2(mat);

	EXPECT_TRUE(matGen1.exists());
	EXPECT_TRUE(matGen2.exists());

}

TEST_F (matrixGeneratorTests, randomFillMatrix) {
	matrix mat1 = matrix(3, 3, 0.0);
	matrix mat2 = matrix(3, 3, 0.0);

	EXPECT_EQ(mat1, mat2);

	MatrixGenerator matGen;

	matGen.randomFillMatrix(mat2);

	EXPECT_NE(mat1, mat2);
}

TEST_F (matrixGeneratorTests, generateSamples) {
	string filename = "sampleData1Ab.dat";
	string filenameA = "sampleData1A.dat";
	string filenameB = "sampleData1B.dat";

	std::ifstream augInput(filename);
	std::ifstream aInput(filenameA);
	std::ifstream bInput(filenameB);

	augMatrix augMat(augInput);
	matrix testA(aInput);
	matrix testB(bInput);

	matrix& matA = augMat.getA();
	matrix& matB = augMat.getB();
	EXPECT_EQ(testA, matA);
	EXPECT_EQ(testB, matB);

	MatrixGenerator matGen(augMat);

	string outputRoot = "unitTestGenerateSamples";
	matGen.generateSamples(3, 3, outputRoot);

	EXPECT_NE(testA, matA);
	EXPECT_NE(testB, matB);

	std::ifstream abInput(outputRoot+"AB.dat");
	std::ifstream xInput(outputRoot+"X.dat");

	augMatrix testAB(abInput);
	matrix testX(xInput);

	matrix computeB = testAB.getA() * testX;
	matrix& expectedB = testAB.getB();

	double error = computeB.relError(expectedB);

	EXPECT_LT(error, 0.00001);
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

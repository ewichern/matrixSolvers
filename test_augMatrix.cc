/*
 * test_augMatrix.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include <fstream>
#include <exception>
#include <random>
#include <string>

#include "denseMatrix.h"
#include "augMatrix.h"

typedef denseMatrix<double> matrix;

using namespace std;

class augMatrixTests: public ::testing::Test {
public:
	augMatrix test1;
	int m, n;
	matrix id, x, b, idTest, xTest, bTest;

	augMatrixTests() {

		m = 3;
		n = 3;

		id.eye(m, n);
		x = matrix(m, 1, 2);
		b = matrix(m, 1, 2);

		test1 = augMatrix(id, x, b);
	}

	virtual ~augMatrixTests() {

	}

};

TEST_F (augMatrixTests, constructorDefault) {
	augMatrix* testAug = new augMatrix();

	EXPECT_TRUE(testAug);
	EXPECT_EQ(0, testAug->numrows());
	EXPECT_EQ(0, testAug->numcols());

	delete testAug;
}

TEST_F (augMatrixTests, constructorMatrices) {
	augMatrix* testAug1 = new augMatrix(id, x, b);
	augMatrix* testAug2 = new augMatrix(id, b);

	EXPECT_TRUE(testAug1);
	EXPECT_EQ(3, testAug1->numrows());
	EXPECT_EQ(3, testAug1->numcols());

	EXPECT_TRUE(testAug2);
	EXPECT_EQ(3, testAug2->numrows());
	EXPECT_EQ(3, testAug2->numcols());

	delete testAug1;
	delete testAug2;
}

TEST_F (augMatrixTests, equality) {
	augMatrix testAug2 = augMatrix(id, x, b);
	augMatrix testAug1 = augMatrix(id, x, b);
	augMatrix testAug0 = augMatrix();

	EXPECT_TRUE((testAug2 == testAug1));
	EXPECT_FALSE((testAug2 == testAug0));
}

TEST_F (augMatrixTests, notEquals) {
	augMatrix testAug2 = augMatrix(id, x, b);
	augMatrix testAug1 = augMatrix(id, x, b);
	augMatrix testAug0 = augMatrix();

	EXPECT_FALSE((testAug2 != testAug1));
	EXPECT_TRUE((testAug2 != testAug0));
}

TEST_F (augMatrixTests, getters) {
	augMatrix testAug = augMatrix(id, x, b);

	idTest = testAug.getA();
	xTest = testAug.getX();
	bTest = testAug.getB();

	EXPECT_EQ(id, idTest);
	EXPECT_EQ(x, xTest);
	EXPECT_EQ(b, bTest);

}

TEST_F (augMatrixTests, setters) {
	augMatrix testAug, testAug2;
	string filePrefix = "sampleData1";

	idTest = testAug.getA();
	xTest = testAug.getX();
	bTest = testAug.getB();

	EXPECT_NE(id, idTest);
	EXPECT_NE(x, xTest);
	EXPECT_NE(b, bTest);

	testAug.setA(id);
	testAug.setX(x);
	testAug.setB(b);

	idTest = testAug.getA();
	xTest = testAug.getX();
	bTest = testAug.getB();

	EXPECT_EQ(id, idTest);
	EXPECT_EQ(x, xTest);
	EXPECT_EQ(b, bTest);

	std::ifstream Ainput(filePrefix + "A.dat");
	std::ifstream Binput(filePrefix + "B.dat");
	std::ifstream Xinput(filePrefix + "x.dat");

	matrix A2(Ainput);
	matrix B2(Binput);
	matrix X2(Xinput);

	Ainput.close();
	Binput.close();
	Xinput.close();

	Ainput.open(filePrefix + "A.dat");
	Binput.open(filePrefix + "B.dat");
	Xinput.open(filePrefix + "x.dat");

	testAug2.setA(Ainput);
	testAug2.setB(Binput);
	testAug2.setX(Xinput);

	Ainput.close();
	Binput.close();
	Xinput.close();

	matrix A2test = testAug2.getA();
	matrix B2test = testAug2.getB();
	matrix X2test = testAug2.getX();

	EXPECT_EQ(A2, A2test);
	EXPECT_EQ(B2, B2test);
	EXPECT_EQ(X2, X2test);
}

TEST_F (augMatrixTests, assignment) {
	augMatrix test2 = test1;

	EXPECT_EQ(test1, test2);
}

TEST_F (augMatrixTests, setAugMatrix) {
	ofstream inputDump("unitTestAugMatrix.dat");
	inputDump << "3 3\n" << id << b;
	inputDump.close();

	ifstream input("unitTestAugMatrix.dat");
	augMatrix testAug = augMatrix();
	testAug.setAugMatrix(input);
	input.close();

	idTest = testAug.getA();
	xTest = testAug.getX();
	bTest = testAug.getB();

	EXPECT_EQ(3, testAug.numrows());
	EXPECT_EQ(3, testAug.numcols());

	EXPECT_EQ(id, idTest);
	EXPECT_EQ(b, bTest);
}

TEST_F (augMatrixTests, filePrintAugMatrix) {
	ifstream input("sampleData1Ab.dat");
	augMatrix testAug = augMatrix(input);
	input.close();

	ofstream output("unitTestAugMatrix.dat");
	testAug.filePrintAugMatrix(output);
	output.close();

	ifstream inputTest("sampleData1Ab.dat");
	ifstream outputTest("unitTestAugMatrix.dat");

	double inNum = -1, outNum = -2;

	while ((inputTest >> inNum) && (outputTest >> outNum)) {
//		std::cerr << inNum << std::endl;
//		std::cerr << outNum << std::endl;

		EXPECT_DOUBLE_EQ(inNum, outNum);
		inNum = -1, outNum = -2;
	}
}

TEST_F (augMatrixTests, changeLocations) {
	const matrix& constA = test1.getA();
	const matrix& constX = test1.getX();
	const matrix& constB = test1.getB();

	EXPECT_EQ(constA[0][0], 1);
	EXPECT_EQ(constX[0][0], 2);
	EXPECT_EQ(constB[0][0], 2);

	matrix& A = test1.getA();
	matrix& X = test1.getX();
	matrix& B = test1.getB();

	A[0][0] = 3;
	X[0][0] = 3;
	B[0][0] = 3;

	EXPECT_EQ(constA[0][0], 3);
	EXPECT_EQ(constX[0][0], 3);
	EXPECT_EQ(constB[0][0], 3);
}

/*
 TEST_F (augMatrixTests, )
 {

 }

 TEST_F (augMatrixTests, writeToFile)
 {
 matrix id1, idTest;
 id1.eye(3, 3);

 ofstream output("unitAugTest.dat");
 MatrixGenerator::writeMatrixToFile(output, id1);
 output.close();

 ifstream input("unitTest.dat");
 MatrixGenerator::readMatrixFromFile(input, idTest);
 input.close();

 EXPECT_EQ(id1, idTest);
 }

 TEST_F (matrixGeneratorTests, writeToFile2)
 {
 matrix A1test, b1test;

 ofstream output("unitTest.dat");
 MatrixGenerator::writeMatrixToFile(output, A1, b1);
 output.close();

 ifstream input("unitTest.dat");
 MatrixGenerator::readMatrixFromFile(input, A1test, b1test);
 input.close();

 EXPECT_EQ(A1, A1test);
 EXPECT_EQ(b1, b1test);
 }

 TEST_F (matrixGeneratorTests, generateSamples)
 {

 typedef std::uniform_real_distribution<double> distribType;
 //typedef std::uniform_int_distribution<> distribType;

 double min = -100.0;
 double max = 100.0;
 string filenameRoot = "unitTest";

 std::random_device randDevice;
 std::mt19937 generator(randDevice());
 distribType dist(min, max);
 //distribType dist((int) min, (int) max);

 MatrixGenerator::generateSamples<distribType>(6, 6, filenameRoot, generator,
 dist);

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


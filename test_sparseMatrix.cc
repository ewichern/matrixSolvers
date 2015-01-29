/*
 * test_sparseMatrix.cpp
 *
 *  Created on: Jan 21, 2015
 *      Author: erik
 */

#include "sparseMatrix.h"
#include "matrixGenerator.h"
#include "gtest/gtest.h"
#include <fstream>
#include <exception>
#include <random>
#include <string>

typedef sparseMatrix<double> matrix;

namespace {

class sparseMatrixTests: public ::testing::Test {
public:
	matrix A1, A1again, A2, x1, x2, b1, b1again, b2;

	sparseMatrixTests() {

		ifstream a1b1input("sampleData1ab.dat");
		ifstream x1input("sampleData1x.dat");

		readMatrixFromFile(a1b1input, A1, b1);

		a1b1input.close();
		a1b1input.open("sampleData1ab.dat");

		readMatrixFromFile(a1b1input, A1again, b1again);
		readMatrixFromFile(x1input, x1);

		ifstream a2b2input("sampleData2ab.dat");
		ifstream x2input("sampleData2x.dat");

		readMatrixFromFile(a2b2input, A2, b2);
		readMatrixFromFile(x2input, x2);
	}

	virtual ~sparseMatrixTests() {

	}

};

TEST_F (sparseMatrixTests, equals) {
	matrix test1(1, 1, 0.0);

	EXPECT_EQ(test1, test1);
	EXPECT_EQ(A1, A1again);
	EXPECT_EQ(b1, b1);
}

TEST_F (sparseMatrixTests, not_equals) {
	matrix test1(1, 1, 0.0);
	matrix test2(2, 1, 0.0);
	matrix test3(1, 1, 1.0);

	EXPECT_NE(test1, test2);
	EXPECT_NE(test1, test3);

	EXPECT_NE(A1, A2);
}

TEST_F (sparseMatrixTests, copy) {
	matrix test1(1, 1, -1);

	matrix test1copy(test1);
	matrix A1copy(A1);
	matrix b1copy(b1);

	EXPECT_EQ(test1, test1copy);
	EXPECT_EQ(A1, A1copy);
	EXPECT_EQ(b1, b1copy);
}

TEST_F (sparseMatrixTests, assign) {
	matrix test1(1, 1, -1);
	matrix test1copy, A1copy, b1copy;

	test1copy = test1;
	A1copy = A1;
	b1copy = b1;

	EXPECT_EQ(test1, test1copy);
	EXPECT_EQ(A1, A1copy);
	EXPECT_EQ(b1, b1copy);
}

TEST_F (sparseMatrixTests, multiplyRight) {
	matrix b1test, b2test;

	try {
		b1test = A1 * x1;
	} catch (exception& e) {
		e.what();
	}

	try {
		b2test = A2 * x2;
	} catch (exception& e) {
		e.what();
	}

	EXPECT_EQ(b1, b1test);
	EXPECT_EQ(b2, b2test);
}

TEST_F (sparseMatrixTests, eye) {
	matrix id1, id2;
	id1.eye(3, 3);

	ifstream input("eye.dat");
	readMatrixFromFile(input, id2);
	input.close();

	EXPECT_EQ(id1, id2);
}

TEST_F (sparseMatrixTests, multiplyScaler) {
	matrix idtest, id1, id2;
	id1.eye(3, 3);
	idtest = 2 * id1;

	ifstream input("eyeTimes2.dat");
	readMatrixFromFile(input, id2);
	input.close();

	EXPECT_EQ(idtest, id2);

	idtest = id2 * 0.5;

	EXPECT_EQ(idtest, id1);
}

TEST_F (sparseMatrixTests, add) {
	matrix idtest, id1, id2;
	id1.eye(3, 3);
	id2.eye(3, 3);
	idtest = id1 + id2;

	ifstream input("eyeTimes2.dat");
	readMatrixFromFile(input, id2);
	input.close();

	EXPECT_EQ(idtest, id2);
}

TEST_F (sparseMatrixTests, subtract) {
	matrix idtest, id1, id2;
	id1.eye(3, 3);

	ifstream input("eyeTimes2.dat");
	readMatrixFromFile(input, id2);
	input.close();

	idtest = id2 - id1;

	EXPECT_EQ(id1, idtest);
}

TEST_F (sparseMatrixTests, writeToFile) {
	matrix id1, idTest;
	id1.eye(3, 3);

	ofstream output("test.dat");
	writeMatrixToFile(output, id1);
	output.close();

	ifstream input("test.dat");
	readMatrixFromFile(input, idTest);
	input.close();

	EXPECT_EQ(id1, idTest);
}

TEST_F (sparseMatrixTests, writeToFile2) {
	matrix A1test, b1test;

	ofstream output("test.dat");
	writeMatrixToFile(output, A1, b1);
	output.close();

	ifstream input("test.dat");
	readMatrixFromFile(input, A1test, b1test);
	input.close();

	EXPECT_EQ(A1, A1test);
	EXPECT_EQ(b1, b1test);
}

TEST_F (sparseMatrixTests, generateSamples) {

	double min = -4.9;
	double max = 4.9;
	string filenameRoot = "test1";

	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	//std::uniform_real_distribution<double> dist (min, max);
	std::uniform_int_distribution<> dist((int) min, (int) max);

	generateSamples(filenameRoot, randDevice, generator, dist);

	matrix A1test, x1test, b1test, b1calc;

	ifstream input1(filenameRoot + "_Ab.dat");
	readMatrixFromFile(input1, A1test, b1test);
	input1.close();

	ifstream input2(filenameRoot + "_x.dat");
	readMatrixFromFile(input2, x1test);
	input2.close();

	b1calc = A1test * x1test;

	EXPECT_EQ(b1test, b1calc);
}

}

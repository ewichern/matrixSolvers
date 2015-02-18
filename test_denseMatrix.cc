/*
 * test_denseMatrix.cc
 *
 *  Created on: Jan 21, 2015
 *      Author: erik
 */

#include "gtest/gtest.h"
#include <fstream>
#include <exception>

#include "denseMatrix.h"
#include "matrixGenerator.h"

typedef denseMatrix<double> matrix;

using namespace std;

class denseMatrixTests: public ::testing::Test
{
public:
	matrix A1, A1again, A2, x1, x2, b1, b1again, b2;

	denseMatrixTests()
	{

		ifstream a1b1input("sampleData1Ab.dat");
		ifstream x1input("sampleData1x.dat");

		MatrixGenerator::readMatrixFromFile(a1b1input, A1, b1);

		a1b1input.close();
		a1b1input.open("sampleData1Ab.dat");

		MatrixGenerator::readMatrixFromFile(a1b1input, A1again, b1again);
		MatrixGenerator::readMatrixFromFile(x1input, x1);

		ifstream a2b2input("sampleData2Ab.dat");
		ifstream x2input("sampleData2x.dat");

		MatrixGenerator::readMatrixFromFile(a2b2input, A2, b2);
		MatrixGenerator::readMatrixFromFile(x2input, x2);
	}

	virtual ~denseMatrixTests()
	{

	}

};

TEST_F (denseMatrixTests, constructors)
{
	matrix* ptr = new matrix();
	matrix* ptr2 = new matrix(6, 6);
	matrix* ptr3 = new matrix(3, 3, 0.1);
	delete ptr;
	delete ptr2;
	delete ptr3;
}

TEST_F (denseMatrixTests, equals)
{
	matrix test1(1, 1, 0.0);

	EXPECT_EQ(test1, test1);
	EXPECT_EQ(A1, A1again);
	EXPECT_EQ(b1, b1);
}

TEST_F (denseMatrixTests, not_equals)
{
	matrix test1(1, 1, 0.0);
	matrix test2(2, 1, 0.0);
	matrix test3(1, 1, 1.0);

	EXPECT_NE(test1, test2);
	EXPECT_NE(test1, test3);

	EXPECT_NE(A1, A2);
}

TEST_F (denseMatrixTests, copy)
{
	matrix test1(1, 1, -1);

	matrix test1copy(test1);
	matrix A1copy(A1);
	matrix b1copy(b1);

	EXPECT_EQ(test1, test1copy);
	EXPECT_EQ(A1, A1copy);
	EXPECT_EQ(b1, b1copy);
}

TEST_F (denseMatrixTests, assign)
{
	matrix test1(1, 1, -1);
	matrix test1copy, A1copy, b1copy;

	test1copy = test1;
	A1copy = A1;
	b1copy = b1;

	EXPECT_EQ(test1, test1copy);
	EXPECT_EQ(A1, A1copy);
	EXPECT_EQ(b1, b1copy);
}

TEST_F (denseMatrixTests, multiplyRight)
{
	matrix b1test, b2test;

	try
	{
		b1test = A1 * x1;
	} catch (exception& e)
	{
		e.what();
	}

	try
	{
		b2test = A2 * x2;
	} catch (exception& e)
	{
		e.what();
	}

	EXPECT_EQ(b1, b1test);
	EXPECT_EQ(b2, b2test);
}

TEST_F (denseMatrixTests, eye)
{
	matrix id1, id2;
	id1.eye(3, 3);

	ifstream input("eye.dat");
	MatrixGenerator::readMatrixFromFile(input, id2);
	input.close();

	EXPECT_EQ(id1, id2);
}

TEST_F (denseMatrixTests, multiplyScaler)
{
	matrix idtest, id1, id2;
	id1.eye(3, 3);
	idtest = 2 * id1;

	ifstream input("eyeTimes2.dat");
	MatrixGenerator::readMatrixFromFile(input, id2);
	input.close();

	EXPECT_EQ(idtest, id2);

	idtest = id2 * 0.5;

	EXPECT_EQ(idtest, id1);
}

TEST_F (denseMatrixTests, add)
{
	matrix idtest, id1, id2;
	id1.eye(3, 3);
	id2.eye(3, 3);
	idtest = id1 + id2;

	ifstream input("eyeTimes2.dat");
	MatrixGenerator::readMatrixFromFile(input, id2);
	input.close();

	EXPECT_EQ(idtest, id2);
}

TEST_F (denseMatrixTests, subtract)
{
	matrix idtest, id1, id2;
	id1.eye(3, 3);

	ifstream input("eyeTimes2.dat");
	MatrixGenerator::readMatrixFromFile(input, id2);
	input.close();

	idtest = id2 - id1;

	EXPECT_EQ(id1, idtest);
}
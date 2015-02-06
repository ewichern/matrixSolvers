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

#include "sparseMatrix.h"
#include "matrixGenerator.h"

typedef sparseMatrix<double> matrix;

using namespace std;

class matrixGeneratorTests: public ::testing::Test
{
public:
	matrix A1, b1;

	matrixGeneratorTests()
	{

		ifstream a1b1input("sampleData1ab.dat");

		MatrixGenerator::readMatrixFromFile(a1b1input, A1, b1);
		a1b1input.close();
	}

	virtual ~matrixGeneratorTests()
	{

	}

};

TEST_F (matrixGeneratorTests, writeToFile)
{
	matrix id1, idTest;
	id1.eye(3, 3);

	ofstream output("test.dat");
	MatrixGenerator::writeMatrixToFile(output, id1);
	output.close();

	ifstream input("test.dat");
	MatrixGenerator::readMatrixFromFile(input, idTest);
	input.close();

	EXPECT_EQ(id1, idTest);
}

TEST_F (matrixGeneratorTests, writeToFile2)
{
	matrix A1test, b1test;

	ofstream output("test.dat");
	MatrixGenerator::writeMatrixToFile(output, A1, b1);
	output.close();

	ifstream input("test.dat");
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
	string filenameRoot = "test1";

	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	distribType dist(min, max);
	//distribType dist((int) min, (int) max);

	MatrixGenerator::generateSamples<distribType > (filenameRoot, randDevice, generator, dist);

	matrix A1test, x1test, b1test, b1calc;

	ifstream input1(filenameRoot + "_Ab.dat");
	MatrixGenerator::readMatrixFromFile(input1, A1test, b1test);
	input1.close();

	ifstream input2(filenameRoot + "_x.dat");
	MatrixGenerator::readMatrixFromFile(input2, x1test);
	input2.close();

	b1calc = A1test * x1test;

	double errLimit = 0.00001;
	double err = relError(b1test, b1calc);
	cerr << "Calculated relative error: " << endl
			<< err << endl;

	EXPECT_LT(err, errLimit);


	//EXPECT_EQ(b1test, b1calc);
}


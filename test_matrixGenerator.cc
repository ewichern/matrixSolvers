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

	matrixGeneratorTests()
	{

		ifstream a1b1input(data1AB);

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

	ofstream output(unitTest);
	MatrixGenerator::writeMatrixToFile(output, id1);
	output.close();

	ifstream input(unitTest);
	MatrixGenerator::readMatrixFromFile(input, idTest);
	input.close();

	EXPECT_EQ(id1, idTest);
}

TEST_F (matrixGeneratorTests, writeToFile2)
{
	matrix A1test, b1test;

	ofstream output(unitTest);
	MatrixGenerator::writeMatrixToFile(output, A1, b1);
	output.close();

	ifstream input(unitTest);
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


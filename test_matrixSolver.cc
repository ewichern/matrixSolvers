/*
 * test_matrixSolver.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: erik
 */

#include "denseMatrix.h"
#include "matrixGenerator.h"
#include "IterativeSolvers.h"
#include <streambuf>
#include <ctime>

#include "gtest/gtest.h"

#include "matrixSolver.cpp"

using namespace std;

class matrixSolverTests: public ::testing::Test
{
public:

	const char* data1AB = "testData/sampleData1Ab.dat";
	const char* data1x = "testData/sampleData1x.dat";
	const char* data2AB = "testData/sampleData2Ab.dat";
	const char* data2x = "testData/sampleData2x.dat";
	const char* identity = "testData/eye.dat";
	const char* identityTimes2 = "testData/eyeTimes2.dat";
	const char* morrisData = "testData/SAMPLEdata.txt";
	const char* morrisXsol = "testData/SAMPLEsol.txt";
	const char* unitTest = "testData/unitTest.dat";
	const string filenameRoot = "testData/unitTest";
	const string testFilename = "googleTestGetFilename";


	matrixSolverTests()
	{

	}

	virtual ~matrixSolverTests()
	{

	}

};

TEST_F (matrixSolverTests, printMenuOptions)
{
	int menuOutput = 999;
	string input1 = "20 \n 4";
	string input2 = "-414 \n 3";
	string input3 = "asdf;aadsf -01234=5 \n 2";
	string input4 = "9999 \n 1";

	stringstream input(input1);
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(4, menuOutput);

//	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str(input2);
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(3, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str(input3);
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(2, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

	input.str(input4);
	menuOutput = printMenuOptions(input);
	EXPECT_EQ(1, menuOutput);
//	std::cerr << "menuOutput: " << menuOutput << endl;

}

TEST_F (matrixSolverTests, getFilename)
{
	string output = "";

	stringstream input(testFilename);
	output = getFilename(input);

	EXPECT_EQ(testFilename, output);
}

TEST_F (matrixSolverTests, getFilenameRoot)
{
	string output = "";

	stringstream input(testFilename);
	output = getFilenameRoot(input);

	EXPECT_EQ(testFilename, output);
}

TEST_F (matrixSolverTests, getABinputFilename)
{
	string output = "";

	stringstream input(testFilename);
	output = getABinputFilename(input);

	EXPECT_EQ(testFilename, output);
}

TEST_F (matrixSolverTests, inputABfromFile)
{
	string failureOutput = "fail";
	string successOutput = morrisData;

	string inputFileName = "";
	stringstream input1("notAvalidFilename");
	stringstream input2(successOutput);
	matrix A, b;

	EXPECT_EQ(A.numrows(), 0);
	EXPECT_EQ(A.numcols(), 0);
	EXPECT_EQ(b.numrows(), 0);
	EXPECT_EQ(b.numrows(), 0);

//	std::cerr << input1.str() << endl;
	inputFileName = inputABfromFile(input1, A, b);
	EXPECT_EQ(failureOutput, inputFileName);

//	std::cerr << input2.str() << endl;
	inputFileName = inputABfromFile(input2, A, b);
	EXPECT_EQ(successOutput, inputFileName);

	EXPECT_GT(A.numrows(), 0);
	EXPECT_GT(A.numcols(), 0);
	EXPECT_GT(b.numrows(), 0);
	EXPECT_GT(b.numrows(), 0);

}

TEST_F (matrixSolverTests, inputXfromFile)
{
	string failureOutput = "fail";
	string successOutput = morrisData;

	string inputFileName = "";
	stringstream input1("notAfilename");
	stringstream input2(successOutput);
	matrix x;

	EXPECT_EQ(x.numrows(), 0);
	EXPECT_EQ(x.numcols(), 0);

//	std::cerr << input1.str() << endl;
	inputFileName = inputXfromFile(input1, x);
	EXPECT_EQ(failureOutput, inputFileName);

//	std::cerr << input2.str() << endl;
	inputFileName = inputXfromFile(input2, x);
	EXPECT_EQ(successOutput, inputFileName);

	EXPECT_GT(x.numrows(), 0);
	EXPECT_GT(x.numcols(), 0);

}


TEST_F (matrixSolverTests, generateMatrixDataFiles)
{
	int m = 6, n = 6;
	string filenameInput = filenameRoot;

	string filenameOutput = "";
	stringstream input;

	input << m << " " << n << " \n " << filenameInput;

	matrix A, b;
	filenameOutput = generateMatrixDataFiles(input, A, b);

	ifstream fileTest(filenameOutput + "_Ab.dat");

	EXPECT_TRUE(fileTest.is_open());
	EXPECT_EQ(filenameInput, filenameOutput);

	tuple<int, int> aSize(A.numrows(), A.numcols());
	tuple<int, int> bSize(b.numrows(), b.numcols());
	tuple<int, int> aExpected(m, n);
	tuple<int, int> bExpected(n, 1);

	EXPECT_TRUE(aExpected == aSize);
	EXPECT_TRUE(bExpected == bSize);

}

TEST_F (matrixSolverTests, executeSolver)
{
	int m = 6, n = 6;
	string filenameInput = filenameRoot;

	string filenameOutput = "";
	stringstream input;

	matrix A, x, xTest, b;

	input << m << " " << n << " \n " << filenameInput;
	filenameOutput = generateMatrixDataFiles(input, A, b);
	ASSERT_EQ(filenameInput, filenameOutput);

	ifstream fileTestAb(filenameOutput + "_Ab.dat");
	ifstream fileTestX(filenameOutput + "_x.dat");

	ASSERT_TRUE(fileTestAb.is_open());
	ASSERT_TRUE(fileTestX.is_open());

	MatrixGenerator::readMatrixFromFile(fileTestX, x);

	tuple<int, int> aSize(A.numrows(), A.numcols());
	tuple<int, int> bSize(b.numrows(), b.numcols());
	tuple<int, int> aExpected(m, n);
	tuple<int, int> bExpected(n, 1);

	EXPECT_TRUE(aExpected == aSize);
	EXPECT_TRUE(bExpected == bSize);

	int numIterations = -1;

	numIterations = executeSolver(input, 1, A, xTest, b);

	EXPECT_NE(-1, numIterations);

	double errLimit = 0.00001;
	double err = relError(xTest, x);
	EXPECT_LT(err, errLimit);

}


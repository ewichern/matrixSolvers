#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <cmath>
#include <exception>
#include <string>

#include "denseMatrix.h"
#include "matrixGenerator.h"

using namespace std;

typedef denseMatrix<double> matrix;

void MatrixGenerator::askForMatrixSize(std::istream& input, int& m, int& n)
{
	std::cout << "Enter desired size (m x n) for matrix A \n"
			<< "-- in integers, separated by a space: \n";

	while (!(input >> m >> n))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// File format:
// integer sizes provided for rows*cols, each followed by \n
// then sufficient values to fill A and b,
// each separated by whitespace or newline
void MatrixGenerator::readMatrixFromFile(std::ifstream& input, matrix& A,
		matrix& b)
{

	int m = 0, n = 0;
	input >> m >> n;

	A = matrix(m, n);
	b = matrix(m, 1);

	double tempValue = 0.0;

	for (int i = 0; i < A.numrows(); ++i)
	{
		for (int j = 0; j < A.numcols(); ++j)
		{
			input >> tempValue;
			A[i][j] = tempValue;
		}
	}

	for (int i = 0; i < b.numrows(); ++i)
	{
		input >> tempValue;
		b[i][0] = tempValue;
	}

}

// Overloaded from above, only reads in one matrix
// File format:
// integer sizes provided for rows*cols, each followed by \n
// then sufficient values to fill A,
// each separated by whitespace or newline
void MatrixGenerator::readMatrixFromFile(std::ifstream& input, matrix& A)
{

	int m = 0, n = 0;
	input >> m >> n;

	A = matrix(m, n);

	double tempValue = 0.0;

	for (int i = 0; i < A.numrows(); ++i)
	{
		for (int j = 0; j < A.numcols(); ++j)
		{
			input >> tempValue;
			A[i][j] = tempValue;
		}
	}
}

void MatrixGenerator::writeMatrixToFile(std::ofstream& output, const matrix& A)
{

	output << A.numrows() << "\n";
	output << A.numcols() << "\n";

	for (int i = 0; i < A.numrows(); ++i)
	{
		for (int j = 0; j < A.numcols(); ++j)
		{
			output << fixed << setprecision(numDigits) << A[i][j] << " ";
		}
		output << "\n";
	}
}

// For writing A and b (of Ax = b) to a sample data file for later use in solver testing
// A.numcols() must == b.num
void MatrixGenerator::writeMatrixToFile(std::ofstream& output, const matrix& A,
		const matrix& b)
{

    std::cerr << A.numcols() << " " << b.numrows() << std::endl;
    std::cerr << b.numcols() << std::endl;

	if ((A.numcols() != b.numrows()) || (b.numcols() != 1))
	{
		throw std::logic_error("Matrix sizes wrong for file format");
	}
	else
	{

		output << A.numrows() << "\n";
		output << A.numcols() << "\n";

		for (int i = 0; i < A.numrows(); ++i)
		{
			for (int j = 0; j < A.numcols(); ++j)
			{
				output << fixed << setprecision(numDigits) << A[i][j] << " ";
			}
			output << "\n";
		}
		for (int i = 0; i < b.numrows(); ++i)
		{
			output << fixed << setprecision(numDigits * numDigits) << b[i][0]
					<< " ";
		}
	}
}

typedef std::uniform_real_distribution<double> distribReal;

template<typename distribType>
void MatrixGenerator::randomFillMatrix(matrix& mat, std::mt19937& generator,
		distribType& dist)
{

	for (int m = 0; m < mat.numrows(); ++m)
	{

		double rowTotal = 0;

		for (int n = 0; n < mat.numcols(); ++n)
		{
			double newValue = (double) dist(generator);
			newValue = round(newValue * 100) / 100.0;
			rowTotal += std::abs(newValue);
			mat[m][n] = newValue;
		}

		if (m < mat.numcols())
		{
			mat[m][m] = rowTotal;
		}
	}

}
template void MatrixGenerator::randomFillMatrix<distribReal>(matrix& mat,
		std::mt19937& generator, distribReal& dist);

template<typename distribType>
void MatrixGenerator::generateSamples(int rows, int cols, string filenameRoot,
		std::mt19937& generator, distribType& dist)
{

	matrix aRand(rows, cols, 0.0);
	matrix xRand(cols, 1, 0.0);

	randomFillMatrix(aRand, generator, dist);
	randomFillMatrix(xRand, generator, dist);

	matrix bRand(cols, 1, 0.0);
	bRand = aRand * xRand;

//	std::cerr << "bRand: " << endl << bRand;

	ofstream output1(filenameRoot + "_Ab.dat");
	writeMatrixToFile(output1, aRand, bRand);
	output1.close();

	ofstream output2(filenameRoot + "_x.dat");
	writeMatrixToFile(output2, xRand);
	output2.close();
}

template void MatrixGenerator::generateSamples<distribReal>(int rows, int cols,
		string filenameRoot, std::mt19937& generator, distribReal& dist);

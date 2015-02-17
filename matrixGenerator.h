#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include "denseMatrix.h"
#include <fstream>
#include <random>
#include <string>

using namespace std;

typedef denseMatrix<double> matrix;

class MatrixGenerator
{
private:
	static const int numDigits = 2;

public:

	static void askForMatrixSize(std::istream& input, int& m, int& n);

	// File format:
	// integer sizes provided for rows*cols, each followed by \n
	// then sufficient values to fill A and b,
	// each separated by whitespace or newline
	static void readMatrixFromFile(std::ifstream& input, matrix& A, matrix& b);

	// Overloaded from above, only reads in one matrix
	// File format:
	// integer sizes provided for rows*cols, each followed by \n
	// then sufficient values to fill A,
	// each separated by whitespace or newline
	static void readMatrixFromFile(std::ifstream& input, matrix& A);

	static void writeMatrixToFile(std::ofstream& output, const matrix& A);

	// For writing A and b (of Ax = b) to a sample data file for later use in solver testing
	// A.numcols() must == b.num
	static void writeMatrixToFile(std::ofstream& output, const matrix& A,
			const matrix& b);

	template<typename distribType>
	static void randomFillMatrix(matrix& mat, std::mt19937& generator,
			distribType& dist);

	template<typename distribType>
	static void generateSamples(int rows, int cols, string filenameRoot,
			std::mt19937& generator, distribType& dist);

};
#endif

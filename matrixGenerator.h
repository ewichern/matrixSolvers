#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include "sparseMatrix.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <cmath>
#include <exception>
#include <string>

using namespace std;

typedef sparseMatrix<double> matrix;

void askForMatrixSize(std::istream& input, int& m, int& n) {

	while (!(input >> m >> n)) {
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
void readMatrixFromFile(std::ifstream& input, matrix& A, matrix& b) {

	int m = 0, n = 0;
	input >> m >> n;

	A = matrix(m, n);
	b = matrix(m, 1);

	double tempValue = 0.0;

	for (int i = 0; i < A.numrows(); ++i) {
		for (int j = 0; j < A.numcols(); ++j) {
			input >> tempValue;
			A[i][j] = tempValue;
		}
	}

	for (int i = 0; i < b.numrows(); ++i) {
		input >> tempValue;
		b[i][0] = tempValue;
	}

}

// Overloaded from above, only reads in one matrix
// File format:
// integer sizes provided for rows*cols, each followed by \n
// then sufficient values to fill A,
// each separated by whitespace or newline
void readMatrixFromFile(std::ifstream& input, matrix& A) {

	int m = 0, n = 0;
	input >> m >> n;

	A = matrix(m, n);

	double tempValue = 0.0;

	for (int i = 0; i < A.numrows(); ++i) {
		for (int j = 0; j < A.numcols(); ++j) {
			input >> tempValue;
			A[i][j] = tempValue;
		}
	}
}

void writeMatrixToFile(std::ofstream& output, const matrix& A) {

	output << A.numrows() << "\n";
	output << A.numcols() << "\n";

	for (int i = 0; i < A.numrows(); ++i) {
		for (int j = 0; j < A.numcols(); ++j) {
			output << A[i][j] << " ";
		}
		output << "\n";
	}
}

// For writing A and b (of Ax = b) to a sample data file for later use in solver testing
// A.numcols() must == b.num
void writeMatrixToFile(std::ofstream& output, const matrix& A,
		const matrix& b) {

	if ((A.numcols() != b.numrows()) || (b.numcols() != 1)) {
		throw std::logic_error("Matrix size mismatch");
	} else {

		output << A.numrows() << "\n";
		output << A.numcols() << "\n";

		for (int i = 0; i < A.numrows(); ++i) {
			for (int j = 0; j < A.numcols(); ++j) {
				output << A[i][j] << " ";
			}
			output << "\n";
		}
		for (int i = 0; i < b.numrows(); ++i) {
			output << b[i][0] << " ";
		}
	}
}

template<class genType, class distribType>
void randomFillMatrix(matrix& mat, const std::random_device& randDevice,
		genType& generator, distribType& dist) {

	for (int m = 0; m < mat.numrows(); ++m) {

		double rowTotal = 0;

		for (int n = 0; n < mat.numcols(); ++n) {
			double newValue = (double)dist(generator);
			rowTotal += std::abs(newValue);
			mat[m][n] = newValue;
		}

		mat[m][m] = rowTotal;
	}

}

template<class genType, class distribType>
void generateSamples(string filenameRoot, const std::random_device& randDevice,
		genType& generator, distribType& dist) {

	int m = 3, n = 3;
	/*
	 std::cout << "Enter desired size (m x n) for matrix A \n"
	 << "-- in integers, separated by a space: \n";
	 askForMatrixSize(std::cin, m, n);
	 */

	matrix aRand(m, n, 0.0);
	matrix xRand(n, 1, 0.0);

	randomFillMatrix(aRand, randDevice, generator, dist);
	randomFillMatrix(xRand, randDevice, generator, dist);

	matrix bRand;
	bRand = aRand * xRand;

	ofstream output1(filenameRoot + "_Ab.dat");
	writeMatrixToFile(output1, aRand, bRand);
	output1.close();

	ofstream output2(filenameRoot + "_x.dat");
	writeMatrixToFile(output2, xRand);
	output2.close();
}

#endif /** MATRIXGENERATOR_H */


#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include "sparseMatrix.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <cmath>

using namespace std;

typedef sparseMatrix<double> matrix;

void askForMatrixSize(std::istream& input, int& m, int& n) {

	while (!(input >> m >> n)) {
		input.clear();
		input.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
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

	for (int i = 0; i < A.numrows(); ++i){
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

	for (int i = 0; i < A.numrows(); ++i){
		for (int j = 0; j < A.numcols(); ++j) {
			input >> tempValue;
			A[i][j] = tempValue;
		}
	}
}

template <class genType, class distribType>
void randomFillMatrix(matrix& mat,
		const std::random_device& randDevice,
		genType& generator,
		distribType& dist) {

	for (int m = 0; m < mat.numrows(); ++m) {

		double rowTotal = 0;

		for (int n = 0; n < mat.numcols(); ++n) {
			double newValue = dist(generator);
			rowTotal += std::abs(newValue);
			mat[m][n] = newValue;
		}

		mat[m][m] = rowTotal;
	}

}

void randomSolution(matrix& x) {

}

#endif

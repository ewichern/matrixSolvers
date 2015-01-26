#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include "sparseMatrix.h"
#include <utility>
#include <iostream>
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

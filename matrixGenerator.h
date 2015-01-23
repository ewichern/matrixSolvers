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

pair<int, int> askForMatrixSize(std::istream& input) {

	int m = 1, n = 1;

	while (!(input >> m >> n)) {
		input.clear();
		input.ignore( std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore( std::numeric_limits<std::streamsize>::max(), '\n');

	return std::make_pair(m, n);
}

void randomFillMatrix(matrix& A,
		const std::random_device& randDevice,
		std::mt19937& generator) {

	std::uniform_real_distribution<double> dist (-9.9, 9.9);

	for (int m = 0; m < A.numrows(); ++m) {

		double rowTotal = 0;

		for (int n = 0; n < A.numcols(); ++n) {
			double newValue = dist(generator);
			rowTotal += std::abs(newValue);
			A[m][n] = newValue;
		}

		A[m][m] = rowTotal;
	}

}


#endif

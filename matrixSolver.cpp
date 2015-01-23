/*
 * matrixSolver.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: erik
 */

#include "sparseMatrix.h"
#include "matrixGenerator.h"
#include <utility>
#include <iostream>
#include <random>

using namespace std;

typedef sparseMatrix<double> matrix;

int main (int argc, char **argv) {

	std::random_device randDevice;
	std::mt19937 generator(randDevice());

	std::cout << "Enter desired size (m x n) for matrix A \n"
				<< "-- in integers, separated by a space: \n";

	pair<int, int> mXn = askForMatrixSize(std::cin);

	matrix A (mXn.first, mXn.second, 0.0);
	randomFillMatrix(A, randDevice, generator);

	std::cout << A;

	return 0;
}

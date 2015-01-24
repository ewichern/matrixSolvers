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

	std::cout << "Enter desired size (m x n) for matrix A \n"
				<< "-- in integers, separated by a space: \n";

	pair<int, int> mXn = askForMatrixSize(std::cin);

	double min = -9.9;
	double max = 9.9;

	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	//std::uniform_real_distribution<double> dist (min, max);
	std::uniform_int_distribution<> dist ((int)min, (int)max);

	matrix A (mXn.first, mXn.second, 0.0);
	matrix x (mXn.second, 1, 0.0);

	randomFillMatrix (A, randDevice, generator, dist);
	std::cout << "A:" << "\n";
	std::cout << A << "\n\n";

	randomFillMatrix (x, randDevice, generator, dist);
	std::cout << "x:" << "\n";
	std::cout << x << "\n";

	return 0;
}

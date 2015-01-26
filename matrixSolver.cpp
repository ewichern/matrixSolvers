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

	int m = 0, n = 0;
	askForMatrixSize(std::cin, m, n);

	double min = -9.9;
	double max = 9.9;

	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	//std::uniform_real_distribution<double> dist (min, max);
	std::uniform_int_distribution<> dist ((int)min, (int)max);

	matrix A (m, n, 0.0);
	matrix x (n, 1, 0.0);

	randomFillMatrix (A, randDevice, generator, dist);
	randomFillMatrix (x, randDevice, generator, dist);

	matrix copyA (A);

	std::cerr << "A:" << "\n";
	std::cerr << A << "\n";

	std::cerr << "copyA:" << "\n";
	std::cerr << copyA << "\n";

	std::cerr << "copyA == A?" << "\n";
	std::cerr << (copyA == A) << "\n\n";

	std::cerr << "x:" << "\n";
	std::cerr << x << "\n";

	std::cerr << "x == A?" << "\n";
	std::cerr << (x == A) << "\n\n";

	matrix b = A*x;

	std::cerr << "b = A*x:" << "\n";
	std::cerr << b << "\n";

	return 0;
}

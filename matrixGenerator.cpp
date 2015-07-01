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

MatrixGenerator::MatrixGenerator() {
	std::random_device randDevice;
	generator = std::mt19937(randDevice());
	dist = distribType(min, max);
}

MatrixGenerator::MatrixGenerator(augMatrix& mat) {
	augMat = &mat;
	std::random_device randDevice;
	generator = std::mt19937(randDevice());
	dist = distribType(min, max);

//	std::random_device randDevice;
//	std::mt19937 generator(randDevice());
//	distribType dist(min, max);
}

MatrixGenerator::~MatrixGenerator() {
}

augMatrix& MatrixGenerator::getAugMatrix() const {
	return *augMat;
}

bool MatrixGenerator::exists() const {
	return true;
}

void MatrixGenerator::randomFillMatrix(matrix& mat) {

	for (int m = 0; m < mat.numrows(); ++m) {

		double rowTotal = 0;

		for (int n = 0; n < mat.numcols(); ++n) {
			double newValue = (double) dist(generator);

//			std::cerr << newValue << "\n";

			newValue = round(newValue * 100) / 100.0;
			rowTotal += std::abs(newValue);
			mat[m][n] = newValue;
		}

		if (m < mat.numcols()) {
			mat[m][m] = rowTotal;
		}
	}

}

void MatrixGenerator::generateSamples(int rows, int cols, string filename) {
	matrix& A = augMat->getA();
	matrix& X = augMat->getX();
	matrix& B = augMat->getB();

	randomFillMatrix(A);
	randomFillMatrix(X);

	B = A * X;

	std::ofstream abOutput(filename + "AB.dat");
	augMat->filePrintAugMatrix(abOutput);

	std::ofstream xOutput(filename + "X.dat");
	X.writeFile(xOutput);
}

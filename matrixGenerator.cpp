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

MatrixGenerator::MatrixGenerator()
{
	augMat = new augMatrix();
	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	distribType dist(min, max);
}

MatrixGenerator::MatrixGenerator(augMatrix& mat)
{
	augMat = mat;
	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	distribType dist(min, max);
}

MatrixGenerator::~MatrixGenerator()
{

}

void MatrixGenerator::randomFillMatrix(matrix& mat)
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
/*
void MatrixGenerator::generateSamples(int rows, int cols, string filename)
{
	this->filenameRoot = filename;

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
*/

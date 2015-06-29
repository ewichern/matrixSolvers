#ifndef MATRIXGENERATOR_H
#define MATRIXGENERATOR_H

#include "denseMatrix.h"
#include "augMatrix.h"
#include <fstream>
#include <random>
#include <string>

using namespace std;

typedef denseMatrix<double> matrix;
typedef std::uniform_real_distribution<double> distribType;

class MatrixGenerator
{
public:

	MatrixGenerator();
	MatrixGenerator(augMatrix&);
	virtual ~MatrixGenerator();

	void randomFillMatrix(matrix&);
	void generateSamples(int rows, int cols, string filenameRoot);

private:
	static const int numDigits = 2;

	augMatrix* augMat;
	std::random_device randDevice;
	std::mt19937 generator;
	distribType dist;

	string filenameRoot = "";

	double min = -100.0;
	double max = 100.0;

};
#endif

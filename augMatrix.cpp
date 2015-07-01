/*
 * augMatrix.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: erik
 */

#include <iostream>
#include <fstream>
#include <limits>
#include <random>
#include <cmath>
#include <exception>
#include <string>
#include "augMatrix.h"
#include "denseMatrix.h"

augMatrix::augMatrix() :
		numRows(0), numCols(0) {
}

augMatrix::augMatrix(matrix a, matrix b) :
		numRows(a.numrows()), numCols(a.numcols()) {
	A = a;
	B = b;
	X = matrix(numRows, 1, 0.1);
}

augMatrix::augMatrix(matrix a, matrix x, matrix b) :
		numRows(a.numrows()), numCols(a.numcols()) {
	A = a;
	B = b;
	X = x;
}

augMatrix::augMatrix(std::ifstream& input) :
		numRows(0), numCols(0) {
	this->setAugMatrix(input);
}

augMatrix::~augMatrix() {
}

const matrix& augMatrix::getA() const {
	return A;
}

matrix& augMatrix::getA() {
	return A;
}

void augMatrix::setA(const matrix& a) {
	A = a;
}

const matrix& augMatrix::getX() const {
	return X;
}

matrix& augMatrix::getX() {
	return X;
}

void augMatrix::setX(const matrix& x) {
	X = x;
}

const matrix& augMatrix::getB() const {
	return B;
}

matrix& augMatrix::getB() {
	return B;
}

void augMatrix::setB(const matrix& b) {
	B = b;
}

int augMatrix::numcols() const {
	return numCols;
}

void augMatrix::setNumCols(int numCols) {
	this->numCols = numCols;
}

int augMatrix::numrows() const {
	return numRows;
}

void augMatrix::setNumRows(int numRows) {
	this->numRows = numRows;
}

/*
 void augMatrix::setAugMatrix(std::ifstream& input)
 {
 int m = 0, n = 0;
 input >> m >> n;

 A = matrix(m, n);
 B = matrix(m, 1);

 double tempValue = 0.0;

 for (int i = 0; i < numRows; ++i)
 {
 for (int j = 0; j < numCols; ++j)
 {
 input >> tempValue;
 A[i][j] = tempValue;
 }
 }

 for (int i = 0; i < numRows; ++i)
 {
 input >> tempValue;
 B[i][0] = tempValue;
 }
 }
 */

void augMatrix::setA(std::ifstream& input) {
	input >> numRows >> numCols;
	setAhelper(input);
}

void augMatrix::setAhelper(std::ifstream& input) {
	A = matrix(numRows, numCols);
	double tempInputValue = 0.0;

	for (int i = 0; i < numRows; ++i) {
		for (int j = 0; j < numCols; ++j) {
			input >> tempInputValue;
			A[i][j] = tempInputValue;
		}

	}
}

void augMatrix::setX(std::ifstream& input) {
	int rows = 0, cols = 1;
	input >> rows >> cols;
	if (rows == numRows) {
		setXhelper(input);
	} else {
		throw std::logic_error("Matrix size mismatch");
	}
}

void augMatrix::setXhelper(std::ifstream& input) {
	X = matrix(numRows, 1);
	double tempInputValue = 0.0;
	for (int i = 0; i < numRows; ++i) {
		input >> tempInputValue;
		X[i][0] = tempInputValue;
	}
}

void augMatrix::setB(std::ifstream& input) {
	int rows = 0, cols = 1;
	input >> rows >> cols;
	if (rows == numRows) {
		setBhelper(input);
	} else {
		throw std::logic_error("Matrix size mismatch");
	}
}

void augMatrix::setBhelper(std::ifstream& input) {
	B = matrix(numRows, 1);
	double tempInputValue = 0.0;
	for (int i = 0; i < numRows; ++i) {
		input >> tempInputValue;
		B[i][0] = tempInputValue;
	}
}

/*
 * Reset stored augmented matrix data based on stream input
 *
 * @param input		requires stream input with data properly formatted and
 * 					sufficient to fill both A and B matrices
 * @return void
 */
void augMatrix::setAugMatrix(std::ifstream& input) {
	input >> numRows >> numCols;

	this->setAhelper(input);
	X = matrix(numRows, 1, 0.1);
	this->setBhelper(input);
}

augMatrix& augMatrix::operator=(const augMatrix& right) {
	if (!(*this == right)) {
		numRows = right.numRows;
		numCols = right.numCols;
		A = right.A;
		B = right.B;
		X = right.X;
	}
	return *this;
}

void augMatrix::filePrintAugMatrix(std::ofstream& output) const {

	output << numRows << "\n";
	output << numCols << "\n";

	output << A;

	for (int i = 0; i < numRows; ++i) {
		output << fixed << setprecision(numDigits * numDigits) << setw(21);
		output << B[i][0] << " ";
	}
}

void augMatrix::askForMatrixSize(std::istream& input) {
	int m = 0;
	int n = 0;

	std::cout << "Enter desired size (m x n) for matrix A \n"
			<< "-- in integers, separated by a space: \n";

	while (!(input >> m >> n)) {
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	numRows = m;
	numCols = n;
}

bool augMatrix::operator ==(const augMatrix& right) const {
	if ((this->A == right.getA()) && (this->X == right.getX())
			&& (this->B == right.getB()))
		return true;
	else
		return false;
}

bool augMatrix::operator !=(const augMatrix& right) const {
	return (!(*this == right));
}


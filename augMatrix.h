/*
 * augMatrix.h
 *
 *  Created on: Jun 21, 2015
 *      Author: erik
 */

#ifndef AUGMATRIX_H_
#define AUGMATRIX_H_

#include "denseMatrix.h"
#include <fstream>
#include <random>
#include <string>

using namespace std;

typedef denseMatrix<double> matrix;

/*
 *
 */
class augMatrix
{
public:
	augMatrix();
	augMatrix(matrix, matrix);
	augMatrix(matrix, matrix, matrix);
	augMatrix(std::ifstream&);

	virtual ~augMatrix();

	/*
	 * File format:
	 * integer sizes provided for rows*cols, each followed by \n
	 * then sufficient values to fill A and b,
	 * each separated by whitespace or newline
	 */
	void setAugMatrix(std::ifstream& input);
	augMatrix& operator=(const augMatrix&);
	void filePrintAugMatrix(std::ofstream& output) const;

	/*
	 * File format:
	 * integer sizes provided for rows*cols, each followed by \n
	 * then sufficient values to fill A OR B,
	 * each value separated by whitespace or newline
	 */
	const matrix& getA() const;
	void setA(const matrix& a);
	void setA(std::ifstream& input);

	const matrix& getX() const;
	void setX(const matrix& x);
	void setX(std::ifstream& input);

	const matrix& getB() const;
	void setB(const matrix& b);
	void setB(std::ifstream& input);

	int numcols() const;
	void setNumCols(int numCols);
	int numrows() const;
	void setNumRows(int numRows);

	void askForMatrixSize(std::istream& input);

	bool operator==(const augMatrix&) const;
	bool operator!=(const augMatrix&) const;

private:
	int numRows;
	int numCols;

	matrix A;
	matrix B;
	matrix X;

	static const int numDigits = 2;

	void setAhelper(std::ifstream& input);
	void setXhelper(std::ifstream& input);
	void setBhelper(std::ifstream& input);
};

#endif /* AUGMATRIX_H_ */

/*
 * augMatrix.h
 *
 *  Created on: Jun 21, 2015
 *      Author: Erik Wichern
 *       Email: ewichern@gmail.com
 */

#ifndef AUGMATRIX_H_
#define AUGMATRIX_H_

#include "denseMatrix.h"
#include <fstream>
#include <string>

using namespace std;

typedef denseMatrix<double> matrix;

/*
 * Augmented matrix class
 *
 * Stores # rows, cols, and A, x, and b matrices.
 * Intended use is as a container to easily pass "augmented" matrix to solvers
 */
class augMatrix {
public:

	/*
	 * Default constructor
	 *
	 * No parameters, initializes both rows/cols to zero. Does not
	 * initialize matrices.
	 *
	 * @return		a new augMatrix object
	 */
	augMatrix();

	/*
	 * AB Constructor
	 *
	 * Initializes rows/cols to a.numrows() and a.numcols()
	 * Assigns a and b to A and B.
	 * Initializes X the appropriate size (numRows x 1) and fills with "0.1"
	 *
	 * @param	a	an "A" matrix where A*x = B
	 * @param	b	a "B" matrix where A*x = B
	 * @return		an augMatrix object
	 */
	augMatrix(matrix, matrix);

	/*
	 * AXB Constructor
	 *
	 * Initializes rows/cols to a.numrows() and a.numcols()
	 * Assigns a, x, and b to A, X, and B.
	 * Note that A*X may not actually == B. User may want to provide an
	 * alternate starting matrix for X, or may be providing A and X and plan to
	 * multiply them to calculate B, etc.
	 *
	 * @param	a	an "A" matrix where A*X = B
	 * @param	x	an "X" matrix where A*X = B
	 * @param	b	a "B" matrix where A*X = B
	 * @return		an augMatrix object
	 */
	augMatrix(matrix, matrix, matrix);

	/*
	 * AB Constructor (stream input)
	 *
	 * File format:
	 * integer sizes provided for rows*cols, each followed by \n
	 * then sufficient values to fill A and b,
	 * each separated by whitespace or newline
	 *
	 * uses
	 * void setAugMatrix(std::ifstream&)
	 * to handle the input of stream data and saving to private data members
	 *
	 * @param	input	an ifstream object with matrix data
	 * @return		an augMatrix object
	 * @see		void setAugMatrix(std::ifstream&)
	 */
	augMatrix(std::ifstream&);

	/*
	 * Destructor
	 *
	 * Doesn't do anything special. No pointers, matrices handled by their own
	 * destructors.
	 */
	virtual ~augMatrix();

	/*
	 * Reset stored augmented matrix data based on stream input
	 *
	 * File format:
	 * integer sizes provided for rows*cols, each followed by \n
	 * then sufficient values to fill A and b,
	 * each separated by whitespace or newline
	 *
	 * @param input		requires stream input with data properly formatted and
	 * 					sufficient to fill both A and B matrices
	 * @return void
	 */
	void setAugMatrix(std::ifstream& input);

	/*
	 * Assignment operator
	 *
	 * Copies rhs onto lhs argument when invoked as "lhs = rhs;"
	 * Or copies right onto left when invoked as left.operator=(right);
	 *
	 * @param	right	the augMatrix *to be copied*
	 * @return		reference to the modified augMatrix object
	 */
	augMatrix& operator=(const augMatrix&);

	/*
	 * Prints A and B in proper format for file output
	 *
	 * Sends numRows and numCols, each followed by newline
	 * Then shovels A to the output stream.
	 * Then puts B in the output stream, but doubles the precision specified
	 * by static variable numDigits (to prevent some rounding errors when
	 * working with randomly generated matrices for testing)
	 *
	 * @param	output	output stream object
	 * @return	void
	 */
	void filePrintAugMatrix(std::ofstream& output) const;

	/*
	 * File format:
	 * integer sizes provided for rows*cols, each followed by \n
	 * then sufficient values to fill A OR B,
	 * each value separated by whitespace or newline
	 */

	/*
	 * getter for matrix A
	 *
	 * @return		const matrix reference to matrix A
	 */
	const matrix& getA() const;

	/*
	 * getter for matrix A
	 *
	 * @return		matrix reference to matrix A
	 */
	matrix& getA();

	/*
	 * setter for matrix A
	 * @param	a	const matrix reference to the matrix that will be copied
	 * 				onto A
	 * @return		void
	 */
	void setA(const matrix& a);

	/*
	 * setter for matrix A
	 *
	 * Overwrites matrix A with information from stream input.
	 * Format is again numrows, numcols, then values, each separated by
	 * whitespace or newlines
	 *
	 * @param	input	stream input properly formatted with matrix information
	 * 					for matrix A
	 * @return		void
	 */
	void setA(std::ifstream& input);

	/*
	 * getter for matrix X
	 *
	 * @return		const matrix reference to matrix X
	 */
	const matrix& getX() const;

	/*
	 * getter for matrix X
	 *
	 * @return		matrix reference to matrix X
	 */
	matrix& getX();

	/*
	 * setter for matrix X
	 * @param	x	const matrix reference to the matrix that will be copied
	 * 				onto X
	 * @return		void
	 */
	void setX(const matrix& x);

	/*
	 * setter for matrix X
	 *
	 * Overwrites matrix X with information from stream input.
	 * Format is again numrows, numcols, then values, each separated by
	 * whitespace or newlines
	 *
	 * @param	input	stream input properly formatted with matrix information
	 * 					for matrix X
	 * @return		void
	 */
	void setX(std::ifstream& input);

	/*
	 * getter for matrix B
	 *
	 * @return		const matrix reference to matrix B
	 */
	const matrix& getB() const;

	/*
	 * getter for matrix B
	 *
	 * @return		matrix reference to matrix B
	 */
	matrix& getB();

	/*
	 * setter for matrix B
	 * @param	b	const matrix reference to the matrix that will be copied
	 * 				onto B
	 * @return		void
	 */
	void setB(const matrix& b);

	/*
	 * setter for matrix B
	 *
	 * Overwrites matrix B with information from stream input.
	 * Format is again numrows, numcols, then values, each separated by
	 * whitespace or newlines
	 *
	 * @param	input	stream input properly formatted with matrix information
	 * 					for matrix B
	 * @return		void
	 */
	void setB(std::ifstream& input);

	/*
	 * getter for private data member numCols
	 *
	 * @return		number of columns in matrix A
	 */
	int numcols() const;

	/*
	 * setter for private data member numCols
	 *
	 * WARNING: COULD LEAD TO PROBLEMS (unreachable values in matrix)
	 * TODO:	add logic to resize matrices if size is reduced
	 *
	 * @param	numCols		new number of columns for matrix A
	 */
	void setNumCols(int numCols);

	/*
	 * getter for private data member numRows
	 *
	 * @return		number of rows (same for all three matrices)
	 */
	int numrows() const;

	/*
	 * setter for private data member numRows
	 *
	 * WARNING: COULD LEAD TO PROBLEMS (unreachable values in matrix)
	 * TODO:	add logic to resize matrices if size is reduced
	 *
	 * @param	numRows		new number of rows (should be the same for all
	 * 							three matrices)
	 */
	void setNumRows(int numRows);

	/*
	 * Prompt the user for numRows and numCols
	 *
	 * Primarily used when generating random matrices for testing.
	 * Sets numRows and numCols to values plucked from istream input
	 *
	 * @param	input	input stream that will accept user input -- though
	 * 					this could also be provided from a file or any other
	 * 					istream source
	 * @return		void
	 */
	void askForMatrixSize(std::istream& input);

	/*
	 * Equality operator
	 *
	 * Use is "lhs == rhs" or "left.operator==(right)"
	 * Evaluates to true if all three of the matrices in left ==
	 * the corresponding matrices in right.
	 *
	 * Else returns false.
	 *
	 * @param	right	const reference to augMatrix object to be compared
	 * 					against
	 * @return		true or false (see above description)
	 */
	bool operator==(const augMatrix&) const;

	/*
	 * NE operator
	 *
	 * Use is "lhs != rhs" or "left.operator!=(right)"
	 * Evaluates !(lhs == rhs) -- see above description for operator==
	 *
	 * @param	right	const reference to augMatrix object to be compared
	 * 					against
	 * @return		true or false (see above description)
	 * @see		bool operator==(const augMatrix&) const
	 */
	bool operator!=(const augMatrix&) const;

private:
	int numRows;
	int numCols;

	matrix A;
	matrix B;
	matrix X;

	// variable to set precision length - mostly for output of randomly generated matrices for testing
	static const int numDigits = 2;

	void setAhelper(std::ifstream& input);
	void setXhelper(std::ifstream& input);
	void setBhelper(std::ifstream& input);
};

#endif /* AUGMATRIX_H_ */

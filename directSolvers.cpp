/*
 * directSolvers.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#include "directSolvers.h"
#include <exception>

/**
 * Finds the pivot row number in a given matrix.
 *
 * Assumes that previous columns are all 1s or 0s and that previous rows
 * have been processed
 *
 * @param column 	column in which we are going to find the pivot row. all previous columns have been processed.
 * @param A		const reference to a diagonally dominant matrix.
 * @return 		the row with the largest value to be used as the pivot column.
 */
int directSolvers::findPivot(const matrix& A, int column)
{

	// set pivotRow to column and start searching at pivotRow+1;
	int pivotRow = column;
	double largest = A[column][column];
	for (int i = column + 1; i < A.numrows(); ++i)
	{
		if (A[i][column] > largest)
			pivotRow = i;
	}

	return pivotRow;
}

/**
 * Gaussian Elimination direct solver.
 *
 * Performs Gaussian eliminiation algorithm given square matrix A and matrix b (size: A.numrows() x 1)
 * @param A		const reference - square diagonally dominant matrix
 * @param x		reference parameter where we will store our solution
 * @param b		const reference - RHS, size A.numrows() x 1
 * @return	void
 */
void directSolvers::gaussianElimination(const matrix& A, matrix& x_k,
		const matrix& b)
{
	matrix augmented = A;
	augmented.augment(b);

	for (int i = 0; i < augmented.numrows(); ++i)
	{
		int pivot = findPivot(augmented, i);
		if (pivot != i)
		{
			augmented.swapRows(pivot, i);

		}
	}

// TODO
}

/*
 int IterativeSolvers::jacobi(const matrix& A, matrix& x_k, const matrix& b)
 {
 if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows()))
 {
 cerr << "A nRows: " << A.numrows() << endl;
 cerr << "A nCols: " << A.numcols() << endl;
 cerr << "b nRows: " << b.numrows() << endl;
 cerr << "b nCols: " << b.numcols() << endl;
 throw std::logic_error("Matrix size mismatch");
 }

 int iterationCount = 0;
 double errLimit = 0.00001;
 double err = 1.0;

 matrix x_kPlus1(x_k);

 while (err > errLimit)
 {
 for (int i = 0; i < A.numrows(); ++i)
 {
 //			std::cerr << " " << i;
 double rowSum = 0.0;
 for (int j = 0; j < A.numcols(); ++j)
 {
 if (j != i)
 {
 rowSum += (A[i][j] * x_k[j][0]);
 }
 }
 x_kPlus1[i][0] = ((b[i][0] - rowSum) / A[i][i]);
 }
 ++iterationCount;
 x_k = x_kPlus1;

 //		std::cerr << "iterationCount: " << iterationCount << std::endl;
 //		std::cerr << "x_k: " << endl << x_k << std::endl;
 matrix bTest = A * x_k;
 err = relError(bTest, b);

 }

 //std::cerr << "Relative error of Jacobi solution: " << err << endl;
 return iterationCount;

 }

 int IterativeSolvers::gaussSeidel(const matrix& A, matrix& x_k, const matrix& b)
 {
 if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows()))
 {
 cerr << "A nRows: " << A.numrows() << endl;
 cerr << "A nCols: " << A.numcols() << endl;
 cerr << "b nRows: " << b.numrows() << endl;
 cerr << "b nCols: " << b.numcols() << endl;
 throw std::logic_error("Matrix size mismatch");
 }

 int iterationCount = 0;
 double errLimit = 0.00001;
 double err = 1.0;

 while (err > errLimit)
 {
 for (int i = 0; i < A.numrows(); ++i)
 {
 //			std::cerr << " " << i;
 double rowSum = b[i][0];
 for (int j = 0; j < A.numcols(); ++j)
 {
 if (j != i)
 {
 rowSum -= (A[i][j] * x_k[j][0]);
 }
 }
 x_k[i][0] = (rowSum / A[i][i]);
 }
 ++iterationCount;

 //std::cerr << "iterationCount: " << iterationCount << std::endl;
 //std::cerr << "x_k: " << endl << x_k << std::endl;
 matrix bTest = A * x_k;
 err = relError(bTest, b);

 }

 //std::cerr << "Relative error of Jacobi solution: " << err << endl;
 return iterationCount;

 }

 int IterativeSolvers::successiveOverRelaxing(const double omega, const matrix& A, matrix& x_k, const matrix& b)
 {
 if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows()))
 {
 cerr << "A nRows: " << A.numrows() << endl;
 cerr << "A nCols: " << A.numcols() << endl;
 cerr << "b nRows: " << b.numrows() << endl;
 cerr << "b nCols: " << b.numcols() << endl;
 throw std::logic_error("Matrix size mismatch");
 }

 int iterationCount = 0;
 double errLimit = 0.00001;
 double err = 1.0;

 while (err > errLimit)
 {
 for (int i = 0; i < A.numrows(); ++i)
 {
 //			std::cerr << " " << i;
 double rowSum = b[i][0];
 double x_old = x_k[i][0];

 for (int j = 0; j < A.numcols(); ++j)
 {
 if (j != i)
 {
 rowSum -= (A[i][j] * x_k[j][0]);
 }
 }

 //			rowSum = (rowSum / A[i][i]);
 //			double new_xValue = x_old + (omega * (rowSum - x_old));

 double new_xValue = x_old + (omega * ((rowSum / A[i][i]) - x_old));

 //			double new_xValue = ((1.0 - omega) * x_old) + (omega  * (rowSum / A[i][i]));

 x_k[i][0] = new_xValue;
 }
 ++iterationCount;

 //		std::cerr << "iterationCount: " << iterationCount << std::endl;
 //		std::cerr << "x_k: " << endl << x_k << std::endl;
 matrix bTest = A * x_k;
 err = relError(bTest, b);
 //		std::cerr << "Relative error of SOR solution: " << err << endl;
 }

 return iterationCount;

 }
 */

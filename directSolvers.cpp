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
 * @return int 		the row with the largest value to be used as the pivot column.
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

/*
 * Backsolve for matrix in Upper Echelon form
 * @param A		reference to *augmented* matrix A, has already been converted to REF or RREF
 * @param x		reference to vector solution variables
 * @return void
 */
void directSolvers::backsolve(matrix& A, matrix& x)
{
	int bCol = A.numcols() - 1;
	int n = A.numrows() - 1;

//	std::cerr << "Walking through the backsolve -- " << std::endl;
	/*
	 * Solve for x_n
	 */
	x[n][0] = (A[n][bCol] / A[n][n]);
//	std::cerr << "x[" << n << "]: " << x[n][0] << std::endl;

	/*
	 * Backsolve from n-1 to 0
	 */
	for (int i = n - 1; i >= 0; --i)
	{
		double sum = 0.0;
		for (int j = i + 1; j <= n; ++j)
		{
			sum += (A[i][j] * x[j][0]);
		}
		/*
		 * A_ii*x_i = b_i - sum
		 * therefore we must divide RHS by A_ii.
		 * Note: unnecessary for GE if elimination process
		 * properly normalizes to leading 1s in each row.
		 */
		x[i][0] = ((A[i][bCol] - sum) / A[i][i]);
//		std::cerr << "x[" << i << "]: " << x[i][0] << std::endl;
	}
}

/*
 * Backsolve for matrix in Upper Echelon form
 * This is primarily for my LU implementation. It operates differently
 * due to assumptions we must make when we change the A matrix to
 * use it for storage of both L and U.
 *
 * @param U		reference to Upper triangular matrix U where where A = LDU
 * @param x		reference to the original x vector which will be solved in this sweep
 * @param y		const reference to intermediate vector y, where if LUx=b, then Ux=y and Ly=b
 * @return void
 */
void directSolvers::LUbacksolve(matrix& U, matrix& x, const matrix& y)
{
	int n = U.numrows() - 1;

//	std::cerr << "Walking through the backsolve -- " << std::endl;
	/*
	 * Solve for x_n
	 */
	x[n][0] = y[n][0];
//	std::cerr << "x[" << n << "]: " << x[n][0] << std::endl;

	/*
	 * Backsolve from n-1 to 0
	 */
	for (int i = n - 1; i >= 0; --i)
	{
		double sum = 0.0;
		for (int j = i + 1; j <= n; ++j)
		{
			sum += (U[i][j] * x[j][0]);
		}
		/*
		 * Must not divide by U_ii in LU backsolve, since diagonal is
		 * storing values for L matrix. For U backsolve, assume diagonal
		 * is filled with 1s, therefore no division necessary.
		 */
		x[i][0] = ((y[i][0] - sum));
//		std::cerr << "x[" << i << "]: " << x[i][0] << std::endl;
	}
}

/*
 * Forward sweep for LU solver
 *
 * @param L		reference to Lower triangular matrix + Diagonal for LU solver, where A = LDU
 * @param y		reference to y (y is an intermedia vector where if LUx = b -> Ux = y and Ly = b)
 * @param b		const reference to the vector b
 * @return void
 */
void directSolvers::forwardSolve(matrix& L, matrix& y, const matrix& b)
{
	int n = L.numrows() - 1;

//	std::cerr << "Walking through the forward sweep -- " << std::endl;
	/*
	 * Solve for y_n
	 */
	y[0][0] = (b[0][0] / L[0][0]);
//	std::cerr << "y[" << n << "]: " << y[n][0] << std::endl;

	/*
	 * Sweep from row 1 to row n;
	 */
	for (int i = 1; i <= n; ++i)
	{
		double sum = 0.0;
		for (int j = 0; j < i; ++j)
		{
			sum += (L[i][j] * y[j][0]);
		}
		/*
		 * L_ii*y_i = b_i - sum
		 * therefore we must divide RHS by L_ii.
		 */
		y[i][0] = ((b[i][0] - sum) / L[i][i]);
//		std::cerr << "y[" << i << "]: " << y[i][0] << std::endl;
	}
}

/**
 * Gaussian Elimination direct solver.
 *
 * Performs Gaussian eliminiation algorithm
 * given square matrix A and matrix b (size: A.numrows() x 1)
 * WARNING: overwrites matrix A.
 *
 * @param A		reference - square diagonally dominant matrix
 * @param x		reference parameter where we will store our solution
 * @param b		const reference - RHS, size A.numrows() x 1
 * @return	void
 */
void directSolvers::gaussianElimination(matrix& A, matrix& x, const matrix& b)
{
	if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows()))
	{
		cerr << "A nRows: " << A.numrows() << endl;
		cerr << "A nCols: " << A.numcols() << endl;
		cerr << "b nRows: " << b.numrows() << endl;
		cerr << "b nCols: " << b.numcols() << endl;
		throw std::logic_error("Gauss - Matrix size mismatch");
	}

//	matrix augmented = A;
	A.augment(b);

	/*
	 * Doing the elimination here.
	 * Backsolve is in its own method so that I can reuse it.
	 */
	for (int i = 0; i < A.numrows(); ++i)
	{
		// find the row with the largest element in column i
		int pivot = findPivot(A, i);

		// row i becomes the pivot row (after swap)
		if (pivot != i)
		{
			A.swapRows(pivot, i);
			// pivot location is now A[i][i]
		}

		/*
		 * we want 1 in our pivot location, so if loc_value != 1
		 * loc_value *= (1 / loc_value)
		 * obviously we have to apply this transformation to the whole row
		 */
		if (A[i][i] != 1.0)
		{
			double inverseA_ii = (1.0 / A[i][i]);
			A.multiplyRow(i, inverseA_ii);
		}

		/*
		 * for row j, where i+1 < j < size(),
		 * multiply the element in location A[j][i] by the pivot row.
		 * then subtract that result from row j.
		 */
		for (int j = i + 1; j < A.numrows(); ++j)
		{
			std::vector<double> savedPivotRow = A[i];

			// change sign so that I can add rows instead of subtract.
			double scaler = (-1.0 * (A[j][i] / A[i][i]));
			A.multiplyRow(i, scaler);
			A.addRows(i, j, j); // pivot, row j, destination (row j);

			// restore pivot row to previous state;
			A.swapRows(savedPivotRow, i);
		}
	}
//	std::cerr << "A after forward solve: " << std::endl << A
//			<< std::endl << std::endl;

	backsolve(A, x);
}

/*
 * Performs Crout decomposition on a square matrix.
 * Used in LU solver. Overwrites A with LU - U assumes 1s on the diagonal.
 *
 * @param A 	reference to square matrix A to be decomposed into Upper and Lower matrices *** A is overwritten
 * @return void
 */
void directSolvers::decomp(matrix& A)
{
	int n = A.numrows() - 1;

	double temp = A[0][0]; // saving because I'm going to temporarily overwrite it.

	/*
	 * First column of A is already in A.
	 * First row of A -> u_1j = A_1j / A_11
	 */
	A.multiplyRow(0, (1 / temp));

	A[0][0] = temp; // returning to correct value after overwriting with first row of A.

	for (int j = 1; j < n; ++j)
	{
		for (int i = j; i <= n; ++i)
		{
			double sumLUterms = 0.0;
			for (int k = 0; k < j; ++k)
			{
				sumLUterms += (A[i][k] * A[k][j]);
			}
			A[i][j] = (A[i][j] - sumLUterms);
		}

		for (int k = (j + 1); k <= n; ++k)
		{
			double sumLUterms = 0.0;
			for (int i = 0; i < j; ++i)
			{
				sumLUterms += (A[j][i] * A[i][k]);
			}
			A[j][k] = ((A[j][k] - sumLUterms) / A[j][j]);
		}
	}

	double sumLUterms = 0.0;
	for (int k = 0; k < n; ++k)
	{
		sumLUterms += A[n][k] * A[k][n];
	}
	A[n][n] = (A[n][n] - sumLUterms);
}

/**
 * LU decomposition direct solver.
 *
 * Performs LU decomposition algorithm given
 * square matrix A and matrix b (size: A.numrows() x 2)
 * Ax = b
 * LU = A (factor into LU)
 * LUx = b
 * Ux = y (substitute y for Ux in equation)
 * Ly = b (now solve for y, using forward substitution)
 * Now that y is known, solve for x in Ux = y using a backsolve.
 *
 * WARNING: overwrites matrix A.
 *
 * @param A		reference - square diagonally dominant matrix
 * @param x		reference parameter where we will store our solution
 * @param b		const reference - RHS, size A.numrows() x 1
 * @return	void
 */
void directSolvers::LUdecomposition(matrix& A, matrix& x, const matrix& b)
{
	if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows()))
	{
		cerr << "A nRows: " << A.numrows() << endl;
		cerr << "A nCols: " << A.numcols() << endl;
		cerr << "b nRows: " << b.numrows() << endl;
		cerr << "b nCols: " << b.numcols() << endl;
		throw std::logic_error("Matrix size mismatch");
	}

	/*
	 * Ax = b
	 * LU = A (factor into LU)
	 * LUx = b
	 */
	decomp(A); // replaces A with LU - U assumes 1s on the diagonal

//	std::cerr << "A after decomposition: " << std::endl << A << std::endl
//			<< std::endl;
	/*
	 * Ux = y (substitute y for Ux in equation)
	 * Ly = b (now solve for y, using forward substitution)
	 */
	matrix y(x.numrows(), 1);
	forwardSolve(A, y, b); // A -> L

//	std::cerr << "y after forward sweep: " << std::endl << y << std::endl
//			<< std::endl;

	/*
	 * Now that y is known, solve for x in Ux = y using a backsolve.
	 */
	LUbacksolve(A, x, y); // A -> U
//	std::cerr << "x after backsolve: " << std::endl << x << std::endl
//			<< std::endl;
}

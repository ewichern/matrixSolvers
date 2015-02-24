/*
 * IterativeSolvers.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#include "IterativeSolvers.h"
#include <exception>

/*
 IterativeSolvers::IterativeSolvers()
 {
 // TODO Auto-generated constructor stub

 }

 IterativeSolvers::~IterativeSolvers()
 {
 // TODO Auto-generated destructor stub
 }
 */

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
	double errLimit = 0.000001;
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
	double errLimit = 0.000001;
	double err = 1.0;

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
			x_k[i][0] = ((b[i][0] - rowSum) / A[i][i]);
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

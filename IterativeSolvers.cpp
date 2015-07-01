/*
 * IterativeSolvers.cpp
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#include "IterativeSolvers.h"
#include <exception>

int IterativeSolvers::jacobi(const matrix& A, matrix& x_old, const matrix& b) {
	if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows())) {
		cerr << "A nRows: " << A.numrows() << endl;
		cerr << "A nCols: " << A.numcols() << endl;
		cerr << "b nRows: " << b.numrows() << endl;
		cerr << "b nCols: " << b.numcols() << endl;
		throw std::logic_error("Matrix size mismatch");
	}

	int iterationCount = 0;
	double errLimit = 0.00001;
	double err = 1.0;

	matrix x_new(x_old);

	while (err > errLimit) {
		for (int i = 0; i < A.numrows(); ++i) {
//			std::cerr << " " << i;
			double rowSum = 0.0;
			for (int j = 0; j < A.numcols(); ++j) {
				if (j != i) {
					rowSum += (A[i][j] * x_old[j][0]);
				}
			}
			x_new[i][0] = ((b[i][0] - rowSum) / A[i][i]);
		}
		++iterationCount;
		err = x_old.relError(x_new);

		x_old = x_new;

//		std::cerr << "iterationCount: " << iterationCount << std::endl;
//		std::cerr << "x_old: " << endl << x_old << std::endl;
//		matrix bTest = A * x_old;

	}

	//std::cerr << "Relative error of Jacobi solution: " << err << endl;
	return iterationCount;
}

int IterativeSolvers::gaussSeidel(const matrix& A, matrix& x_old,
		const matrix& b) {
	if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows())) {
		cerr << "A nRows: " << A.numrows() << endl;
		cerr << "A nCols: " << A.numcols() << endl;
		cerr << "b nRows: " << b.numrows() << endl;
		cerr << "b nCols: " << b.numcols() << endl;
		throw std::logic_error("Matrix size mismatch");
	}

	int iterationCount = 0;
	double errLimit = 0.00001;
	double err = 1.0;

	matrix x_new(x_old);

	while (err > errLimit) {
		for (int i = 0; i < A.numrows(); ++i) {
//			std::cerr << " " << i;
			double rowSum = b[i][0];
			for (int j = 0; j < A.numcols(); ++j) {
				if (j < i) {
					rowSum -= (A[i][j] * x_new[j][0]);
				} else if (j > i) {
					rowSum -= (A[i][j] * x_old[j][0]);
				}
			}
			x_new[i][0] = (rowSum / A[i][i]);
		}
		++iterationCount;
		err = x_old.relError(x_new);

		x_old = x_new;

//		std::cerr << "iterationCount: " << iterationCount << std::endl;
//		std::cerr << "x_old: " << endl << x_old << std::endl;
//		matrix bTest = A * x_old;
	}

	//std::cerr << "Relative error of Jacobi solution: " << err << endl;
	return iterationCount;
}

int IterativeSolvers::successiveOverRelaxing(const double omega,
		const matrix& A, matrix& x, const matrix& b) {
	if (!(A.numcols() == A.numrows()) || !(A.numcols() == b.numrows())) {
		cerr << "A nRows: " << A.numrows() << endl;
		cerr << "A nCols: " << A.numcols() << endl;
		cerr << "b nRows: " << b.numrows() << endl;
		cerr << "b nCols: " << b.numcols() << endl;
		throw std::logic_error("Matrix size mismatch");
	}

	int iterationCount = 0;
	double errLimit = 0.00001;
	double err = 1.0;

	matrix x_old(x);
	matrix x_new(x);

	while ((err > errLimit) && (err < 10)) {
		for (int i = 0; i < A.numrows(); ++i) {
//			std::cerr << " " << i;
			double sigma = 0;

			for (int j = 0; j < i; ++j) {
				sigma += (A[i][j] * x_new[j][0]);
			}
			for (int j = i + 1; j < A.numcols(); ++j) {
				sigma += (A[i][j] * x_old[j][0]);
			}

			double bMinusSigma = b[i][0] - sigma;
			double x_old_i = x_old[i][0];

			x_new[i][0] = x_old_i
					+ (omega * ((bMinusSigma / A[i][i]) - x_old_i));

//			x_new[i][0] = ((1.0 - omega) * x_old[i][0]) + ((omega / A[i][i]) * bMinusSigma);
		}

		++iterationCount;
		err = x_old.relError(x_new);

		x_old = x_new;

//		std::cerr << "iterationCount: " << iterationCount << std::endl;
//		std::cerr << "x_old: " << endl << x_old << std::endl;
//		matrix bTest = A * x_old;
	}

	x = x_new;

	if (err >= 10) {
		std::cout << "ALERT: SOR diverges using " << omega
				<< " as a relaxation constant."
				<< " Perhaps choose another and try again?" << std::endl;
		std::cout << "Relative error of SOR solution: " << err << std::endl;
	}
	return iterationCount;
}

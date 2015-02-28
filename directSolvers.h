/*
 * directSolvers.h
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#ifndef DIRECTSOLVERS_H_
#define DIRECTSOLVERS_H_

#include "denseMatrix.h"

/*
 *
 */

typedef denseMatrix<double> matrix;


class directSolvers
{
public:

	static int findPivot(const matrix&, int);
	static void gaussianElimination(const matrix&, matrix&, const matrix&);
	static void backsolve(matrix&, matrix&);

};

#endif /* DIRECTSOLVERS_H_ */

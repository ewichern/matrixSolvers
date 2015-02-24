/*
 * IterativeSolvers.h
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#ifndef ITERATIVESOLVERS_H_
#define ITERATIVESOLVERS_H_

#include "denseMatrix.h"

/*
 *
 */

typedef denseMatrix<double> matrix;


class IterativeSolvers
{
public:
//	IterativeSolvers();
//	virtual ~IterativeSolvers();

	static int jacobi(const matrix&, matrix&, const matrix&);
	static int gaussSeidel(const matrix&, matrix&, const matrix&);

};

#endif /* ITERATIVESOLVERS_H_ */

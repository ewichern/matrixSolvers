/*
 * IterativeSolvers.h
 *
 *  Created on: Feb 6, 2015
 *      Author: erik
 */

#ifndef ITERATIVESOLVERS_H_
#define ITERATIVESOLVERS_H_

#include "sparseMatrix.h"

/*
 *
 */

typedef sparseMatrix<double> matrix;

class IterativeSolvers
{
public:
//	IterativeSolvers();
//	virtual ~IterativeSolvers();

	static int jacobiSolver(const matrix&, matrix&, const matrix&);

};

#endif /* ITERATIVESOLVERS_H_ */

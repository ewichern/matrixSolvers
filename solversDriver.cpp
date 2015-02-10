#include "sparseMatrix.h"
#include "matrixGenerator.h"
#include "IterativeSolvers.h"
#include <iostream>

#include "matrixSolver.cpp"

using namespace std;

typedef sparseMatrix<double> matrix;

int main(int argc, char **argv)
{
	// end of 1/15 video for initial detailed explanation

	if (argc > 2)
	{
		std::cerr << "Usage: \n";
		std::cerr << "   " << argv[0] << "Ab_matrixDataFile" << endl;
		return 1;
	}

	else if (argc == 2)
	{
		matrix A;
		matrix b;
		ifstream matricesIn(argv[1]);
		MatrixGenerator::readMatrixFromFile(matricesIn, A, b);

		matrix x(A.numcols(), 1, 0.1);
		int numIterations = IterativeSolvers::jacobiSolver(A, x, b);
		cout << "Jacobi solution: " << endl;
		cout << x;

		cout << "Jacobi completed in " << numIterations << " iterations."
				<< endl;
	}

	else
		mainMenu(std::cin);

	return 0;
}

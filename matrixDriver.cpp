#include "denseMatrix.h"
#include "matrixGenerator.h"
#include "IterativeSolvers.h"
#include <iostream>

#include "matrixSolver.cpp"

using namespace std;

typedef denseMatrix<double> matrix;

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
		int numIterations = IterativeSolvers::jacobi(A, x, b);
		cout << "Jacobi solution: " << endl;
		cout << x;

		cout << "Jacobi method completed in " << numIterations << " iterations."
				<< endl;
		cout << "Relative error of solution is: " << relError(b, (A*x)) << endl;
	}

	else
		mainMenu(std::cin);

	return 0;
}

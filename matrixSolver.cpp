/*
 * matrixSolver.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: erik
 */

#include "denseMatrix.h"
#include "matrixGenerator.h"
#include "IterativeSolvers.h"
#include <iostream>
#include <random>
#include <string>
#include <sstream>
#include <time.h>

using namespace std;

typedef denseMatrix<double> matrix;
enum solvers
{
	cancel = -1, jacobi = 1, gaussSeidel = 2, SOR = 3
};

int printMenuOptions(istream& input)
{
	cout << "1 - Input A and b matrices from a file." << endl;
	cout << "2 - Input matrix x from a file." << endl;
	cout << "3 - Multiply A by x (primarily for testing)" << endl;
	cout << "4 - Generate matrices filled with random "
			<< "doubles (user will be prompted for size)." << endl;
	cout << "5 - Use a solver to solve for x. (default is Jacobi method. "
			<< "matrices A and b must be loaded prior to executing solver)"
			<< endl;
	cout << "6 - Print most recent solution -- a solver should be run first "
			<< "using option 5." << endl;
	cout << "7 - Exit." << endl;
	cout << "Enter selection : " << endl;

	int selection;

	while (!(input >> selection) || ((selection < 1) || (selection > 7)))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return selection;
}

int printSolverOptions(istream& input)
{
	//TODO unit test
	std::cout << "1 - Jacobi Method" << std::endl;
	std::cout << "2 - Gauss-Seidel Method" << std::endl;
	std::cout << "3 - Successive Over Relaxation Method" << std::endl;
	std::cout << "4 - Cancel" << std::endl;
	std::cout << "Enter selection : " << std::endl;

	int selection;

	while (!(input >> selection) || ((selection < 1) || (selection > 4)))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return selection;
}

void getRelaxationConstant(double& omega, istream& input)
{
	//TODO unit test
	std::cout << "Enter relaxation constant : " << std::endl;

	while (!(input >> omega))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

string getFilename(istream& input)
{
	string name;
	while (!(input >> name))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return name;
}

string getFilenameRoot(istream& input)
{
	string filenameRoot = "";

	std::cout << "Enter the root of a filename where these matrices should be "
			<< "saved. The final filenames will be formatted \'root_Ab.dat\' "
			<< "and \'root_x.dat\'. Any existing files will be overwritten."
			<< std::endl;
	std::cout << "Filename root: " << std::endl;

	filenameRoot = getFilename(input);
	return filenameRoot;
}

string getABinputFilename(istream& input)
{
	string inputFilename = "";

	cout << "Enter the filename where data for A and b matrices has been "
			<< "stored. If A is an m*n matrix, b must be an n*1 matrix. "
			<< "Format should be: " << endl;
	cout << "AnumRows" << endl << "AnumCols" << endl
			<< "A data (separated by tabs/spaces/newlines)" << endl
			<< "b data (separated by tabs/spaces/newlines)" << endl;
	cout << "Filename: " << endl;

	inputFilename = getFilename(input);
	return inputFilename;
}

string getXinputFilename(istream& input)
{
	string inputFilename = "";

	cout << "Enter the filename where data for matrix x has been "
			<< "stored. If intending to multiply x by A, "
			<< "and A is an m*n matrix, x must be an n*_ matrix. "
			<< "Format should be: " << endl;
	cout << "x_numRows" << endl << "x_numCols" << endl
			<< "x data (separated by tabs/spaces/newlines)" << endl;
	cout << "Filename: " << endl;

	inputFilename = getFilename(input);
	return inputFilename;
}

string generateMatrixDataFiles(istream& input, matrix& A, matrix& b)
{
	int m = 3, n = 3;
	MatrixGenerator::askForMatrixSize(input, m, n);

	typedef std::uniform_real_distribution<double> distribType;
	//typedef std::uniform_int_distribution<> distribType;

	double min = -100.0;
	double max = 100.0;
	string filenameRoot = "";

	filenameRoot = getFilenameRoot(input);

	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	distribType dist(min, max);
	//distribType dist((int) min, (int) max);

	MatrixGenerator::generateSamples<distribType>(m, n, filenameRoot, generator,
			dist);

	std::ifstream readIn(filenameRoot + "_Ab.dat");
	MatrixGenerator::readMatrixFromFile(readIn, A, b);

	return filenameRoot;
}

string inputABfromFile(istream& input, matrix& A, matrix& b)
{
	string inputFilename = getABinputFilename(input);
	ifstream inFile(inputFilename);

	if (inFile)
	{
		MatrixGenerator::readMatrixFromFile(inFile, A, b);
		cout << "Matrices loaded from \"" << inputFilename << "\"" << endl;
		inFile.close();
	}
	else
	{
		cout << "\"" << inputFilename << "\" is not a valid filename." << endl;
		inputFilename = "fail";
	}
	return inputFilename;
}

string inputXfromFile(istream& input, matrix& x)
{
	string inputFilename = getXinputFilename(input);
	ifstream inFile(inputFilename);

	if (inFile)
	{
		MatrixGenerator::readMatrixFromFile(inFile, x);
		cout << "Matrix loaded from \"" << inputFilename << "\"" << endl;
		inFile.close();
	}
	else
	{
		cout << "\"" << inputFilename << "\" is not a valid filename." << endl;
		inputFilename = "fail";
	}
	return inputFilename;
}

string getSolverName(int enumValue)
{
	//TODO unit test
	switch (enumValue)
	{
	case jacobi:
		return "Jacobi method";
	case gaussSeidel:
		return "Gauss-Seidel method";
	case SOR:
		return "Successive Over-Relaxing";
	default:
		return "invalid value";
	}
}

void printSolution(const matrix& x)
{
	cout << "Solution x is: " << endl;
	cout << x << endl;
}

void multiplyAx(const matrix& A, const matrix& x, matrix& b)
{
	b = A * x;
	cout << "A * x = " << endl << b << endl;
}

int executeSolver(istream& input, int selection, const matrix& A, matrix& x,
		const matrix& b)
{
	clock_t t_0, t_end;
	int numIterations = -1;
	x = matrix(A.numcols(), 1, 1.0);
	double omega = 1.4;

	switch (selection)
	{
	case SOR:
		t_0 = clock();
		getRelaxationConstant(omega, input);
		numIterations = IterativeSolvers::successiveOverRelaxing(omega, A, x,
				b);
		t_end = clock();
		break;
	case gaussSeidel:
		t_0 = clock();
		numIterations = IterativeSolvers::gaussSeidel(A, x, b);
		t_end = clock();
		break;
	case jacobi:
	default:
		t_0 = clock();
		numIterations = IterativeSolvers::jacobi(A, x, b);
		t_end = clock();
		break;
	}
	cout << endl << "Solved in " << numIterations << " iterations using "
			<< getSolverName(selection) << "." << endl;
// matrix bTest = A * x;
// double err = relError(b, bTest);
	std::cout << "Relative error of solver solution: " << relError(b, (A * x))
			<< endl;
	std::cout << "Calculations took "
			<< ((float) (t_end - t_0)) / CLOCKS_PER_SEC << " seconds." << endl
			<< endl;
	return numIterations;
}

solvers solverMenu(istream& input)
{
//TODO unit test
	int menuSelection = 0;
	solvers solverSelection = jacobi;

	menuSelection = printSolverOptions(input);

	switch (menuSelection)
	{
	case 4:
		solverSelection = cancel;
		break;
	case SOR:
		solverSelection = SOR;
		break;
	case gaussSeidel:
		solverSelection = gaussSeidel;
		break;
	case jacobi:
	default:
		solverSelection = jacobi;
		break;
	}

	return solverSelection;
}

string mainMenu(istream& input)
{
//TODO unit test
	int menuSelection = 0;
	stringstream menuHistory;

	solvers solverSelection = jacobi;
//int numIterations = -1;

	matrix A, x, b;

	while (menuSelection != 7)
	{
		menuSelection = printMenuOptions(input);
		menuHistory << menuSelection;

		switch (menuSelection)
		{
		case 1:
			inputABfromFile(input, A, b);
			break;
		case 2:
			inputXfromFile(input, x);
			break;
		case 3:
			multiplyAx(A, x, b);
			break;
		case 4:
			generateMatrixDataFiles(input, A, b);
			break;
		case 5:
			if (A.numrows() == 0 || b.numrows() == 0)
			{
				cout << "Load A and b matrices from file before "
						<< "running solvers!" << endl << endl;
				break;
			}
			solverSelection = solverMenu(input);
			if (!(solverSelection == cancel))
				executeSolver(input, solverSelection, A, x, b);
			break;
		case 6:
			printSolution(x);
			break;
		default:
			break;
		}
	}

	return menuHistory.str();
}


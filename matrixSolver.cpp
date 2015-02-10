/*
 * matrixSolver.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: erik
 */

#include "sparseMatrix.h"
#include "matrixGenerator.h"
#include "IterativeSolvers.h"
#include <iostream>
#include <random>
#include <string>
#include <sstream>

using namespace std;

typedef sparseMatrix<double> matrix;

int printMenuOptions(istream& input)
{
	cout << "1 - Input A and b matrices from a file." << endl;
	cout << "2 - Generate matrices filled with random "
			<< "doubles (user will be prompted for size)." << endl;
	cout << "3 - Use an iterative solver to solve for x. (matrices A and b "
			<< "must be loaded prior to executing solver)" << endl;
	cout << "Not Yet Implemented - Use a direct solver to solve for x." << endl;
	cout << "4 - Exit." << endl;

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

	cout << "Enter the root of a filename where these matrices should be "
			<< "saved. The final filenames will be formatted \'root_Ab.dat\' "
			<< "and \'root_x.dat\'. Any existing files will be overwritten."
			<< endl;
	cout << "Filename root: " << endl;

	filenameRoot = getFilename(input);
	return filenameRoot;
}

string getInputFilename(istream& input)
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

string generateMatrixDataFiles(istream& input)
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

	return filenameRoot;
}

string inputFromFile(istream& input, matrix& A, matrix& b)
{
	string inputFilename = getInputFilename(input);
	ifstream inFile(inputFilename);

	MatrixGenerator::readMatrixFromFile(inFile, A, b);
	return inputFilename;
	//TODO give user feedback about whether file loaded properly
}

int executeIterativeSolver(int selection, const matrix& A, matrix& x,
		const matrix& b)
{
	int numIterations = -1;
	x = matrix(A.numcols(), 1, 0.1);

	switch (selection)
	{
	case 0:
		numIterations = IterativeSolvers::jacobiSolver(A, x, b);
		break;
	default:
		break;
	}
	return numIterations;
}

string mainMenu(istream& input)
{
	int menuSelection = 0;
	stringstream menuHistory;
	enum iterative
	{
		jacobi, gaussSeidel, SOR
	};

	iterative solverSelection = jacobi;
	int numIterations = -1;

	matrix A, x, b;

	while (menuSelection != 4)
	{
		menuSelection = printMenuOptions(input);
		menuHistory << menuSelection;

		switch (menuSelection)
		{
		case 1:
			inputFromFile(input, A, b);
			break;
		case 2:
			generateMatrixDataFiles(input);
			break;
		case 3:

			numIterations = executeIterativeSolver(solverSelection, A, x, b);

			//TODO switch for printing out correct text based on enum
			cout << "Solved in " << numIterations << " iterations using "
					<< solverSelection << " iteration." << endl;

			break;
		default:
			break;
		}
	}

	return menuHistory.str();
}


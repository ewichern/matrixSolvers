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
#include <fstream>
#include <random>
#include <string>

using namespace std;

typedef sparseMatrix<double> matrix;

int printMenuOptions()
{
	cout << "1 - Input A and b matrices from a file." << endl;
	cout << "2 - Generate matrices filled with random "
			<< "doubles (user will be prompted for size)." << endl;
	cout << "3 - Use an iterative solver to solve for x." << endl;
	cout << "Not Yet Implemented - " << "Use a direct solver to solve for x."
			<< endl;
	cout << "4 - Exit." << endl;

	int selection;

	while (!(cin >> selection) && ((selection < 1) || (selection > 4)))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return selection;
}

string getFilenameRoot(istream& input)
{

	string filenameRoot = "";

	cout << "Enter the root of a filename where these "
			<< "matrices should be saved. The final filenames "
			<< "will be formatted \'root_Ab.dat\' and \'root_x.dat\'. "
			<< "Any existing files will be overwritten." << endl;
	cout << "Filename root: " << endl;

	while (!(input >> filenameRoot))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return filenameRoot;
}

void generateMatrices()
{

	int m = 3, n = 3;
	MatrixGenerator::askForMatrixSize(std::cin, m, n);

	typedef std::uniform_real_distribution<double> distribType;
	//typedef std::uniform_int_distribution<> distribType;

	double min = -100.0;
	double max = 100.0;
	string filenameRoot = "";

	filenameRoot = getFilenameRoot(cin);

	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	distribType dist(min, max);
	//distribType dist((int) min, (int) max);

	MatrixGenerator::generateSamples<distribType>(m, n, filenameRoot,
			randDevice, generator, dist);
}

void inputFromFile()
{

}

void mainMenu()
{
	int menuSelection = 0;

	while (menuSelection != 4)
	{
		menuSelection = printMenuOptions();
		switch (menuSelection)
		{
		case 1:
			break;
		case 2:
			generateMatrices();
			break;
		case 3:
			break;
		default:
			break;
		}
	}
}

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
		mainMenu();

	return 0;
}

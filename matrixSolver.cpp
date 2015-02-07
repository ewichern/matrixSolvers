/*
 * matrixSolver.cpp
 *
 *  Created on: Jan 23, 2015
 *      Author: erik
 */

#include "sparseMatrix.h"
#include "matrixGenerator.h"
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

void generateMatrices()
{
	typedef std::uniform_real_distribution<double> distribType;
	//typedef std::uniform_int_distribution<> distribType;

	double min = -100.0;
	double max = 100.0;
	string filenameRoot;

	cout << "Enter the root of a filename where these "
			<< "matrices should be saved. The final filenames "
			<< "will be formatted \'root_Ab.dat\' and \'root_x.dat\'. "
			<< "Any existing files will be overwritten." << endl;
	cout << "Filename root: " << endl;

	while (!(cin >> filenameRoot))
	{
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


	std::random_device randDevice;
	std::mt19937 generator(randDevice());
	distribType dist(min, max);
	//distribType dist((int) min, (int) max);

	MatrixGenerator::generateSamples<distribType > (filenameRoot, randDevice, generator, dist);
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

	matrix A;
	//matrix x;
	matrix b;

	if (argc > 2)
	{
		std::cerr << "Usage: \n";
		std::cerr << "   " << argv[0] << "matrixDataFile" << endl;
		return 1;
	}

	if (argc == 2)
	{
		ifstream matricesIn(argv[1]);
		MatrixGenerator::readMatrixFromFile(matricesIn, A, b);
	}

	mainMenu();

	return 0;
}

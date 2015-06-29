/*
 * rootDriver.cpp
 *
 *  Created on: Apr 3, 2015
 *      Author: erik
 */

#include "rootSolvers.h"
#include "polynomial.h"
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include <vector>

using namespace std;

enum solvers
{
	cancel = -1, bisection = 1, falsePosition = 2, newton = 3
};

// TODO write documentation comments
int printRootMenuOptions(std::istream& input)
{
	std::cout << "1 - Input expression as polynomial coefficients."
			<< std::endl;
	std::cout << "2 - Solve polynomial expression using bisection."
			<< std::endl;
	std::cout << "3 - Solve polynomial expression using false-position."
			<< std::endl;
	std::cout << "4 - Solve polynomial expression using newton." << std::endl;
	std::cout << "5 - Print polynomial expression." << std::endl;
	std::cout << "0 - Exit." << std::endl;
	std::cout << "Enter selection : " << std::endl;

	int selection;

	while (!(input >> selection) || ((selection < 0) || (selection > 5)))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return selection;
}

// TODO write documentation comments
std::vector<double> getExpression(istream& input)
{
	std::vector<double> coeffs;
	double coeff = 0.0;

	std::cout << "Enter the coefficients for a polynomial expression, beginning \n"
			<< "with C*x^0 (i.e. 'reverse' of what most people would call the \n"
			<< "normal order when an expression is written with descending \n"
			<< "powers of a variable) and continuing until you've entered all \n"
			<< "desired terms. If no term with a specific power of x is \n"
			<< "required, enter a zero for that term's coefficient. \n\n";

	while (input >> coeff)
	{
		if (input.good())
			coeffs.push_back(coeff);
		else
		{
			input.clear();
			input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid input, try again: \n";
		}
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return coeffs;
}

// TODO write documentation comments
void getBrackets(double& lower, double& upper, istream& input)
{
	std::cout << "Enter lower, then upper bracketing limits: " << std::endl;

	while (!(input >> lower >> upper) || (lower > upper))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

// TODO write documentation comments
void getRootGuess(double& guess, istream& input)
{
	std::cout << "Enter initial guess for root for Newton-Raphson solver: "
			<< std::endl;

	while (!(input >> guess))
	{
		input.clear();
		input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input, try again: \n";
	}
	input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

}

// TODO write documentation comments
string getRootSolverName(int enumValue)
{
	switch (enumValue)
	{
	case bisection:
		return "Bisection method";
	case falsePosition:
		return "Regula-Falsi method";
	case newton:
		return "Newton-Raphson method";
	default:
		return "invalid solver selection";
	}
}

// TODO write documentation comments
void executeRootSolver(istream& input, int selection, const polynomial expr)
{
	int numIterations = -1;
	double lower, upper, root_guess, solution;
	double errLim = 0.00001;

	switch (selection)
	{
	case bisection:
		getBrackets(lower, upper, input);
		solution = rootSolvers::bisection(expr, lower, upper, numIterations,
				errLim);
		break;
	case falsePosition:
		getBrackets(lower, upper, input);
		solution = rootSolvers::falsePosition(expr, lower, upper, numIterations,
				errLim);
		break;
	case newton:
		getRootGuess(root_guess, input);
		solution = rootSolvers::newton(expr, root_guess, numIterations, errLim);
		break;
	default:
		break;
	}

	std::cout << expr << " has a root of " << solution << ", arrived at via "
			<< getRootSolverName(selection) << " in " << numIterations
			<< " iterations." << std::endl << std::endl;
}

// TODO write documentation comments
std::string rootMainMenu(std::istream& input)
{
	int menuSelection = -1;
	std::stringstream menuHistory;

//	solvers solverSelection = bisection;

	polynomial expression;

	while (menuSelection != 0)
	{
		menuSelection = printRootMenuOptions(input);
		menuHistory << menuSelection;

		switch (menuSelection)
		{
		case 1:
			expression = polynomial(getExpression(input));
			break;
		case 2:
			executeRootSolver(input, 1, expression);
			break;
		case 3:
			executeRootSolver(input, 2, expression);
			break;
		case 4:
			executeRootSolver(input, 3, expression);
			break;
		case 5:
			std::cout << expression << std::endl << std::endl;
			break;
		default:
			break;
		}
	}

	return menuHistory.str();
}

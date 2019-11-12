#ifndef EQUATION_RESOLVER_H
#define EQUATION_RESOLVER_H

#include <string>
#include <vector>
#include <fstream>
#include "EquationCorrectness.h"

class EquationResolver
{
private:
	std::string equation;

	EquationCorrectness equationChecker;

public:
	EquationResolver();

	EquationResolver(std::string equation);

	~EquationResolver();

	void setEquation(std::string & equation);

	void setEquationFromFile(std::string filename);

	double resolve();

	double resolve(std::string &equation);

private:
	double calculate(double &number1, double &number2, char &operation);

	std::vector<std::string> reversePolishNotation(std::vector<std::string> &equationItems);

	std::vector<std::string> prepareDataStructures(std::string &equation);

	int priority(char &c);
};

#endif
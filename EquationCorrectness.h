#ifndef EQUATION_CORRECTNESS_H
#define EQUATION_CORRECTNESS_H

#include <string>
#include <algorithm>
#include <iostream>

class EquationCorrectness
{
private:
	const std::string 
		LEGAL_CHARACTERS,
		OPERATIONS;
public:
	EquationCorrectness();

	~EquationCorrectness();

	bool check(std::string &equation);

	bool isNumberPart(char &c);

	bool isOperator(char &c);

	bool isBracket(char &c);

	bool isOpeningBracket(char &c);

	bool isClosingBracket(char &c);

	int lastNumberIndex(std::string &s, int start);

	bool isDigit(char &c);

private:
	// (',' => '.') & ('\' => '/') & ('—' => '-')
	void conversions(std::string &s);

	void removeWhiteSymbols(std::string &s);

	//number of '(' equals number of ')'
	bool checkBrackets(std::string &equation);
};

#endif
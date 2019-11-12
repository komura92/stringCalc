#include "EquationCorrectness.h"

EquationCorrectness::EquationCorrectness() :
	LEGAL_CHARACTERS("()*/-+0987654321^."),
	OPERATIONS("/*-+^")
{
}

EquationCorrectness::~EquationCorrectness()
{
}

bool EquationCorrectness::check(std::string & equation)
{
	std::string out{}; 
	
	bool 
		pointUsed = false,
		wasOperator = false,
		wasOpeningBracket = false,
		wasClosingBracket = false,
		wasNumber = false;

	removeWhiteSymbols(equation);
	conversions(equation);

	if (!checkBrackets(equation)) {
		std::cout << "U probably should check brackets, bro. :D" << std::endl;
		return false;
	}

	if (isOperator((equation[equation.length() - 1]))) {
		std::cout << "Are U sure that's end of this equation? I'm not." << std::endl;
		return false;
	}

	for (char c : equation) {

		if (LEGAL_CHARACTERS.find(c) == std::string::npos) {
			std::cout << "Illegal character... Focus! [" << c << ']' << std::endl;
			return false;
		}
		else if (isNumberPart(c)) {
			if (c == '.') {
				if (pointUsed) {
					std::cout << "Two points in one number? Wtf, man?" << std::endl;
					return false;
				}
				pointUsed = true;
			}
			if (wasClosingBracket)
				out += '*';
			wasOperator = false;
			wasOpeningBracket = false;
			wasClosingBracket = false;
			wasNumber = true;
		}
		else if (isOperator(c)) {
			if (wasOperator) {
				std::cout << "Two consecutive operators?! C'mon..." << std::endl;
				return false;
			}
			else if (wasOpeningBracket) {
				if (c != '-') {
					std::cout << "Operator after opening bracket? Nope..." << std::endl;
					return false;
				}
				out += '0';
			}
			wasOperator = true;
			pointUsed = false;
			wasOpeningBracket = false;
			wasClosingBracket = false;
			wasNumber = false;
		}
		else if (isBracket(c)) {
			if (wasOpeningBracket && isClosingBracket(c)) {
				std::cout << "Why U're opening and immediately closing bracket? U don't know? Mee too!" << std::endl;
				return false;
			}
			else if (wasOperator && isClosingBracket(c)) {
				std::cout << "Operator before closing bracket? Whyyyyyy?!" << std::endl;
				return false;
			}
			wasOpeningBracket = isOpeningBracket(c);
			if (wasClosingBracket && wasOpeningBracket)
				out += '*';
			wasClosingBracket = isClosingBracket(c);
			wasOperator = false;
			pointUsed = false;
			if (wasNumber && wasOpeningBracket)
				out += '*';
			wasNumber = false;
		}
		out += c;
	}
	equation = out;
	return true;
}

void EquationCorrectness::conversions(std::string & s)
{
	std::string out{};

	for (char c : s)
		if (c == ',')
			out += '.';
		else if (c == '—')
			out += '-';
		else if (c == '\\')
			out += '/';
		else
			out += c;

	s = out;
}

void EquationCorrectness::removeWhiteSymbols(std::string & s)
{
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	s.erase(std::remove(s.begin(), s.end(), '	'), s.end());
	s.erase(std::remove(s.begin(), s.end(), '\n'), s.end());
}

bool EquationCorrectness::isDigit(char & c)
{
	return (c >= '0') && (c <= '9');
}

bool EquationCorrectness::isNumberPart(char & c)
{
	return isDigit(c) || c == '.';
}

bool EquationCorrectness::isOperator(char & c)
{
	return OPERATIONS.find(c) != std::string::npos;
}

bool EquationCorrectness::checkBrackets(std::string & equation)
{
	int counter = 0;

	for (char c : equation)
		if (c == '(')
			counter++;
		else if (c == ')')
			counter--;

	return counter == 0;
}

bool EquationCorrectness::isBracket(char & c)
{
	return isOpeningBracket(c) || isClosingBracket(c);
}

bool EquationCorrectness::isOpeningBracket(char & c)
{
	return c == '(';
}

bool EquationCorrectness::isClosingBracket(char & c)
{
	return c == ')';
}

int EquationCorrectness::lastNumberIndex(std::string & s, int start)
{
	size_t i = start;

	for (; i < s.length(); i++)
		if (!isNumberPart(s[i]))
			break;

	return --i;
}

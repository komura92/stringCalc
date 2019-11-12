#include "EquationResolver.h"

EquationResolver::EquationResolver() :
	equation("")
{
}

EquationResolver::EquationResolver(std::string equation)
{
	this->equation = equation;
}

EquationResolver::~EquationResolver()
{
}

void EquationResolver::setEquation(std::string & equation)
{
	this->equation = equation;
}

void EquationResolver::setEquationFromFile(std::string filename)
{
	std::ifstream file(filename);
	char c;
	std::string data{};

	if (!file.good()) {
		std::cout << "Error opening file!" << std::endl;
		return;
	}
	file >> std::noskipws;

	while (true) {
		file >> c;
		if (file.eof())
			break;
		data += c;
	}

	file.close();
	equation = data;
	std::cout << data << std::endl;
}

double EquationResolver::resolve()
{
	if (equation == "") {
		std::cout << "First set the equation!" << std::endl;
		return 0.0;
	}

	if (!equationChecker.check(equation)) {
		equation = "";
		return 0.0;
	}

	double result{};
	std::string item{};

	std::vector<std::string> items = prepareDataStructures(equation);
	items = reversePolishNotation(items);
	std::vector<double> numbers{};
	double number1, number2;

	for (std::vector<std::string>::iterator i = items.begin(); i != items.end(); i++) {
		item = *i;

		if (equationChecker.isNumberPart(item[0])) {
			numbers.push_back(std::stod(item));
		}
		else if (equationChecker.isOperator(item[0])) {
			number1 = numbers.back();
			numbers.pop_back();

			if (!numbers.empty()) {
				number2 = numbers.back();
				numbers.pop_back();
			}
			else {
				number2 = 0.0;
			}
			result = calculate(number2, number1, item[0]);
			numbers.push_back(result);
		}
	}
	return numbers.back();
}

double EquationResolver::resolve(std::string & equation)
{
	setEquation(equation);
	return resolve();
}

double EquationResolver::calculate(double &number1, double &number2, char &operation)
{
	switch (operation)
	{
	case '-':
		return number1 - number2;
	case '+':
		return number1 + number2;
	case '/':
		return number1 / number2;
	case '*':
		return number1 * number2;
	case '^':
		return pow(number1, number2);
	default:
		return 0.0;
	}
}

std::vector<std::string> EquationResolver::prepareDataStructures(std::string & equation)
{
	std::vector<std::string> items{};
	char c;
	std::string number{};

	for (size_t i{}; i < equation.length(); i++) {
		c = equation[i];
		if (equationChecker.isBracket(c) || equationChecker.isOperator(c)) {
			number = equation.substr(i, 1);
			//std::cout << c << std::endl;
			items.push_back(number);
		}
		else if (equationChecker.isNumberPart(c)) {
			number = equation.substr(i, equationChecker.lastNumberIndex(equation, i) - i + 1);
			//std::cout << number << std::endl;
			i = equationChecker.lastNumberIndex(equation, i);
			items.push_back(number);
		}
	}

	return items;
}

int EquationResolver::priority(char & c)
{
	if ((c == '-') || (c == '+'))
		return 0;
	else if ((c == '*') || (c == '/'))
		return 1;
	else if (c == '^')
		return 2;

	return -1;
}

std::vector<std::string> EquationResolver::reversePolishNotation(std::vector<std::string>& equationItems)
{
	std::vector<std::string> out{}, stack{};
	std::string item;
	char c;

	for (std::vector<std::string>::iterator i = equationItems.begin();
		i != equationItems.end();
		i++) {
		c = (*i)[0];
		if (equationChecker.isNumberPart(c))
			out.push_back(*i);
		else if (equationChecker.isOpeningBracket(c))
			stack.push_back(*i);
		else if (equationChecker.isOperator(c)) {
			while ((!stack.empty()) && (priority(c) <= priority(stack.back()[0]))) {
				out.push_back(stack.back());
				stack.pop_back();
			}
			stack.push_back(*i);
		}
		else if (equationChecker.isClosingBracket(c)) {
			while ((!stack.empty()) && (!equationChecker.isOpeningBracket(stack.back()[0]))) {
				out.push_back(stack.back());
				stack.pop_back();
			}
			stack.pop_back();
		}
	}

	while (!stack.empty()) {
		out.push_back(stack.back());
		stack.pop_back();
	}

	return out;
}
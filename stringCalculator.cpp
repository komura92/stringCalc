#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

void removeWhiteSymbols(std::string &s);

bool isCorrect(std::string &s);

double resolve(std::string &equation);

std::vector<std::string> reversePolishNotation(std::vector<std::string> &equationItems);

std::vector<std::string> prepareDataStructures(std::string &equation);

bool isDigit(char &c);

bool isNumberPart(char &c);

bool isOperator(char &c);

bool checkBrackets(std::string &equation);

bool isBracket(char &c);

bool isOpeningBracket(char c);

bool isClosingBracket(char c);

int priority(char c);

int lastNumberIndex(std::string &s, int start);

void display(std::vector<std::string> &s);

double calculate(double number1, double number2, char operation);

int main() {
	double result{};
	std::string s = "-2+(-2,05\\0—4)2(-3+2)";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = "-2+((-2,05\\31—4)2)(3+2)";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = "-2+(-2,05\\31—4)2(3+2)*";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = " 4.2 *    3";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;


	s = "(   2*3)  +6";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;


	s = "  1* 4+	3";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;


	s = "-(3*2)*3+7";
	std::cout << s << std::endl;
	result = resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	getchar();
	getchar();
	return 0;
}

// (',' => '.') & ('\' => '/') & ('—' => '-')
void conversions(std::string &s) {
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

void removeWhiteSymbols(std::string &s) {
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	s.erase(std::remove(s.begin(), s.end(), '	'), s.end());
}

bool isCorrect(std::string &s) {
	std::string LEGAL_CHARACTERS = "()*/-+0987654321^.",
		out{};
	bool pointUsed = false,
		wasOperator = false,
		wasOpeningBracket = false,
		wasClosingBracket = false,
		wasNumber = false;

	removeWhiteSymbols(s);
	conversions(s);

	if (!checkBrackets(s)) {
		std::cout << "U probably should check brackets, bro. :D" << std::endl;
		return false;
	}

	if (isOperator((s[s.length() - 1]))) {
		std::cout << "Are U sure that's end of this equation? I'm not." << std::endl;
		return false;
	}

	for (char c : s) {

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
	s = out;
	return true;
}

double resolve(std::string &equation) {

	if (!isCorrect(equation))
		return 0.0;

	double result{};
	std::string item{};

	std::vector<std::string> items = prepareDataStructures(equation);
	items = reversePolishNotation(items);
	std::vector<double> numbers{};
	double number1, number2;

	for (std::vector<std::string>::iterator i = items.begin(); i != items.end(); i++) {
		item = *i;

		if (isNumberPart(item[0])) {
			numbers.push_back(std::stod(item));
		}
		else if (isOperator(item[0])) {
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

std::vector<std::string> reversePolishNotation(std::vector<std::string> &equationItems) {
	std::vector<std::string> out{}, stack{};
	std::string item;
	char c;

	for (std::vector<std::string>::iterator i = equationItems.begin();
			i != equationItems.end();
			i++) {
		c = (*i)[0];
		if (isNumberPart(c))
			out.push_back(*i);
		else if (isOpeningBracket(c))
			stack.push_back(*i);
		else if (isOperator(c)) {
			while ((!stack.empty()) && (priority(c) <= priority(stack.back()[0]))) {
				out.push_back(stack.back());
				stack.pop_back();
			}
			stack.push_back(*i);
		}
		else if (isClosingBracket(c)) {
			while ((!stack.empty()) && (!isOpeningBracket(stack.back()[0]))) {
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

std::vector<std::string> prepareDataStructures(std::string &equation) {
	std::vector<std::string> items{};
	char c;
	std::string number{};

	for (size_t i{}; i < equation.length(); i++) {
		c = equation[i];
		if (isBracket(c) || isOperator(c)) {
			number = equation.substr(i, 1);
			//std::cout << c << std::endl;
			items.push_back(number);
		}
		else if (isNumberPart(c)) {
			number = equation.substr(i, lastNumberIndex(equation, i) - i + 1);
			//std::cout << number << std::endl;
			i = lastNumberIndex(equation, i);
			items.push_back(number);
		}
	}

	return items;
}

bool isDigit(char &c) { return (c >= '0') && (c <= '9'); }

bool isNumberPart(char &c) { return isDigit(c) || c == '.'; }

int priority(char c) {
	if ((c == '-') || (c == '+'))
		return 0;
	else if ((c == '*') || (c == '/'))
		return 1;
	else if (c == '^')
		return 2;

	return -1;
}

bool isOperator(char &c) {
	const std::string operations = "/*-+^";
	return operations.find(c) != std::string::npos;
}

bool isBracket(char &c) { return isOpeningBracket(c) || isClosingBracket(c); }

bool isOpeningBracket(char c) { return c == '('; }

bool isClosingBracket(char c) { return c == ')'; }

//number of '(' equals number of ')'
bool checkBrackets(std::string &equation) {
	int counter = 0;

	for (char c : equation)
		if (c == '(')
			counter++;
		else if (c == ')')
			counter--;

	return counter == 0;
}

int lastNumberIndex(std::string &s, int start) {
	size_t i = start;
	
	for (; i < s.length(); i++)
		if (!isNumberPart(s[i]))
			break;

	return --i;
}

void display(std::vector<std::string> &s)
{
	for (std::vector<std::string>::iterator i = s.begin(); i != s.end(); i++)
		std::cout << *i << std::endl;
}

double calculate(double number1, double number2, char operation) {
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

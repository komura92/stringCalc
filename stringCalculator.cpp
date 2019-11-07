#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

void removeWhiteSymbols(std::string &s);

bool isCorrect(std::string &s);

void resolve(std::string &equation);

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

int main() {
	std::string s = "(2,05/31+4)*2";
	std::cout << s;
	std::cout << "	" << isCorrect(s) << std::endl;
	std::vector<std::string> v = prepareDataStructures(s);
	//display(v);
	v = reversePolishNotation(v);
	display(v);
	/*s = " 4 *    a";
	std::cout << s;
	std::cout << "	" << isCorrect(s) << std::endl;


	s = "(   2*3)  +6";
	std::cout << s;
	std::cout << "	" << isCorrect(s) << std::endl;


	s = "  1* 4+	3";
	std::cout << s;
	std::cout << "	" << isCorrect(s) << std::endl;*/

	getchar();
	return 0;
}

void pointToDot(std::string &s) {
	std::string out{};

	for (char c : s)
		if (c == ',')
			out += '.';
		else
			out += c;
	
	s = out;
}

void removeWhiteSymbols(std::string &s) {
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
	s.erase(std::remove(s.begin(), s.end(), '	'), s.end());
}

bool isCorrect(std::string &s) {
	std::string LEGAL_CHARACTERS = "()*/-+0987654321^.";
	bool pointUsed = false,
		wasOperator = false,
		wasBracket = false;

	removeWhiteSymbols(s);
	pointToDot(s);

	if (!checkBrackets(s)) {
		std::cout << "U probably should check brackets, bro. :D" << std::endl;
		return false;
	}

	//replace '\' with '/'

	//replace big minus with -

	//TODO No symbol '*' near to brackets - need to add it for processing


	for (char c : s)
		if (LEGAL_CHARACTERS.find(c) == std::string::npos) {
			std::cout << "Illegal character... Focus!" << std::endl;
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
			wasOperator = false;
			wasBracket = false;
		} else if (isOperator(c)) {
			if (wasOperator) {
				std::cout << "Two consecutive operators?! C'mon..." << std::endl;
				return false;
			}
			wasOperator = true;
			pointUsed = false;
			wasBracket = false;
		} else if (isBracket(c)) {
			//TODO one more possibility: ((
			if (wasBracket)
				return false;
			wasOperator = false;
			pointUsed = false;
			wasBracket = true;
		}

	return true;
}

void resolve(std::string &equation) {

	if (!isCorrect(equation))
		return;

	double result{};

	std::vector<std::string> items = prepareDataStructures(equation);

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

	for (std::vector<std::string>::iterator i = stack.begin();
		i != stack.end();
		i++) {
		out.push_back(*i);
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

//to replace with string
bool isOperator(char &c) { return (c == '/') || (c == '*') || (c == '-') || (c == '+'); }

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

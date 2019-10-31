#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

void removeWhiteSymbols(std::string &s);

bool isCorrect(std::string &s);

void resolve(std::string &equation);

std::string reversePolishNotation(std::string &equation);

std::vector<std::string> prepareDataStructures(std::string &equation);

bool isDigit(char &c);

bool isNumberPart(char &c);

bool isOperator(char &c);

bool isBracket(char &c);

int main() {
	std::string s = "(2,05/31+4)*2";
	std::cout << s;
	std::cout << "	" << isCorrect(s) << std::endl;

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


	for (char c : s)
		if (LEGAL_CHARACTERS.find(c) == std::string::npos)
			return false;
		else if (isNumberPart(c)) {
			if (c == '.') {
				if (pointUsed)
					return false;
				pointUsed = true;
			}
			wasOperator = false;
			wasBracket = false;
		} else if (isOperator(c)) {
			if (wasOperator)
				return false;
			wasOperator = true;
			pointUsed = false;
			wasBracket = false;
		} else if (isBracket(c)) {
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

std::string reversePolishNotation(std::string &equation) {
	std::string out = "";

	for (char c : equation) {
		//if

		out += c;
	}

	return out;
}

std::vector<std::string> prepareDataStructures(std::string &equation) {
	std::vector<std::string> items{};

	//opers

	return items;
}

bool isDigit(char &c) { return (c >= '0') && (c <= '9'); }

bool isNumberPart(char &c) { return isDigit(c) || c == '.'; }

bool isOperator(char &c) { return (c == '/') || (c == '*') || (c == '-') || (c == '+'); }

bool isBracket(char &c) { return (c == '(') || (c == ')'); }

int lastNumberIndex(std::string &s, int start) {
	int i = start;
	
	for (; i < s.length(); i++)
		if (!isNumberPart(s[i]))
			break;

	return --i;
}
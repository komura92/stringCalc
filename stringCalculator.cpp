#include <iostream>
#include "EquationResolver.h"

int main() {
	EquationResolver resolver;

	resolver.setEquationFromFile("equation");
	std::cout << resolver.resolve() << std::endl << std::endl;
	/*double result{};
	std::string s = "-2+(-2,05\\0—4)2(-3+2)";
	std::cout << s << std::endl;
	result = resolver.resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = "-2+((-2,05\\31—4)2)(3+2)";
	std::cout << s << std::endl;
	result = resolver.resolve(s);
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = "-2+((-2,05\\31—4)2)^(3+2-1)";
	std::cout << s << std::endl;
	resolver.setEquation(s);
	result = resolver.resolve();
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = "-2+(-2,05\\31—4)2(3+2)*";
	std::cout << s << std::endl;
	resolver.setEquation(s);
	result = resolver.resolve();
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;

	s = " 4.2 *    3";
	std::cout << s << std::endl;
	resolver.setEquation(s);
	result = resolver.resolve();
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;


	s = "(   2*3)  +6";
	std::cout << s << std::endl;
	resolver.setEquation(s);
	result = resolver.resolve();
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;


	s = "  1* 4+	3";
	std::cout << s << std::endl;
	resolver.setEquation(s);
	result = resolver.resolve();
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;


	s = "-(3*2)*3+7";
	std::cout << s << std::endl;
	resolver.setEquation(s);
	result = resolver.resolve();
	std::cout << s << std::endl;
	std::cout << result << std::endl << std::endl;*/

	getchar();
	getchar();
	return 0;
}


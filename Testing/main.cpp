#include "main.h"

int main() {
	calc calc(getValidInput());
	printVector(calc.getParenthesesRank());
	printVector(calc.getParenthesesLocation());
	printVector(calc.getNumberList());
	printVector(calc.getNumberLocation());
	printVector(calc.getOperatorRank());
	printVector(calc.getOperatorList());
	printVector(calc.getOperatorLocation());
	
	std::cout << "Answer: " << calc.findAnswer() << std::endl;

	return 0;
}

void removeSpaces(std::string& input) {
	int offset = 0;
	char temp;
	for (int i = 0; i < input.length(); i++) {
		temp = input[i];
		input[i - offset] = temp;
		if (input[i] == ' ') {
			offset++;
		}
		if (i == input.length() - 1) {
			input.erase(input.length() - offset, input.length());
		}
	}
}

bool isValidEquation(std::string input) {
	for (int i = 0; i < input.length(); i++) {
		if (!((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '^') || isdigit(input[i]) || (input[i] == '.') || (input[i] == '(') || (input[i] == ')') || (input[i] == '[') || (input[i] == ']') || (input[i] == ' '))) {
			return false;
		}
	}
	return true;
}

std::string getValidInput() {
	std::cout << "Please enter a valid Equation. (Supports: ##.##, (), [], +, -, *, /, ^)\n";
	std::cout << "I don't have error checking for multiple operators in a row so please avoid that.\n";
	std::string input;
	std::getline(std::cin, input);
	while (!isValidEquation(input)) {
		std::cout << "Please enter a valid Equation. (Supports: ##.##, (), [], +, -, *, /, ^)\n";
		std::string input;
		std::getline(std::cin, input);
	}

	return input;
}

void printVector(std::vector<int> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void printVector(std::vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}

void printVector(std::vector<char> vec) {
	for (int i = 0; i < vec.size(); i++) {
		std::cout << vec[i] << " ";
	}
	std::cout << std::endl;
}
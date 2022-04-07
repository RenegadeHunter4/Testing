#include "main.h"

double inputProcessing(const std::string input) {

	// Decalre Variables
	std::string num;
	double numbers[2];
	int numIndex = 0;
	bool flag = false;
	int type = 0;

	// Loops Through ever letter in input string
	for (int i = 0; i < input.length(); i++) {
		// Needed for Recursion
		if (flag) {
			num = num + input[i];
		}

		// Checks if number is a number.
		else if (isdigit(input[i]) || (input[i] == '.')) {
			num = num + input[i];
		}

		// If not a number:
		else {
			// To filter out the first loop
			if (!num.empty()) {
				// Does this after encountering first operator
				if(numIndex == 0) {
					numbers[numIndex] = std::stod(num);
					num = "";
					numIndex++;
				}
				// Does this after encountering second opeartor (Concatanates Rest of String and uses recursion to start over.)
				else if (numIndex == 1) {
					num = num + input[i];
					flag = true;
					numIndex = 2;
				}
			}
			// Doesn't update operator if encounters second operator.
			if (numIndex != 2) {

				// Choses Operator
				if (input[i] == '+') { type = 1; }
				else if (input[i] == '-') { type = 2; }
				else if (input[i] == '*') { type = 3; }
				else if (input[i] == '/') { type = 4; }
				else {
					std::cout << "ERROR: " << input[i] << " is not supported.\n";
					return 0;
				}
			}
		}
	}

	// Output if user only enters a number
	if (numIndex == 0) {
		return std::stod(input);
	}

	// Output if user enters 2 numbers
	else if (numIndex == 1) {
		numbers[numIndex] = std::stod(num);

		switch (type) {
		case 1:
			return numbers[0] + numbers[1];
			break;
		case 2:
			return numbers[0] - numbers[1];
			break;
		case 3:
			return numbers[0] * numbers[1];
			break;
		case 4:
			return numbers[0] / numbers[1];
			break;
		default:
			std::cout << "ERROR: Switch Failed, Unknwon Cause\n";
			return 0;
		}
	}

	// Output if user enters more then 2 numbers (Uses recursion)
	else {
		switch (type) {
		case 1:
			return numbers[0] + inputProcessing(num);
			break;
		case 2:
			return numbers[0] - inputProcessing(num);
			break;
		case 3:
			return numbers[0] * inputProcessing(num);
			break;
		case 4:
			return numbers[0] / inputProcessing(num);
			break;
		default:
			std::cout << "ERROR: Switch Failed, Unknwon Cause\n";
			return 0;
		}
	}
	
}

std::string removeSpaces(std::string input) {
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

	return input;
}

std::string checkForParentheses(std::string input, std::string (&parenthesesArray)[32]) {
	int arrayI = 0;
	char letter = 'a';

	for (int i = 0; i < input.length(); i++) {
		if ((input[i] == '(') || (input[i] == '[')) {
			if (arrayI != 0) { letter++; }
			std::string l(1, letter);
			parenthesesArray[arrayI] = l + std::to_string(i);
			arrayI++;
		}
		else if ((input[i] == ')') || (input[i] == ']')) {
			std::string l(1, letter);
			parenthesesArray[arrayI] = l + std::to_string(i);
			arrayI++;
			letter--;
		}
	}

	for (int i = 0; i < 32; i++) {
		std::cout << parenthesesArray[i] << " ";
	}
	std::cout << std::endl;

	return input;
}

int main() {
	std::cout << "Creating Window\n";
	std::string parentheses[32];

	std::string input;
	std::getline(std::cin, input);
	std::cout << checkForParentheses(removeSpaces(input), parentheses) << std::endl;

	/*
	Window* window = new Window();

	bool running = true;
	while (running) {
		if (!(window->ProcessMessage())) {
			std::cout << "Running Window\n";
			running = false;
		}

		//Render

		Sleep(10);
	}
	*/

	return 0;
}

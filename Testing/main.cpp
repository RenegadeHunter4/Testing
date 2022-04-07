#include "main.h"

const int size = 32;

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

void checkForParentheses(std::string input, int (&parenthesesRank)[size], int(&parenthesesLocation)[size]) {
	//Init Variables
	int arrayI = 0;
	int rank = 0;

	//Loops Through Screen
	for (int i = 0; i < input.length(); i++) {
		if ((input[i] == '(') || (input[i] == '[')) { //checks for open parenthesies
			if (arrayI != 0) { rank++; }              //idk why this works but it does
			parenthesesRank[arrayI] = rank;           //sets how deep the parenethesies are
			parenthesesLocation[arrayI] = i;          //sets where the parenthesies are
			arrayI++;
		}
		else if ((input[i] == ')') || (input[i] == ']')) { //Checks for Closed Parenthesies
			parenthesesRank[arrayI] = rank;				   //sets how deep the parenethesies a
			parenthesesLocation[arrayI] = i;			   //sets where the parenthesies are
			arrayI++;
			rank--;
		}
	}

	//ForTesting-------------------------------------Start

	//Prints parenthesesRank Array
	for (int i = 0; i < arrayI; i++) {
		std::cout << parenthesesRank[i] << " ";
	}
	std::cout << std::endl;

	//Prints parenthesesLocation Array
	for (int i = 0; i < arrayI; i++) {
		std::cout << parenthesesLocation[i] << " ";
	}
	std::cout << std::endl;

	//ForTesting-------------------------------------End
}

void checkForNumbers(std::string input, double(&numberList)[size], int(&numberLocation)[size]) {
	//Init Variables
	std::string num = "";
	int arrayI = 0;

	//Loops over string
	for (int i = 0; i < input.length(); i++) {
		if (isdigit(input[i]) || (input[i] == '.')) {

			//Records Location of start of number
			if (num.empty()) {
				numberLocation[arrayI] = i; 
			}

			//Records Full number into var num.
			num = num + input[i]; 
		}
		else {
			//Puts number into numberList Array
			if (!num.empty()) {
				numberList[arrayI] = stod(num); 
				num = "";
				arrayI++;
			}
		}
	}

	//Incase string ends on a number
	if (!num.empty()) {
		numberList[arrayI] = stod(num);
	}

	//ForTesting-------------------------------------Start

	//Prints numberList Array
	for (int i = 0; i <= arrayI; i++) {
		std::cout << numberList[i] << " ";
	}
	std::cout << std::endl;

	//Prints numberLocation Array
	for (int i = 0; i <= arrayI; i++) {
		std::cout << numberLocation[i] << " ";
	}
	std::cout << std::endl;

	//ForTesting-------------------------------------End
}

bool isOperator(const char op) {
	if ((op == '+') || (op == '-') || (op == '*') || (op == '/') || (op == '^')) {
		return true;
	}
	else {
		return false;
	}
}

void checkForOperators(std::string input, int(&operatorLocation)[size], char (&operatorList)[size]) {
	//Init Variables
	int arrayI = 0;

	//Loops over string
	for (int i = 0; i < input.length(); i++) {
		if (isOperator(input[i])) {
			operatorLocation[arrayI] = i;
			operatorList[arrayI] = input[i];
			arrayI++;
		}
	}

	arrayI--;

	//ForTesting-------------------------------------Start

	//Prints numberList Array
	for (int i = 0; i <= arrayI; i++) {
		std::cout << operatorList[i] << " ";
	}
	std::cout << std::endl;

	//Prints numberLocation Array
	for (int i = 0; i <= arrayI; i++) {
		std::cout << operatorLocation[i] << " ";
	}
	std::cout << std::endl;

	//ForTesting-------------------------------------End
}

int main() {
	std::cout << "Creating Window\n";
	int parenthesesRank[size];
	int parenthesesLocation[size];
	double numberList[size];
	int numberLocation[size];
	int operatorLocation[size];
	char operatorList[size];

	std::string input;
	std::getline(std::cin, input);
	std::cout << removeSpaces(input) << std::endl;

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

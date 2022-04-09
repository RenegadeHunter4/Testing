#include "main.h"

void removeSpaces(std::string &input) {
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

int checkForParentheses(std::string input, int (&parenthesesRank)[size], int(&parenthesesLocation)[size]) {
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

	return arrayI;
}

int checkForNumbers(std::string input, double(&numberList)[size], int(&numberLocation)[size]) {
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
		arrayI++;
	}

	//ForTesting-------------------------------------Start

	//Prints numberList Array
	for (int i = 0; i < arrayI; i++) {
		std::cout << numberList[i] << " ";
	}
	std::cout << std::endl;

	//Prints numberLocation Array
	for (int i = 0; i < arrayI; i++) {
		std::cout << numberLocation[i] << " ";
	}
	std::cout << std::endl;

	//ForTesting-------------------------------------End

	return arrayI;
}

bool isOperator(const char op) {
	if ((op == '+') || (op == '-') || (op == '*') || (op == '/') || (op == '^')) {
		return true;
	}
	else {
		return false;
	}
}

int checkForOperators(std::string input, char(&operatorList)[size], int(&operatorLocation)[size], int(&operatorRank)[size]) {
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

	for (int i = 0; i < arrayI; i++) {
		if ((operatorList[i] == '+') || (operatorList[i] == '-')) {
			operatorRank[i] = 0;
		}
		else if ((operatorList[i] == '*') || (operatorList[i] == '/')) {
			operatorRank[i] = 1;
		}
		else {
			operatorRank[i] = 2;
		}
	}

	//ForTesting-------------------------------------Start

	//Prints numberList Array
	for (int i = 0; i < arrayI; i++) {
		std::cout << operatorList[i] << " ";
	}
	std::cout << std::endl;

	//Prints numberLocation Array
	for (int i = 0; i < arrayI; i++) {
		std::cout << operatorLocation[i] << " ";
	}
	std::cout << std::endl;

	//ForTesting-------------------------------------End

	return arrayI;
}

bool isValidEquation(std::string input) {
	for (int i = 0; i < input.length(); i++) {
		if (isOperator(input[i]) || isdigit(input[i]) || (input[i] == '.') || (input[i] == '(') || (input[i] == ')') || (input[i] == '[') || (input[i] == ']') || (input[i] == ' ')) {
			// u good
		}
		else {
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

double equationProcessing() {
	//Decalring arrays
	int parenthesesRank[size];
	int parenthesesLocation[size];
	double numberList[size];
	int numberLocation[size];
	int operatorLocation[size];
	char operatorList[size];
	int operatorRank[size];

	//User Input
	std::string input = getValidInput();

	//Initializing Stuff
	parenthesesLocation[0] = -1;
	parenthesesLocation[1] = input.length() + 1;

	//PreProcessing
	removeSpaces(input);
	int numParentheses = checkForParentheses(input, parenthesesRank, parenthesesLocation);     //Generates List of Parentheses by rank and their locations
	int numNumbers = checkForNumbers(input, numberList, numberLocation);                       //Generates List of Numbers and their locations
	int numOperators = checkForOperators(input, operatorList, operatorLocation, operatorRank); //Generates List of Operators and their locations and their rank
	

	//Processing
	while (numParentheses >= 0) {
		int range[5] = { 0, 1, 1, 1, 1 }; //[0] stores range of parentheses, [1]-[2] stores range of numbers, and [3][4] stores range of operators.
		if(numParentheses == 0) {
			parenthesesLocation[0] = -1;
			parenthesesLocation[1] = input.length() + 1;
		}

		// Finds Deepest Parentheses
		range[0] = findDeepestParenthese(numParentheses, parenthesesRank);

		// Finds Numbers within those Parentheses
		range[1] = findFirstNumIndex(numNumbers, numberLocation, parenthesesLocation, range);
		range[2] = findSecondNumIndex(numNumbers, numberLocation, parenthesesLocation, range);

		// Finds Operators within those Parentheses
		range[3] = findFirstOperatorIndex(numOperators, operatorLocation, parenthesesLocation, range);
		range[4] = findSecondOperatorIndex(numOperators, operatorLocation, parenthesesLocation, range);

		int range3 = range[3];
		int range4 = range[4];
		// Loops through operators in range
		for (int numOperatorsProcessed = 0; numOperatorsProcessed < (range4 - range3 + 1); numOperatorsProcessed++) {
			int opIndex = 0;
			int numIndex = 0;
			double num1 = 0;
			double num2 = 0;
			double result = 0;

			// Finds highest ranking operator (Accarding to Order of Operations)
			opIndex = findOperatorLocation(operatorRank, range);

			// Finds number before operator and number after operator.
			numIndex = findNumberLocations(range, numberLocation, numberList, num1, num2, operatorLocation, opIndex);

			// Does math
			result = doArithmitc(operatorList[opIndex], num1, num2);

			//Updates numberList with result
			numberList[numIndex] = result;
			for (int i = numIndex + 1; i < numNumbers; i++) {
				numberList[i] = numberList[i + 1];
				numberLocation[i] = numberLocation[i + 1];
			}
			range[2]--;
			numNumbers--;

			//Updates opList with result
			for (int i = opIndex; i < numOperators; i++) {
				operatorList[i] = operatorList[i + 1];
				operatorLocation[i] = operatorLocation[i + 1];
				operatorRank[i] = operatorRank[i + 1];
			}
			range[4]--;
			numOperators--;
		}

		
		for (int i = range[0]; i < numParentheses; i++) {
			parenthesesRank[i] = parenthesesRank[i + 2];
			parenthesesLocation[i] = parenthesesLocation[i + 2];
		}
		numParentheses -= 2;
	}

	return numberList[0];
}

int main() {
	double result = equationProcessing();
	std::cout << "Result: " << result << std::endl;

	return 0;
}

int findDeepestParenthese(int numParentheses, int parenthesesRank[size]) {
	int index = 0;
	int max = 0;
	for (int i = 0; i < numParentheses; i++) {
		if (parenthesesRank[i] > max) {
			max = parenthesesRank[i];
			index = i;
		}
	}
	return index;
}

int findFirstNumIndex(int numNumbers, int numberLocation[size], int parenthesesLocation[size], int rank[5]) {
	bool flag = false;
	int index1 = 0;

	for (int i = 0; i < numNumbers; i++) {
		if ((numberLocation[i] > parenthesesLocation[rank[0]]) && (numberLocation[i] < parenthesesLocation[rank[0] + 1])) {
			if (!flag) {
				index1 = i;
				flag = true;
			}
		}
	}

	return index1;
}

int findSecondNumIndex(int numNumbers, int numberLocation[size], int parenthesesLocation[size], int rank[5]) {
	bool flag = false;
	int index2 = 0;

	for (int i = 0; i < numNumbers; i++) {
		if ((numberLocation[i] > parenthesesLocation[rank[0]]) && (numberLocation[i] < parenthesesLocation[rank[0] + 1])) {
			if (!flag) {
				index2 = i;
				flag = true;
			}
			else {
				index2 = i;
			}
		}
	}

	return index2;
}

int findFirstOperatorIndex(int numOperators, int operatorLocation[size], int parenthesesLocation[size], int rank[5]) {
	bool flag = false;
	int index3 = 0;

	for (int i = 0; i < numOperators; i++) {
		if ((operatorLocation[i] > parenthesesLocation[rank[0]]) && (operatorLocation[i] < parenthesesLocation[rank[0] + 1])) {
			if (!flag) {
				index3 = i;
				flag = true;
			}
		}
	}

	return index3;
}

int findSecondOperatorIndex(int numOperators, int operatorLocation[size], int parenthesesLocation[size], int rank[5]) {
	bool flag = false;
	int index4 = 0;

	for (int i = 0; i < numOperators; i++) {
		if ((operatorLocation[i] > parenthesesLocation[rank[0]]) && (operatorLocation[i] < parenthesesLocation[rank[0] + 1])) {
			if (!flag) {
				index4 = i;
				flag = true;
			}
			else {
				index4 = i;
			}
		}
	}

	return index4;
}

int findOperatorLocation(int operatorRank[size], int range[5]) {
	int opIndex = range[3];
	for (int i = range[3]; i < range[4] + 1; i++) {
		int max = 0;
		if (operatorRank[i] > max) {
			max = operatorRank[i];
			opIndex = i;
		}
	}

	return opIndex;
}

int findNumberLocations(int range[5], int numberLocation[size], double numberList[size], double& num1, double& num2, int operatorLocation[size], int opIndex) {
	int numIndex = 0;
	bool flag = false;

	for (int i = range[1]; i < range[2] + 1; i++) {
		if (numberLocation[i] < operatorLocation[opIndex]) {
			num1 = numberList[i];
			numIndex = i;
		}
		else if (!flag) {
			num2 = numberList[i];
			flag = true;
		}
	}

	return numIndex;
}

double doArithmitc(char op, double num1, double num2) {
	switch (op) {
	case '+':
		return num1 + num2;
		break;
	case '-':
		return num1 - num2;
		break;
	case '*':
		return num1 * num2;
		break;
	case '/':
		return num1 / num2;
		break;
	case '^':
		return pow(num1, num2);
		break;
	default:
		std::cout << "How did that happen" << std::endl;
		return -1;
		break;
	}
}

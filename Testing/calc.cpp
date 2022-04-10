#include "calc.h"

calc::calc(std::string input): input(input) {
	//Init Variables
	int parenthesesI = 0;
	int numI = 0;
	int opI = 0;
	int rank = 0;
	std::string num = "";

	//Loops Through String, intitalizes vectors
	for (int i = 0; i < input.length(); i++) {

		//Sets parentheseRank and Location for open parentheses
		if ((input[i] == '(') || (input[i] == '[')) {
			if (parenthesesI != 0) { rank++; }
			parenthesesRank.push_back(rank);
			parenthesesLocation.push_back(i);
			parenthesesI++;
		}

		//Sets parentheseRank and Location for closed parentheses
		else if ((input[i] == ')') || (input[i] == ']')) {
			parenthesesRank.push_back(rank);
			parenthesesLocation.push_back(i);
			parenthesesI++;
			rank--;
		}

		//Sets numLocation for each number
		else if (isdigit(input[i]) || (input[i] == '.')) {
			//Records Location of start of number
			if (num.empty()) {
				numberLocation.push_back(i);
			}
			//Records Full number into var num.
			num = num + input[i];
		}

		//Sets operatorLocation, operatorType, and operatorRank for each Operator in string
		else if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') || (input[i] == '/') || (input[i] == '^')) {
			operatorLocation.push_back(i);
			operatorList.push_back(input[i]);
			if ((input[i] == '+') || (input[i] == '-')) {
				operatorRank.push_back(0);
			}
			else if ((input[i] == '*') || (input[i] == '/')) {
				operatorRank.push_back(1);
			}
			else {
				operatorRank.push_back(2);
			}
			opI++;
		}
		
		//Records number into numberList once number ends
		if (!(isdigit(input[i]) || (input[i] == '.')) && !num.empty()) {
			numberList.push_back(stod(num));
			num = "";
			numI++;
		}
	} 

	//Incase string ends on a number
	if (!num.empty()) {
		numberList.push_back(stod(num));
		numI++;
	}

	numNumbers = numI;
	numOperators = opI;
	numParentheses = parenthesesI;
}

int calc::findAnswer() {
	while (numParentheses >= 0) {
		int range[5] = { 0, 1, 1, 1, 1 }; //[0] stores range of parentheses, [1]-[2] stores range of numbers, and [3][4] stores range of operators.
		bool flag = false; //For Range Finding
		int max = 0;       

		//To properly set range when no parentheses are left
		if (numParentheses == 0) {
			parenthesesLocation[0] = -1;
			parenthesesLocation[1] = input.length() + 1;
		}

		// Finds Deepest Parentheses
		for (int i = 0; i < numParentheses; i++) {
			if (parenthesesRank[i] > max) {
				max = parenthesesRank[i];
				range[0] = i;
			}
		}

		// Finds Numbers within those Parentheses
		for (int i = 0; i < numNumbers; i++) {
			if ((numberLocation[i] > parenthesesLocation[range[0]]) && (numberLocation[i] < parenthesesLocation[range[0] + 1])) {
				if (!flag) {
					range[1] = i;
					range[2] = i;
					flag = true;
				}
				else {
					range[2] = i;
				}
			}
		}

		flag = false; //reuse flag
		// Finds Operators within those Parentheses
		for (int i = 0; i < numOperators; i++) {
			if ((operatorLocation[i] > parenthesesLocation[range[0]]) && (operatorLocation[i] < parenthesesLocation[range[0] + 1])) {
				if (!flag) {
					range[3] = i;
					range[4] = i;
					flag = true;
				}
				else {
					range[4] = i;
				}
			}
		}

		int range3 = range[3];
		int range4 = range[4];
		// Loops through operators in range
		for (int numOperatorsProcessed = 0; numOperatorsProcessed < (range4 - range3 + 1); numOperatorsProcessed++) {
			int opIndex = range[3];
			int numIndex = 0;
			double num1 = 0;
			double num2 = 0;
			double result = 0;

			max = 0; // reuse max
			// Finds highest ranking operator (Accarding to Order of Operations)
			for (int i = range[3]; i < range[4] + 1; i++) {
				if (operatorRank[i] > max) {
					max = operatorRank[i];
					opIndex = i;
				}
			}

			flag = false; //reuse flag
			// Finds number before operator and number after operator.
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

			// Does math
			switch (operatorList[opIndex]) {
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num1 - num2;
				break;
			case '*':
				result = num1 * num2;
				break;
			case '/':
				result = num1 / num2;
				break;
			case '^':
				result = pow(num1, num2);
				break;
			default:
				std::cout << "How did that happen" << std::endl;
				return -1;
				break;
			}

			//Updates numberList with result
			numberList[numIndex] = result;
			for (int i = numIndex + 1; i < numNumbers - 1; i++) {
				numberList[i] = numberList[i + 1];
				numberLocation[i] = numberLocation[i + 1];
			}
			range[2]--;
			numNumbers--;

			//Updates opList with result
			for (int i = opIndex; i < numOperators - 1; i++) {
				operatorList[i] = operatorList[i + 1];
				operatorLocation[i] = operatorLocation[i + 1];
				operatorRank[i] = operatorRank[i + 1];
			}
			range[4]--;
			numOperators--;
		}


		for (int i = range[0]; i < numParentheses - 2; i++) {
			parenthesesRank[i] = parenthesesRank[i + 2];
			parenthesesLocation[i] = parenthesesLocation[i + 2];
		}
		numParentheses -= 2;
	}

	return numberList[0];
}

std::vector<int> calc::getParenthesesRank()
{
	return parenthesesRank;
}

std::vector<int> calc::getParenthesesLocation()
{
	return parenthesesLocation;
}

std::vector<double> calc::getNumberList()
{
	return numberList;
}

std::vector<int> calc::getNumberLocation()
{
	return numberLocation;
}

std::vector<int> calc::getOperatorLocation()
{
	return operatorLocation;
}

std::vector<char> calc::getOperatorList()
{
	return operatorList;
}

std::vector<int> calc::getOperatorRank()
{
	return operatorRank;
}

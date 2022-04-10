#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class calc {
//Public Functions
public:
	calc(std::string input);
	int findAnswer();

	std::vector<int> getParenthesesRank();
	std::vector<int> getParenthesesLocation();
	std::vector<double> getNumberList();
	std::vector<int> getNumberLocation();
	std::vector<int> getOperatorLocation();
	std::vector<char> getOperatorList();
	std::vector<int> getOperatorRank();
//Private Functions
private:

//Private Variables
private: 
	std::string input;

	std::vector<int> parenthesesRank;
	std::vector<int> parenthesesLocation;
	std::vector<double> numberList;
	std::vector<int> numberLocation;
	std::vector<int> operatorLocation;
	std::vector<char> operatorList;
	std::vector<int> operatorRank;

	int numParentheses;
	int numNumbers;
	int numOperators;
};
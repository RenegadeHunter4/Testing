#pragma once
#include "window.h"
#include <iostream>
#include <string>
#include <algorithm>

const int size = 32;

//Does Stuff
int main();
std::string getValidInput();
double equationProcessing();

//Modifies Stuff For Other Stuff
void removeSpaces(std::string& input);
int checkForParentheses(std::string input, int(&parenthesesRank)[size], int(&parenthesesLocation)[size]);
int checkForNumbers(std::string input, double(&numberList)[size], int(&numberLocation)[size]);
int checkForOperators(std::string input, char(&operatorList)[size], int(&operatorLocation)[size], int(&operatorRank)[size]);

//Checks Stuff
bool isOperator(const char op);
bool isValidEquation(std::string input);

//I haven't done this Stuff
int findDeepestParenthese(int numParentheses, int parenthesesRank[size]);
int findFirstNumIndex(int numNumbers, int numberLocation[size], int parenthesesLocation[size], int rank[5]);
int findSecondNumIndex(int numNumbers, int numberLocation[size], int parenthesesLocation[size], int rank[5]);
int findFirstOperatorIndex(int numOperators, int operatorLocation[size], int parenthesesLocation[size], int rank[5]);
int findSecondOperatorIndex(int numOperators, int operatorLocation[size], int parenthesesLocation[size], int rank[5]);

int findOperatorLocation(int operatorRank[size], int range[5]);
int findNumberLocations(int range[5], int numberLocation[size], double numberList[size], double& num1, double& num2, int operatorLocation[size], int opIndex);
double doArithmitc(char op, double num1, double num2);

//findFirst/secondNumIndex :: return index1 - 1;
//findfirst/secondnumIndex :: i < numNumbers + 1;
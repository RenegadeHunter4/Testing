#pragma once
#include "calc.h"
#include <iostream>
#include <string>
#include <algorithm>

const int size = 32;

//Does Stuff
int main();
std::string getValidInput();
void printVector(std::vector<int> vec);
void printVector(std::vector<double> vec);
void printVector(std::vector<char> vec);

//Modifies Stuff For Other Stuff
void removeSpaces(std::string& input);

//Checks Stuff
bool isValidEquation(std::string input);
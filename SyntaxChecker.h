/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>
#include "GenStack.h"

using namespace std;

class SyntaxChecker
{
public:
	SyntaxChecker(string fileName);
	~SyntaxChecker();

	//functions
	void ReadFile(string fileName);
	string GetString();


	//member variables
	GenStack<char> symbolStack;
	GenStack<int> lineNumStack;

};
/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/

#include <iostream>
using namespace std;

class Delimiter
{
public:
	Delimiter(int lineNum, char symbol);
	//Delimiter();
	string GetString();

	char symbol;
	int lineNum;
	bool hasPair;
};
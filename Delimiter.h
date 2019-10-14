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
private:
	void DeterminePairType();

public:
	Delimiter(int lineNum, char symbol);
	//Delimiter();
	string GetString();
	
	char closeSymbol = '\0';
	char symbol;
	int lineNum;
	bool hasPair;
};
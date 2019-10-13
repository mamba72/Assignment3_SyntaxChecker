/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/

#include "Delimiter.h"
#include <string>
using namespace std;
Delimiter::Delimiter(int lineNum, char symbol)
{
	this->lineNum = lineNum;
	this->symbol = symbol;
	hasPair = false;
}

/*
Delimiter::Delimiter()
{
	lineNum = -1;
	symbol = '\0';
	hasPair = false;
}*/

string Delimiter::GetString()
{
	string outputString = "Line number: " + to_string(lineNum) + "\tSymbol: " + symbol + "\n";
	return outputString;
}
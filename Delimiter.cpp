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
	DeterminePairType();
}

string Delimiter::GetString()
{
	string outputString = "Line number: " + to_string(lineNum) + "\tSymbol: " + symbol + "\tHas Pair: "+ to_string(hasPair) + "\n";
	return outputString;
}

//this will return the closing of that symbol
void Delimiter::DeterminePairType()
{
	if (symbol == '(')
		closeSymbol = ')';
	else if (symbol == '{')
		closeSymbol = '}';
	else if (symbol == '[')
		closeSymbol = ']';
}
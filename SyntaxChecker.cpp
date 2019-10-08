/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/

#include "SyntaxChecker.h"
#include <fstream>

//constructor
SyntaxChecker::SyntaxChecker(string fileName)
{
	//intialize the stacks
	symbolStack = GenStack<char>();
	lineNumStack = GenStack<int>();

	ReadFile(fileName);


}

//destruct
SyntaxChecker::~SyntaxChecker()
{
	symbolStack.~GenStack();
	lineNumStack.~GenStack();
}

//read the file and enter all the symbols into the stacks
void SyntaxChecker::ReadFile(string fileName)
{
	ifstream inputFile;
	inputFile.open(fileName);
	//make sure its open
	if (!inputFile)
		throw runtime_error("Could not open file named " + fileName + ".");

	//now move through the file 
	string line = "";
	int lineCounter = 0;
	//iterate through every line
	while (getline(inputFile, line))
	{
		//iterate through the line gathering what symbol and the line number
		for (int i = 0; i < line.length(); ++i)
		{
			//record the symbol and its line number
			if (line[i] == '(' || line[i] == ')')
			{
				symbolStack.push(line[i]);
				lineNumStack.push(lineCounter);
			}
			else if (line[i] == '{' || line[i] == '}')
			{
				symbolStack.push(line[i]);
				lineNumStack.push(lineCounter);
			}
			else if (line[i] == '[' || line[i] == ']')
			{
				symbolStack.push(line[i]);
				lineNumStack.push(lineCounter);
			}		
		}
		lineCounter++;
	}
}

string SyntaxChecker::GetString()
{
	return string();
}

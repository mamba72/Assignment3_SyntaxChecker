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
	symbolStack = new  GenStack<char>();
	lineNumStack = new GenStack<int>();
	lineCount = 0;
	this->fileName = fileName;
	lineStack = new GenStack<string>();
	ReadFile(fileName);//need to change this
	GetSymbols();

}

//destruct
SyntaxChecker::~SyntaxChecker()
{
	symbolStack->~GenStack();
	lineNumStack->~GenStack();
	lineStack->~GenStack();
}

//read the file and put each line into the stack called lineStack
void SyntaxChecker::ReadFile(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		throw runtime_error("The file could not be opened.");
	}

	string line = "";
	//counts the line number and puts each line into a stack
	while (getline(file, line))
	{
		cout << "Line number: " << lineCount << "| Line: " << line << endl;
		lineCount++;
		lineStack->push(line);
	}
}

//now go through the line array gathering every symbol and line number
//into the symbolStack and lineNumStacks
void SyntaxChecker::GetSymbols()
{
	cout << "Total line count: " << lineCount << endl;
	string line = "";
	//iterate through every line
	for (int i = 1; i <= lineCount; ++i)
	{
		line = lineStack->pop();
		
		//cout << "Line number: " << i << " | line: " << line << endl;

		//iterate through each character
		for (int num = 0; num < line.length(); ++num)
		{
			if (line[num] == '(' || line[num] == ')' || line[num] == '{' || line[num] == '}' || line[num] == '[' || line[num] == ']')
			{
				symbolStack->push(line[num]);
				lineNumStack->push(i);
			}
		}
	}
}


string SyntaxChecker::GetString()
{
	return string();
}

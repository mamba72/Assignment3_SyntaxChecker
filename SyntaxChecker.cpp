/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/

#include "SyntaxChecker.h"
#include <fstream>
#include <string>

//constructor
SyntaxChecker::SyntaxChecker(string fileName)
{
	//intialize the stacks
	delimiterStack = new GenStack<Delimiter*>();
	lineCount = 0;
	this->fileName = fileName;
	lineStack = new GenStack<string>();
	ReadFile(fileName);
	GetSymbols();
}

//destruct
SyntaxChecker::~SyntaxChecker()
{
	delimiterStack->~GenStack();
	lineStack->~GenStack();
}

//read the file and put each line into the stack called lineStack
void SyntaxChecker::ReadFile(string fileName)
{
	ifstream file;
	file.open(fileName);

	if (!file.is_open())
	{
		throw CouldNotOpenFileException("The file could not be opened.");
	}

	string line = "";
	//counts the line number and puts each line into a stack
	while (getline(file, line))
	{
		lineCount++;
		lineStack->push(line);
	}
}

//now go through the line array gathering every symbol and line number
//into the symbolStack and lineNumStacks
void SyntaxChecker::GetSymbols()
{
	//cout << "Total line count: " << lineCount << endl;
	string line = "";
	//iterate through every line
	//go backwards through the line count because the first line popped is the last one read.
	for (int i = lineCount; i > 0; --i)
	{
		line = lineStack->pop();
		
		bool isNotInString = true;
		//iterate through each character
		for (int num = line.length() -1; num >= 0; --num)
		{
			//skip delimiters in strings
			if (line[num] == '\"' || line[num] == '\'')
			{
				if (isNotInString == false)
					isNotInString = true;
				else
					isNotInString = false;
			}
			if (isNotInString == false)
				continue;
			//end skipping delimiters in strings

			//add the delimiters to the stack
			if (line[num] == '(')
			{
				Delimiter* d = new Delimiter(i, '(');
				delimiterStack->push(d);
			}
			else if (line[num] == ')')
			{
				Delimiter* d = new Delimiter(i, ')');
				delimiterStack->push(d);
			}
			else if (line[num] == '{')
			{
				Delimiter* d = new Delimiter(i, '{');
				delimiterStack->push(d);
			}
			else if (line[num] == '}')
			{
				Delimiter* d = new Delimiter(i, '}');
				delimiterStack->push(d);
			}
			else if (line[num] == '[')
			{
				Delimiter* d = new Delimiter(i, '[');
				delimiterStack->push(d);
			}
			else if (line[num] == ']')
			{
				Delimiter* d = new Delimiter(i, ']');
				delimiterStack->push(d);
			}
		}
	}
}

//this function will return whether there is a problem, the string about it, and the line thats the issue
SyntaxChecker::ProblemReport SyntaxChecker::FindPairs()
{
	ProblemReport report = CreateReport(false, "", -1);

	//go through the stack checking if you find any close delimiters before an open
	while (delimiterStack->isEmpty() == false)
	{
		int openCounter = 0;

		Delimiter* curDelim = delimiterStack->pop();

		if (curDelim->hasPair == false)
		{
			//if it is unpaired and a close, then it shouldnt be there
			if (curDelim->symbol == ')' || curDelim->symbol == '}' || curDelim->symbol == ']')
			{
				report.isProblem = true;
				report.problemDescription = ("Unexpected " + string(1, curDelim->symbol) + " on line " + to_string(curDelim->lineNum));
				report.lineNum = curDelim->lineNum;
				return report;
			}
			else
			{
				//iterate through the rest of the stack
				for (int i = delimiterStack->top; i >= 0; --i)
				{
					//if you find multiple opens, then skip that number of closes
					if (curDelim->symbol == delimiterStack->myArray[i]->symbol)
					{
						openCounter++;
						continue;
					}
					//if you see a close and have already seen another open, then skip the close
					else if (curDelim->closeSymbol == delimiterStack->myArray[i]->symbol && openCounter > 0)
					{
						openCounter--;
						continue;
					}
					//if the counter is greater than zero, skip
					if (openCounter > 0)
					{
						continue;
					}
					//if this delimiter is the closing symbol of the current delimiter, then it is a pair
					if (delimiterStack->myArray[i]->symbol == curDelim->closeSymbol)
					{
						curDelim->hasPair = true;
						delimiterStack->myArray[i]->hasPair = true;
						break;
					}
				}
			}
		}
		//by now, if the current delimiter doesnt have a pair, it is missing a close
		//this should check to see if there is an open delim without a pairing close delim
		if (curDelim->hasPair == false)
		{
			report.isProblem = true;
			report.problemDescription = "Unpaired " + string(1, curDelim->symbol) + " on line " + to_string(curDelim->lineNum);
			report.lineNum = curDelim->lineNum;
			return report;
		}
	}
	return report;
}

void SyntaxChecker::ReadyForNextFile()
{
	//lineStack->~GenStack();
	//delimiterStack->~GenStack();
	//these create problems
}
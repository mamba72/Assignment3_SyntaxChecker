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
	//symbolStack = new  GenStack<char>();
	//lineNumStack = new GenStack<int>();
	delimiterStack = new GenStack<Delimiter*>();
	lineCount = 0;
	this->fileName = fileName;
	lineStack = new GenStack<string>();
	ReadFile(fileName);//need to change this
	GetSymbols();

}

//destruct
SyntaxChecker::~SyntaxChecker()
{
	//symbolStack->~GenStack();
	//lineNumStack->~GenStack();
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
		throw runtime_error("The file could not be opened.");
	}

	string line = "";
	//counts the line number and puts each line into a stack
	while (getline(file, line))
	{
		//cout << "Line number: " << lineCount << "| Line: " << line << endl;
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
	for (int i = lineCount; i > 0; --i)
	{
		line = lineStack->pop();
		
		bool quotePair = true;
		//iterate through each character
		for (int num = line.length() -1; num >= 0; --num)
		{
			//skip delimiters in strings
			if (line[num] == '\"' || line[num] == '\'')
			{
				if (quotePair == false)
					quotePair = true;
				else
					quotePair = false;
			}
			if (quotePair == false)
				continue;
			//end skipping delimiters in strings

			//add the delimiters to the stack
			if (line[num] == '(')
			{
				//symbolStack->push(line[num]);
				//lineNumStack->push(i);
				Delimiter* d = new Delimiter(i, '(');
				delimiterStack->push(d);
				CountPairs(d);
			}
			else if (line[num] == ')')
			{
				Delimiter* d = new Delimiter(i, ')');
				delimiterStack->push(d);
				CountPairs(d);
			}
			else if (line[num] == '{')
			{
				Delimiter* d = new Delimiter(i, '{');
				delimiterStack->push(d);
				CountPairs(d);
			}
			else if (line[num] == '}')
			{
				Delimiter* d = new Delimiter(i, '}');
				delimiterStack->push(d);
				CountPairs(d);
			}
			else if (line[num] == '[')
			{
				Delimiter* d = new Delimiter(i, '[');
				delimiterStack->push(d);
				CountPairs(d);
			}
			else if (line[num] == ']')
			{
				Delimiter* d = new Delimiter(i, ']');
				delimiterStack->push(d);
				CountPairs(d);
			}
		}
	}
}

//this function will be doing the heavy lifting
void SyntaxChecker::CountPairs(Delimiter* &d)
{
	if (d->symbol == '(')
		numOpenParens++;
	else if (d->symbol == ')')
		numCloseParens++;
	else if (d->symbol == '{')
		numOpenCurlyBrackets++;
	else if (d->symbol == '}')
		numCloseCurlyBrackets++;
	else if (d->symbol == '[')
		numOpenBrackets++;
	else if (d->symbol == ']')
		numCloseBrackets++;
	else
		throw runtime_error("The symbol in the stack is not valid. The symbol is " + d->symbol);
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
		//cout << "Before " << curDelim->GetString();
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
					//if this delimiter is the closing symbol of the current delimiter, then it is a pair
					if (curDelim->symbol == delimiterStack->myArray[i]->symbol)
					{
						openCounter++;
						continue;
					}
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

					if (delimiterStack->myArray[i]->symbol == curDelim->closeSymbol)
					{
						curDelim->hasPair = true;
						delimiterStack->myArray[i]->hasPair = true;
						break;
					}
				}
			}
		}
		//cout << "After " << curDelim->GetString();
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
	numOpenParens = 0;
	numCloseParens = 0;
	numOpenBrackets = 0;
	numCloseBrackets = 0;
	numOpenCurlyBrackets = 0;
	numCloseCurlyBrackets = 0;

	//lineStack->~GenStack();
	//delimiterStack->~GenStack();
}
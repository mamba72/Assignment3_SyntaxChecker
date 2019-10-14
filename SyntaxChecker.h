/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>
#include "GenStack.h"
#include "Delimiter.h"
#include "CustomExceptions.h"
using namespace std;

class SyntaxChecker
{
public:
	//this is used to contain the information about the syntax problem
	struct ProblemReport
	{
		bool isProblem;
		string problemDescription = "";
		int lineNum = -1;

		string toString()
		{
			if (isProblem)
				return problemDescription;
			else
				return "There were no problems.";
		}
	};

	ProblemReport CreateReport(bool problem, string description, int line)
	{
		return { problem, description, line };
	}


	SyntaxChecker(string fileName);
	~SyntaxChecker();

	//functions
	void ReadFile(string fileName);
	void GetSymbols();
	ProblemReport FindPairs();
	void ReadyForNextFile();


	//member variables
	GenStack<Delimiter*>* delimiterStack;

	//file member vars
	GenStack<string>* lineStack;
	int lineCount;
	string fileName;

	

};

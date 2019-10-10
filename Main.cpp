/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>
//#include "GenStack.h"
#include "SyntaxChecker.h"

using namespace std;

int main(int argc, char** argv)
{

	//SyntaxChecker sc("TestCPP");
	SyntaxChecker sc(argv[1]);

	cout << endl << endl;

	//cout << "SC Peak: " << sc.lineStack->peek() << endl;
	cout << "Num elements of symbolStack: " << sc.symbolStack->top << endl;

	//cout << "Hello\n";

}

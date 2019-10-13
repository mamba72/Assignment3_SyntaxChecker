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
#include <string>

using namespace std;

int main(int argc, char** argv)
{
	if (argc != 2)
	{
		cout << "You did not enter a file in the command line arguments.\n";
		return 1;
	}


	string fileName = argv[1];
	char stay = 'y';

	while (stay == 'y')
	{
		//SyntaxChecker sc("TestCPP");
		SyntaxChecker sc(fileName);

		cout << endl << endl;

		//cout << "SC Peak: " << sc.lineStack->peek() << endl;
		cout << "Num elements of symbolStack: " << sc.delimiterStack->top << endl;

		cout << "Last delimiter: " << sc.delimiterStack->peek()->GetString() << endl;

		for (int i = 0; i < sc.delimiterStack->top + 1; ++i)
		{
			cout << "Delimiter Number: " << i << "\t" << sc.delimiterStack->myArray[i]->GetString();
		}

		cout << "NumOpenParens: " << to_string(sc.numOpenParens) << endl;
		cout << "NumCloseParens: " << to_string(sc.numCloseParens) << endl;
		cout << "NumOpenBrackets: " << to_string(sc.numOpenBrackets) << endl;
		cout << "NumCloseBrackets: " << to_string(sc.numCloseBrackets) << endl;
		cout << "NumOpenCurlyBrackets: " << to_string(sc.numOpenCurlyBrackets) << endl;
		cout << "NumCloseCurlyBrackets: " << to_string(sc.numCloseCurlyBrackets) << endl;


		

		//ask the user if they want to stay
		cout << "\n\nWould you like to do another file? (y/n)\n";
		cin >> stay;

		//only do this when you're sure you're done with the file
		sc.ReadyForNextFile();

		if (stay == 'y')
		{
			
			cout << "Enter the file name of your next file:\n";
			cin >> fileName;
		}

	}

	cout << "Goodbye :)\n";


	


}

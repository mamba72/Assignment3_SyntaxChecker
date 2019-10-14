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
		SyntaxChecker* sc;

		try 
		{
			sc = new SyntaxChecker(fileName);
		}
		catch (CouldNotOpenFileException e)
		{
			cout << "Your file named " + fileName + " couldn't be opened." << endl;
			cout << "Your exception output:\n" << e.what() << endl;
			return 1;
		}

		int delimiterNumberCounter = 0;
		for (int i = sc->delimiterStack->top; i >= 0; --i)
		{
			//cout << "Delimiter Number: " << delimiterNumberCounter << "\t" << sc.delimiterStack->myArray[i]->GetString();
			delimiterNumberCounter++;
		}
		
		SyntaxChecker::ProblemReport report = sc->FindPairs();

		cout << report.toString() << endl;

		//ask the user if they want to stay
		cout << "\nWould you like to do another file? (y/n)\n";
		cin >> stay;

		//only do this when you're sure you're done with the file
		sc->ReadyForNextFile();

		if (stay == 'y')
		{
			
			cout << "Enter the file name of your next file:\n";
			cin >> fileName;
		}

	}

	cout << "Goodbye :)\n";


	


}
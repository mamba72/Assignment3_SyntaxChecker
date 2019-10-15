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
	if (argc > 2)
	{
		cout << "There can only be two command line arguments: the inital command and the file name.\n";
		return 1;
	}
	else if (argc != 2)
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
			//create the object. this will read the file and gather delimiters automatically
			sc = new SyntaxChecker(fileName);
		}
		catch (CouldNotOpenFileException e)
		{
			cout << "Your file named " + fileName + " couldn't be opened." << endl;
			cout << "Your exception output:\n" << e.what() << endl;
			return 1;
		}
		catch (FileIsEmptyException e)
		{
			cout << "The file you entered by the name of " + fileName + " is empty.\nTry a different file that has content.\n";
			cout << "Your Exception report:\n\t" << e.what() << endl;
			return 1;
		}
		
		//grab the problem report from the function
		SyntaxChecker::ProblemReport report = sc->FindPairs();

		cout << report.toString() << endl;

		//ask the user if they want to stay
		cout << "\nWould you like to do another file? (y/n)\n";
		cin >> stay;

		if (stay == 'y')
		{
			
			cout << "Enter the file name of your next file:\n";
			cin >> fileName;
		}

	}

	cout << "Goodbye :)\n";

	return 0;
}
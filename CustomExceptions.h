/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>
#include <exception>

using namespace std;

//exception to tell whether the file could be opened
class CouldNotOpenFileException : public std::exception
{
	const char* msg;
public:
	CouldNotOpenFileException(const char* msg) : std::exception()
	{
		this->msg = msg;
	}

	const char* what() const throw ()
	{
		return msg;
	}
};

//exception to tell whether the file has any content
class FileIsEmptyException : public std::exception
{
	const char* msg;
public:
	FileIsEmptyException(const char* msg) : std::exception()
	{
		this->msg = msg;
	}

	const char* what() const throw ()
	{
		return msg;
	}
};
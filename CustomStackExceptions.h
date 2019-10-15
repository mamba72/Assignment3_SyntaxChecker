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

//exception to tell whether the stack is empty
class StackEmptyException : public std::exception
{
	const char* msg;
public:
	StackEmptyException(const char* msg) : std::exception()
	{
		this->msg = msg;
	}

	const char* what() const throw ()
	{
		return msg;
	}
};

//exception to tell when the input max size is not allowed. Usually when maxSize < 1
class InvalidMaxSizeException : public std::exception
{
	const char* msg;
public:
	InvalidMaxSizeException(const char* msg) : std::exception()
	{
		this->msg = msg;
	}

	const char* what() const throw ()
	{
		return msg;
	}
};
/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>

template <typename T>
class GenStack 
{
public:
	GenStack();
	GenStack(int maxSize);
	~GenStack();

	void push(T d);
	T pop();
	T peek();//aka top()
	

	bool isFull();
	bool isEmpty();

	int size;
	int top;//the var that maintains the position of the top object

	T* myArray;//pointer to a char. Allows dynamic memory allocation

private:
	void resizeArray();

};
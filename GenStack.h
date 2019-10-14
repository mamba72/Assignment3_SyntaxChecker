/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>
#include "CustomExceptions.h"
using namespace std;

template <class T> 
class GenStack 
{
public:
	//constructor
	GenStack()
	{
		myArray = new T[50];
		size = 50;
		top = -1;
	}
	
	//overloaded constructor
	GenStack(int maxSize)
	{
		if (maxSize < 1)
			throw runtime_error("The max size can't be less than 1.");

		myArray = new T[maxSize];
		size = maxSize;
		top = -1;
	}
	~GenStack()
	{
		//make sure you delete the array
		delete[] myArray;
	}

	void push(T d)
	{
		//need to check to make sure that you dont exceed the length of the array
		//i need to implement that
		if (isFull() == false)
		{
			//add the new element to the array
			myArray[++top] = d;
		}
		else
		{
			cout << "Resizing array. Size = " << size << " Top = " << top << endl;
			resizeArray();

			//push(d);
			myArray[++top] = d;
		}
	}

	T pop()
	{
		//make sure you implement error checking
		if (isEmpty())
		{
			throw StackEmptyException("Stack is empty. Can't pop.");
		}
		return myArray[top--];
	}

	T peek()//aka top()
	{
		//check to see if its empty first
		if (isEmpty())
		{
			throw StackEmptyException("Stack is empty. Can't peek.");
		}
		return myArray[top];
	}
	

	bool isFull()
	{
		return (top == size - 1);
	}

	bool isEmpty()
	{
		return (top == -1);
	}

	int size;
	int top;//the var that maintains the position of the top object

	T* myArray;//pointer to a char. Allows dynamic memory allocation

private:
	//a function to resize the array to twice the original's length
	void resizeArray()
	{
		T* tempArray = new T[size * 2];
		//copy everything from old array into new one.
		for (int i = 0; i < size; ++i)
		{
			tempArray[i] = myArray[i];
		}

		//delete[] myArray;//creates memory errors
		myArray = tempArray;
		//delete[] tempArray;
		//update the size
		this->size = this->size * 2;
	}

};



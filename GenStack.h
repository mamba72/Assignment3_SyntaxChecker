/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include <iostream>
#include "CustomStackExceptions.h"
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
			throw InvalidMaxSizeException("The max size can't be less than 1.");

		myArray = new T[maxSize];
		size = maxSize;
		top = -1;
	}
	~GenStack()
	{
		//make sure you delete the array
		delete[] myArray;
	}
	
	//places the given object into the stack
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
			resizeArray();

			//push(d);//could do recursion, but that would make it more complex and harder to debug
			myArray[++top] = d;
		}
	}

	//returns the top element of the stack and removes it
	T pop()
	{
		//make sure you implement error checking
		if (isEmpty())
		{
			throw StackEmptyException("Stack is empty. Can't pop.");
		}
		return myArray[top--];
	}

	//returns the top element of the stack (doesnt remove it)
	T peek()//aka top()
	{
		//check to see if its empty first
		if (isEmpty())
		{
			throw StackEmptyException("Stack is empty. Can't peek.");
		}
		return myArray[top];
	}
	
	//returns whether the stack is full
	bool isFull()
	{
		return (top == size - 1);
	}
	//returns whether the stack is empty
	bool isEmpty()
	{
		return (top == -1);
	}

	//the variable that maintains the length of the array (not the number of elements)
	int size;
	//the var that maintains the index of the top object
	int top;

	//pointer to an array. Allows dynamic memory allocation
	T* myArray;

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

		//update the size
		this->size = this->size * 2;
	}

};



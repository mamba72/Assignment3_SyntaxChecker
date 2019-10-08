/*
Stephen White
Student ID: 002323381
Assignment 3
Data Structures
Syntax Checker
*/
#include "GenStack.h"

using namespace std;

//the default constructor
template <typename T>
GenStack<T>::GenStack()
{
	myArray = new T[50];
	size = 50;
	top = -1;
}

//overloaded constructor
template <typename T>
GenStack<T>::GenStack(int maxSize)
{
	myArray = new T[maxSize];
	size = maxSize;
	top = -1;
}

//destructor that deletes the array
template <typename T>
GenStack<T>::~GenStack()
{
	//make sure you delete the array
	delete[] myArray;
}

template <typename T>
void GenStack<T>::push(T d)
{
	//need to check to make sure that you dont exceed the length of the array
	//i need to implement that
	if ((top + 1) < size)
	{
		//add the new element to the array
		myArray[++top] = d;
	}
}

template <typename T>
T GenStack<T>::pop()
{
	//make sure you implement error checking
	if (isEmpty())
	{
		throw runtime_error("Your stack is empty. Can't pop.");
	}
	return myArray[top--];
}

template <typename T>
T GenStack<T>::peek()
{
	//check to see if its empty first
	if (isEmpty())
	{
		throw runtime_error("Your stack is empty. Can't peek.");
	}
	return myArray[top];
}

template <typename T>
bool GenStack<T>::isFull()
{
	return (top == size - 1);
}

template <typename T>
bool GenStack<T>::isEmpty()
{
	return (top == -1);
}

//resize the array by replacing the array with an array with double the size
template<typename T>
void GenStack<T>::resizeArray()
{

}

//This is stupid! You need to give it expected use cases?
//because the compiler needs to be given examples
template class GenStack<char>;
template class GenStack<int>;
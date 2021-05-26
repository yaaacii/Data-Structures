/*
* Name: Cicelia Siu, 5005247749, Assignment 5
* Description: myStack.h for Assignment 5 ; 
* 	gives function declaration and implementation for myStack object
* Input: N/A
* Output: N/A
*/

#include <stdio.h>
#include <iostream>
using namespace std;

template <class Type>
class myStack
{
public:
	myStack();
	myStack(const myStack<Type>&);
	const myStack<Type>& operator=(const myStack<Type>&);
	~myStack();

	void push(const Type&);
	void pop();
	Type top() const;
	bool isEmpty() const;

private:
	struct node
	{
		Type item;
		node * next;
	};

	node * topOfmyStack;
};

/*
* myStack(): constructor for a new, empty myStack object
* parameters: N/A
* return value: N/A
*/
template <class Type>
myStack<Type>::myStack()
{
	topOfmyStack = nullptr;
}

/*
* myStack(const myStack<Type>& copy): copy constructor for a myStack object
* parameters: copy - is the original myStack object to be copied 
* return value: a copy of the original myStack object
*/
template <class Type>
myStack<Type>::myStack(const myStack<Type>& copy)
{
	//deep copy
	if (copy.isEmpty())
	{
		(*this).topOfMystack = nullptr;
	} 
	else
	{
		node * current = copy.topOfMyStack;
		(*this).topOfMyStack = copy.topOfMyStack;
		for (int i = 0; current->next == nullptr; current = current->next)
		{
			push(current->item);
		}
	}
}

/*
* operator=(const myStack<Type>& rhs): operator= for a myStack object
* parameters: rhs - is the myStack object to be copied 
* return value: a myStack object that is a deep copy of the rhs myStack object
*/
template<class Type>
const myStack<Type>& myStack<Type>::operator=(const myStack<Type>& rhs)
{
	//clear lhs
	do
	{
		pop();
	} while (!isEmpty());

	//deep copy
	if (rhs.isEmpty())
	{
		(*this).topOfMystack = nullptr;
	} 
	else
	{
		node * current = rhs.topOfMyStack;
		(*this).topOfMyStack = rhs.topOfMyStack;
		for (int i = 0; current->next == nullptr; current = current->next)
		{
			push(current->item);
		}
		return *this;
	}
}

/*
* ~myStack(): destructor for a myStack object
* parameters: N/A
* return value: destroyed myStack object
*/
template<class Type>
myStack<Type>::~myStack()
{
	while (!isEmpty())
	{
		pop();
	}
}

/*
* push(const Type& insert): pushes a Type (in this assignment: an int) into the top of the myStack object
* parameters: insert - is a Type (in this assignment: an int) to be pushed onto the stack
* return value: N/A
*/
template <class Type>
void myStack<Type>::push(const Type& insert)
{
	node * newNode;
	newNode = new node;
	newNode->item = insert;
	newNode->next = topOfmyStack;
	topOfmyStack = newNode;
}

/*
* pop(): pops a Type (in this assignment: an int) off the top of the myStack object
* parameters: N/A
* return value: N/A
*/
template <class Type>
void myStack<Type>::pop()
{
	if (!isEmpty())
	{
		node * deletePtr = topOfmyStack;
		topOfmyStack = topOfmyStack->next;
		delete deletePtr;
	}
}

/*
* top() const: gets the data type (in assignment : an int) at the top of the stack
* parameters: N/A
* return value: topOfmyStack->item - the data at the top of the stack
*/
template <class Type>
Type myStack<Type>::top() const
{
	return topOfmyStack->item;
}

/*
* isEmpty() const: checks if the myStack object is empty
* parameters: N/A
* return value: true if empty, false if not empty
*/
template <class Type>
bool myStack<Type>::isEmpty() const
{
	if (topOfmyStack == nullptr)
	{
		return 1; 
	} 
	else 
	{
		return 0;
	}
}

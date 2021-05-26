/*
* Name: Cicelia Siu, 5005247749, Assignment 8
* Description: priorityQ.h for Assignment  ; 
* 	gives function declaration and implementation for priorityQ class
* Input: N/A
* Output: N/A
*/

#include <string>
#include <cstdlib>
#include <iostream>
//#include "lander.h"
using namespace std;


template <class Type>
class priorityQ
{
public:
    priorityQ(int = 10);
    priorityQ(const priorityQ<Type>&);
    ~priorityQ();
    const priorityQ<Type> & operator=(const priorityQ<Type>&);
    void insert(const Type&);
    void deleteHighestPriority();
    Type getHighestPriority() const;
    bool isEmpty() const;
    void bubbleUp(int);
    void bubbleDown(int);
    int getSize() const;
private:
    int capacity;
    int items;
    Type * heapArray;
};

/*
* priorityQ(int capacity): constructor for a new, empty priorityQ
* parameters: capacity - int with the size of queue
* return value: N/A
*/
template <class Type>
priorityQ<Type>::priorityQ(int capacity)
{
    this->capacity = capacity;
    heapArray= new Type[capacity+1];
    items = 0;
}

/*
* priorityQ(const priorityQ<Type> & copy): copy constructor for priorityQ
* parameters: copy - priorityQ class to copy into *this
* return value: N/A
*/
template <class Type>
priorityQ<Type>::priorityQ(const priorityQ<Type> & copy)
{
    this->capacity = copy.capacity;
    heapArray = new Type[capacity];
    for (int i = 0; i < copy.capacity; i++)
	{
        heapArray[i] = copy.heapArray[i];
        items++;
	}
}


/*
* ~priorityQ(): destructor for priorityQ
* parameters: N/A
* return value: deleted priorityQ
*/
template <class Type>
priorityQ<Type>::~priorityQ()
{
    for (int i = 0; i < capacity; i++)
	{
        heapArray[i] = 0;
        items--;
	}
    delete [] heapArray;

}

/*
* operator=(const priorityQ<Type>& rhs): operator= constructor for priorityQ
* parameters: rhs - priorityQ class to assign copy *this
* return value: priorityQ with the same information as rhs
*/
template <class Type>
const priorityQ<Type>& priorityQ<Type>::operator=(const priorityQ<Type>& rhs)
{
    //self check
    if (this != &rhs)
    {
        //deallocate
        ~priorityQ();

        //reallocate and deep copy
        this->capacity = rhs.capacity;
        //*this->heapArray = new Type;
        for (int i = 0; i < rhs.capacity; i++)
	    {
		    (*this)->heapArray[i] = rhs.heapArray[i];
            (*this)->items++;
	    }
    }

}

/*
* insert(const Type & element): inserts element to the end of the heap and bubbles the element up, resizes if needed, also increments items counter by 1
* parameters: element - lander class to insert into heap
* return value: N/A
*/
template <class Type>
void priorityQ<Type>::insert(const Type & element)
{
    heapArray[items+1] = element;
    items++;
    bubbleUp(items);
    //cout << items << " items " << endl;
    if (items > capacity)
        capacity++;
}

/*
* deleteHighestPriority(): removes the root element by assigning the rootwith the end element in the heap 
* and bubbles the element down,  also decrements items by 1 (doesnothing if the heap is empty)
* parameters: N/A
* return value: N/A
*/
template <class Type>
void priorityQ<Type>::deleteHighestPriority()
{
    if (!isEmpty())
    {
        // cout << "\n Before Delete : ";
        // for (int i = 1; i  < items+1; i++)
        // {
        //     cout <<heapArray[i].get_id() << " ";
        // }
        // cout << endl;
        swap(heapArray[1],heapArray[items]);
        items--;
        bubbleDown(1);   
    }
}

/*
* getHighestPriority(): returns the highest priority item, the itemat index 1 of the heapArray
* parameters: N/A
* return value: the first element in heapArray
*/
template <class Type>
Type priorityQ<Type>::getHighestPriority() const
{
    return heapArray[1];
}

/*
* isEmpty(): returns true if there are no items in the heap and false otherwise
* parameters: N/A
* return value: true or false
*/
template <class Type>
bool priorityQ<Type>::isEmpty() const
{
    if (getSize() <=0)
    {
        return true;
    }
    else   
    {
        return false;
    }

}

/*
* bubbleUp(int index):  bubbles up an element in heapArray at index ”index”, and keeps bubbling up as needed, 
* remember an the parent of element at index x in the heapArrayis at index x / 2
* parameters: index - int of the index of the array in which to bubble up that element
* return value: N/A
*/
template <class Type>
void priorityQ<Type>::bubbleUp(int index)
{
    int parentIndex = index/2;
    if ((index <= 1) || (parentIndex <= 0))
    {
        //cout << "index too smol" << endl;
        return;
    }
    //swap
    if(heapArray[index] < heapArray[parentIndex])
    {
        //update
        swap(heapArray[parentIndex], heapArray[index]);
        bubbleUp(parentIndex);
        
        // cout << "\n After Bubble Up Swap: ";
        // for (int i = 1; i  < 11; i++)
        // {
        //     cout <<heapArray[i].get_id() << " ";
        // }
        // cout << endl;
    }

}

/*
* bubbleDown(int index): bubbles  down  an  element  from  index  ”index”
* ,and keeps bubbling down as needed, remember the left child and right child of element x is
*  at location2 * x and 2 * x + 1 respectively, you always bubble down with the highest priority child,
*  also rememberif 2 * x>items then x is a leaf node and no bubbling down is needed/
* parameters: index - int of the index of the array in which to bubble down that element
* return value: N/A
*/
template <class Type>
void priorityQ<Type>::bubbleDown(int index)
{
    // cout << "\n Before BubbleDown Swap: ";
    // for (int i = 1; i  < 11; i++)
    // {
    //     cout <<heapArray[i].get_id() << " ";
    // }
    // cout << endl;

    int rightChildI, leftChildI;
    Type tmpElement;
    leftChildI = 2*index;
    rightChildI = (2*index)+1;

    int leafCheck = 2 * index;
    if(leafCheck > items)
    {
        return;
    }
    // cout << rightChildI << " here  " << items << endl;
    if ((leftChildI <= items) && (rightChildI <= items))
    {     
        if ((heapArray[leftChildI] < heapArray[index]) && (heapArray[leftChildI] < heapArray[rightChildI]))
        {
            swap(heapArray[leftChildI], heapArray[index]);
            bubbleDown(leftChildI);
        }
        else if (heapArray[rightChildI] < heapArray[index])
        {
            swap(heapArray[rightChildI], heapArray[index]);
            bubbleDown(rightChildI);
        }
    }
    else if (leftChildI <= items)
    {
        if (heapArray[leftChildI] < heapArray[rightChildI])
        {
            swap(heapArray[leftChildI], heapArray[index]);
            bubbleDown(leftChildI);
        }
    }
    else if (rightChildI <= items)
    {    
        if (heapArray[rightChildI] < heapArray[index])
        {  
            swap(heapArray[rightChildI], heapArray[index]);
            bubbleDown(rightChildI);
        } 
    }
    // cout << "\n After BubbleDown Swap: ";
    // for (int i = 1; i  <= items; i++)
    // {
    //     cout <<heapArray[i].get_id() << " ";
    // }
    // cout << endl;
    return;

}   

/*
* getSize():  returns the amount of elements stored in the heap
* parameters: N/A
* return value: int - of amount of elements stored in the heap
*/
template <class Type>
int priorityQ<Type>::getSize() const
{
    return items;
}
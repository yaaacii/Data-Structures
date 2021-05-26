/*
* Name: Cicelia Siu, 5005247749, Assignment 9
* Description: vertex.h for Assignment 9 ; 
* 	gives function declaration and implementation for vector and edgeIterator class
* Input: N/A
* Output: N/A
*/

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;


template <class Type> 
class vertex
{
    struct node
    {
        Type item;
        node * link;
    };
    public:
        class edgeIterator
        {
            public:
                friend class vertex;
                edgeIterator();
                edgeIterator(node *);
                edgeIterator operator++(int);
                Type operator*();
                bool operator==(const edgeIterator&);
                bool operator!=(const edgeIterator&);
            private:
                node * current;
        };
        vertex();
        vertex(const  vertex <Type >&);
        const vertex& operator=(const vertex <Type >&);
        ~vertex ();
        edgeIterator begin();
        edgeIterator end();
        void addEdge(const  Type &);
    private:
    node * neighbors;
};

/*
* edgeIterator(): constructor for a new, empty hashmap
* parameters: N/A
* return value: N/A
*/
template <class Type> 
vertex<Type>::edgeIterator::edgeIterator()
{
    current = NULL;
}

/*
* edgeIterator(vertex<Type>::node * edge): constructor that is not empty
* parameters: edge - node pointer that is set to current
* return value: N/A
*/
template <class Type> 
vertex<Type>::edgeIterator::edgeIterator(vertex<Type>::node * edge)
{
    current = edge;
}

/*
* operator++(int): sets iterator to point to the next node object
* parameters: n/a ?
* return value: N/A
*/
template <class Type> 
typename vertex<Type>::edgeIterator vertex<Type>::edgeIterator::operator++(int)
{
    current = current->link;
    return current;
}


/*
* operator*()): dereferences the iteraator
* parameters: N/A
* return value: item field of the current node
*/
template <class Type> 
Type vertex<Type>::edgeIterator::operator*()
{
    return current->item;
}

/*
* operator==(const vertex<Type>::edgeIterator& rhs): 
* compares adress of the iterator on left to right
* parameters: rhs- adress of iterator to compare to
* return value: true if same, false if different
*/
template <class Type> 
bool vertex<Type>::edgeIterator::operator==(const vertex<Type>::edgeIterator& rhs)
{
    if (current == rhs.current)
        return true;
    // else
    return false;
}


/*
* operator!=(const vertex<Type>::edgeIterator& rhs): 
* compares adress of the iterator on left to right
* parameters: rhs- adress of iterator to compare to
* return value: true if different, false if same
*/
template <class Type> 
bool vertex<Type>::edgeIterator::operator!=(const vertex<Type>::edgeIterator& rhs)
{
    if (current != rhs.current)
        return true;
    // else
    return false;
}

/*
* vertex(): default constructor that sets neighbors to NULL
* parameters: N/A
* return value: N/A
*/
template <class Type> 
vertex<Type>::vertex()
{
    neighbors = NULL;
}

/*
* vertex<Type>::vertex(const vertex<Type>& copy)- a copy constructor
* that deep copies the neighbor list of the object passed into the constructor to the object that calls the constructor
* parameters: copy - vertex object that is going to be copied
* return value: N/A
*/
template <class Type> 
vertex<Type>::vertex(const vertex<Type>& copy)
{
        if (copy.neighbors == nullptr)
        {
            neighbors = nullptr;
        }

        node * tmpC; 
        node * tmpL;
        tmpC = copy.neighbors;
        tmpL = new node;
        neighbors = tmpL;
        tmpL->item = tmpC->item;
        tmpL->link = tmpC->link;
            // move to next node
        tmpC = tmpC->link; 
        while (tmpC != NULL)
        {
            tmpL->link = new node;
            tmpL = tmpL->link;
             
            tmpL->item = tmpC->item;
            tmpL->link = tmpC->link;

            tmpC = tmpC->link;
             
        }
        tmpL->link = NULL;
}


/*
* const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& copy)- assignment operator,
* that performs a deep copy of the right side object with the left side object (the object 
* that calls the operator function)
* parameters: copy - vertex object that is going to be copied
* return value: N/A
*/
template <class Type> 
const vertex<Type>& vertex<Type>::operator=(const vertex<Type>& rhs)
{
    if (this != &rhs)
    {
        //deallocate
        ~vertex();
        // while (neighbors != nullptr)
        // {
        //     node * del1;
        //     del1 = neighbors;
        //     neighbors = neighbors->link;
        //     delete del1;
        // }

        //copy
        (vertex(rhs));
    }
    return *this;
}

/*
* vertex<Type>::~vertex()- destructor, deallocates all the nodes in its neighbor list
* parameters - N/A
* return value: N/A
*/
template <class Type> 
vertex<Type>::~vertex()
{
    while (neighbors != NULL)
    {
        node * del1;
        del1 = neighbors;
        neighbors = neighbors->link;
        delete del1;
    }
    // node * del1;
    // node * prev;
    // del1 = neighbors;
    // while (del1 != nullptr)
    // {
    //     prev = del1;
    //     del1 = del1->link;
    //     delete prev;
    // }
}


/*
* typename vertex<Type>::edgeIterator vertex<Type>::begin()- returns a edgeIterator object 
* whose current will be the head of the neighbor list for the vertex object
* parameters - N/A
* return value: edgeIterator object
*/
template <class Type> 
typename vertex<Type>::edgeIterator vertex<Type>::begin()
{
    if (neighbors == NULL)
        return NULL;
    vertex<Type>:: edgeIterator first;
    first.current = neighbors;
    return first;
}


/*
typename vertex<Type>::edgeIterator vertex<Type>::end()-  returns a edgeIterator object
* whose current will be assigned to NULL
* parameters - N/A
* return value: edgeIterator object
*/
template <class Type> 
typename vertex<Type>::edgeIterator vertex<Type>::end()
{
    if(neighbors == NULL)
        return NULL;
    vertex<Type>:: edgeIterator last;
    last.current = NULL;
    return last;
}

/*
* void vertex<Type>::addEdge(const Type& edge)- adds a new node into the neighbor list 
* (a headinsert would be the best way to implement this)
* parameters: edge - a Type of which is going to be added
* return value: N/A
*/
template <class Type> 
void vertex<Type>::addEdge(const Type& edge)
{
    if (neighbors == nullptr)
    {
        node * front = new node;
        front->item = edge;
        front->link = nullptr;
        neighbors = front;
    }
    else
    {    
    node * front = new node;
    front->item = edge;
    front->link = neighbors;
    neighbors = front;
    }
}

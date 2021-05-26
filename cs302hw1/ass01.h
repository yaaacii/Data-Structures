/*
Name: Cicelia Siu
Class: CS 302
Assignment 1 - CS 202 Review - Make a 15 Puzzle

ass01.h file
*/

#ifndef __ASS01_H__
#define __ASS01_H__


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

template <class Type >
class LL
{
    struct node
    {
        Type item;
        node * next;
        node * prev;
    };
    public:
        class iterator
        {
        public:
            friend class LL;
            iterator ();        // constructor
            iterator(node *);
            Type  operator *();
            iterator  operator ++(int);
            iterator  operator --(int);
            bool  operator ==( const  iterator &)  const;
            bool  operator !=( const  iterator &)  const;
        private:
            node * current;
        };

        LL();       //constructor
        LL(const LL&);
        const LL& operator =(const  LL&);
        ~LL();
        iterator  begin () const;
        iterator  end() const;
        void  headRemove ();
        void  tailRemove ();
        void  removeNode(const  iterator &);
        bool  isEmpty ()  const;
        void  headInsert(const  Type &);
        void  tailInsert(const  Type &);
        void  update(const  iterator&, const  Type &);
    private:
        node * head;
        node * tail;
};


//constructor
template <class Type>
LL<Type>::iterator::iterator ()
{
    current = nullptr;
}

//copy constructor
template <class Type>
LL<Type>::iterator::iterator(node * pointer)
{ 
    current = pointer;
}

//get private item
template <class Type>
Type LL<Type>::iterator::operator *()
{
    return current->item;       //return's current's item
}

//moves iterator to the right
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator::operator ++(int)
{
    current = current->next;     //sets current to its next link for the next node
    return *this;               //not sure if this part is right
}

//moves iterator to the left
template <class Type>
typename LL<Type>::iterator LL<Type>::iterator:: operator --(int)
{
    current = current->prev;    //sets current to its previous 
    return *this;
}

//comparision for iterators
template <class Type>
bool LL<Type>::iterator::operator ==(const iterator & rhs) const
{
    return rhs == *this;        //if rhs == *this, return true, if not, false
}

//comparison for iterators
template <class Type>
bool LL<Type>::iterator:: operator !=(const iterator & rhs) const
{
    return rhs != *this;        //if rhs != *this, return true, if not false.
}

//constructor
template <class Type>
LL<Type>::LL()
{
    head = nullptr;
    tail = nullptr;
}

//copy constructor 
template <class Type>
LL<Type>::LL(const LL& copy)
{
    if (copy.isEmpty())
    {
        tail = nullptr;
        head = nullptr;
    }
    else
    {
        node * tmpCopy = copy.head;
        node * tmpCurrent= head;
        tmpCurrent = new node;        //create new node for head and copy item, next, previous
        tmpCurrent->item = tmpCopy->item;
        tmpCurrent->next = tmpCopy->next;  
        tmpCurrent->prev = tmpCopy->prev;     //should be nullptr
        node * tmpPrev = tmpCurrent;   
        tmpCopy = tmpCopy->next;            //move to next node

        while (tmpCopy != nullptr)
        {
            tmpCurrent->next = new node;     // allocate memory for a new node
            tmpCurrent = tmpCurrent->next;
            tmpCurrent->item = tmpCopy->item;      //copy info from tmp
            tmpCurrent->prev = tmpPrev;
            tmpCurrent->next = nullptr;       // null bc idk if there is a next at this point

            tmpPrev = tmpCurrent;              // update for the next previous
            tmpCopy = tmpCopy->next;                //next node on tmp, will loop if tmp!=nullptr
        }
        tail = tmpCurrent;                    // not sure if this is needed
    }
}

//operator =
template <class Type>
const LL<Type>& LL<Type>::operator =(const  LL& rhs)
{
    //deallocate lhs
    while (!(*this).isEmpty())
    {
        (*this).removeHead();
    }

    //then do same as copy constructor
    if (rhs.isEmpty())
    {
        tail = nullptr;
        head = nullptr;
        return *this;
    }

    node * tmpCopy = rhs.head;
    node * tmpCurrent= head;
    tmpCurrent = new node;        //create new node for head and copy item, next, previous
    tmpCurrent->item = tmpCopy->item;
    tmpCurrent->next = tmpCopy->next;  
    tmpCurrent->prev = tmpCopy->prev;     //should be nullptr
    node * tmpPrev = tmpCurrent;   
    tmpCopy = tmpCopy->next;            //move to next node

    while (tmpCopy != nullptr)
    {
        tmpCurrent->next = new node;     // allocate memory for a new node
        tmpCurrent = tmpCurrent->next;
        tmpCurrent->item = tmpCopy->item;      //copy info from tmp
        tmpCurrent->prev = tmpPrev;
        tmpCurrent->next = nullptr;       // null bc idk if there is a next at this point

        tmpPrev = tmpCurrent;              // update for the next previous
        tmpCopy = tmpCopy->next;                //next node on tmp, will loop if tmp!=nullptr
    }
    tail = tmpCurrent;                    // not sure if this is needed
    return *this;
}

//destructor
template <class Type>
LL<Type>::~LL()
{
    while(!isEmpty())
        {
            node * tmp = head;      
            head = head->next;  
            delete tmp;             //deallocate each node
        }
        tail = nullptr;
}


//sets iterator to beginning of Linked List
template <class Type>
typename LL<Type>::iterator LL<Type>:: begin () const
{
    return LL<Type>::iterator(head);
}

template <class Type>
typename LL<Type>::iterator LL<Type>:: end() const
{
    return LL<Type>::iterator(tail);
}

//remove the head and deallocate
template <class Type>
void LL<Type>:: headRemove ()
{
    node * d1;
    d1 = head;
    head = head->next;
    delete d1;

}

//remove and deallocate tail
template <class Type>
void  LL<Type>::tailRemove ()
{
    node * d1;
    d1 = tail;
    tail = tail->prev;
    delete d1;
}

//remove and deallocate node
template <class Type>
void LL<Type>:: removeNode(const  iterator & it)
{
    node * d1, * d2;
    d1 = it.current;
    d2 = d1->prev;
    d2->next = d1->next;
    it.current = d2;
    delete d1;
}

//check if LL is empty
template <class Type>
bool LL<Type>::isEmpty () const 
{
   return head == nullptr;
}

//insert a node into the head
template <class Type>
void LL<Type>::headInsert(const Type & element)
{
    if (head == nullptr)
    {
        node * tmp;
        tmp = new node;
        tmp->item = element;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        head = tmp;
        tail = tmp;
    }
    else
    {
        node * tmp;
        tmp = new node;
        tmp->item = element;
        tmp->next = head;
        tmp->prev = nullptr;
        head = tmp;
    }
}

//insert a node into the tail
template <class Type>
void  LL<Type>::tailInsert(const  Type & element)
{
    if (head == nullptr)
    {
        node * tmp;
        tmp = new node;
        tmp->item = element;
        tmp->next = nullptr;
        tmp->prev = nullptr;
        head = tmp;
        tail = tmp;
    }
    else
    {
        node * tmp;
        tmp = new node;
        tmp->item = element;
        tmp->next = nullptr;
        tmp->prev = tail;
        tail->next = tmp;
        tail = tmp;
    }
    
}


//putting element into it's current's item
template <class Type>
void LL<Type>::update(const LL<Type>::iterator & it, const Type & element)
{
    node * tmp = it.current;
    tmp->item = element;
}



#endif // __ASS01_H__
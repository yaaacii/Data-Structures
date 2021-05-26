/*
* Name: Cicelia Siu, 5005247749, Assignment 7
* Description: hashmap.h for Assignment 7 ; 
* 	gives function declaration and implementation for hashmap class
* Input: N/A
* Output: N/A
*/

#include <string>
#include <cstdlib>
#include <iostream>
using namespace std;


template <class type1, class type2>
class hashMap
{
public:
	const int MAX_ELEMENTS;
	hashMap(int = 10);
	hashMap(const hashMap<type1, type2>&);
	const hashMap<type1, type2>& operator=(const hashMap<type1, type2>&);
	~hashMap();
	type2& operator[](std::string);
private:
	int hashFunction(std::string) const;
	void resize(int);
	

	struct node
	{
		type1 key;
		type2 value;
		node * next;
		node * prev;
	};

	struct list
	{
		node * head;
		node * middleElement;
		int amount;
	};
	
	int filledEntries;
	int tableSize;

	list * table;
};

/*
* hashMap(int init): constructor for a new, empty hashmap
* parameters: init - int with the size if the table
* return value: N/A
*/
template <class type1, class type2>
hashMap<type1, type2>::hashMap(int init) : MAX_ELEMENTS(10)
{
	tableSize = init;
	filledEntries = 0;
	
	table = new list[tableSize];
	for (int i = 0; i < tableSize; i++)
	{
		table[i].head = 0;
	}
}


/*
* hashMap(const hashMap<type1, type2>& copy): copy constructor for hashmap
* parameters: copy - hashmap class to copy into *this
* return value: N/A
*/
template <class type1, class type2>
hashMap<type1, type2>::hashMap(const hashMap<type1, type2>& copy) : MAX_ELEMENTS(10)
{
		list * copyTable = copy.table;
		tableSize = copy.tableSize;
		filledEntries = 0;
		table = new list[tableSize];

		for (int i = 0; i < tableSize; i++)
		{
			table[i].head = NULL;
			table[i].middleElement = NULL;
			table[i].amount = 0;
		}

		node * it;
		for (int i = 0; i < tableSize; i++)
			for (it = copyTable[i].head; it != NULL; it = it->next)
				(*this)[it->key] = it->value;
}

/*
* operator=(const hashMap<type1, type2>& rhs): operator= constructor for hashmap
* parameters: rhs - hashmap class to assign copy *this
* return value: hashmap with the same information as rhs
*/
template <class type1, class type2>
const hashMap<type1, type2>& hashMap<type1, type2>::operator=(const hashMap<type1, type2>& rhs)
{
	//check for self assignment
	if (this != &rhs)
	{
		//deallocate table
		for (int i = 0; i < tableSize; i++)
		{
			node * del1, * del2;
			del1 = table[i].head;

			while (del1 != NULL)
			{
				del2 = del1->next;
				delete del1;
				del1 = del2;
			}
		}
		delete []table;
		// reallocate
		list * rhsTable = rhs.table;
		tableSize = rhs.tableSize;
		filledEntries = 0;
		table = new list[tableSize];

		for (int i = 0; i < tableSize; i++)
		{
			table[i].head = NULL;
			table[i].middleElement = NULL;
			table[i].amount = 0;
		}

		node * it;
		for (int i = 0; i < tableSize; i++)
			for (it = rhsTable[i].head; it != NULL; it = it->next)
				(*this)[it->key] = it->value;
	}
	return *this;
}


/*
* ~hashMap(): destructor for hashmap
* parameters: N/A
* return value: deleted hashmap
*/
template <class type1, class type2>
hashMap<type1, type2>::~hashMap()
{
	//Deallocate table
	for (int i = 0; i < tableSize; i++)
	{
		node * del1, * del2;
		del1 = table[i].head;

		while (del1 != NULL)
		{
			del2 = del1->next;
			delete del1;
			del1 = del2;
		}
	}
	delete [] table;
}

/*
* operator[](std::string key): 
* creates or finds the key in the hash structor
* parameters:key - string in which you want to find/create
* return value: type2() value of the node with the matching key
*/
template <class type1, class type2>
type2& hashMap<type1, type2>::operator[](std::string key)
{
	//find loadFactor
	int loadFactor = filledEntries/tableSize;
	if (loadFactor >= 0.5)
	{
		resize(tableSize*2);
	}
	// hashfunction and assign result to variable index
	int index = hashFunction(key);
	// if table[index].head is empty, add node
	step3:
	if (table[index].head == NULL)
	{
		node * tmp;
		tmp = new node;
		tmp->next = NULL;
		tmp->prev = NULL;
		table[index].head = tmp;
		table[index].middleElement = tmp;
		tmp->key = key;
		tmp->value = type2();
		table[index].amount++;
		return table[index].head->value;
	} else 
	// if table[index].head is not Empty, add it into table
	{
		//4a
		node * it;
		it = table[index].middleElement;
		//4b and c
		while (it->key != key)
		{
			if (it->key < key)
			{	
				//check if reached the end
				if (it->next == NULL)
				{
					if (table[index].amount < MAX_ELEMENTS)
					{
						node * tmp;
						tmp = new node;
						tmp->next = NULL;
						tmp->prev = it;
						it->next = tmp;
						table[index].amount++;
			
						if (table[index].amount % 2 == 1)
						{
							node * mE = table[index].middleElement;
							table[index].middleElement = mE->next;
						}
						if (table[index].amount == MAX_ELEMENTS)
							filledEntries++;
						tmp->key = key;
						tmp->value = type2();
						return tmp->value;
					} 
					else  // max elements
					{
						index = (index + 1) % tableSize;
						goto step3;
					}
				}
				else
				{
					it = it->next;
				}
			} 
			else if (it->key > key)
			{
				// check if reached the beginning
				if (it->prev == NULL)
				{
					if (table[index].amount < MAX_ELEMENTS)
					{
						node * tmp;
						tmp = new node;
						tmp->next = it;
						it->prev = tmp;
						tmp->prev = NULL;
						table[index].head = tmp;
						table[index].amount++;
						//possibly wrong?
						if (table[index].amount % 2 == 0)
						{
							node * mE = table[index].middleElement;
							table[index].middleElement = mE->prev;
						}
						if (table[index].amount == MAX_ELEMENTS)
							filledEntries++;
						tmp->key = key;
						tmp->value = type2();
						return tmp->value;
					} 
					else  // max elements
					{
						index = (index + 1) % tableSize;
						goto step3;
					}
				}
				else
				{
					//move it left
					it = it->prev;
				}
			}
		}
		return it->value;
	}
}

/*
* hashFunction(std::string key) const: 
* 	this function adds up all the ASCII values for each character in 
* 	the string parameter passed in, then mods this sum by the tableSIze 
* 	and returns that value
* parameters:key - string in which you want to find the value for
* return value: int - the value that is added and mod
*/
template <class type1, class type2>
int hashMap<type1, type2>::hashFunction(std::string key) const
{
    int sum = 0;
	for(int i = 0; i < key.size(); i++)
	{
		sum += key[i];
	}
    sum = sum % tableSize;
	return sum; 
}

/*
* resize(int amt): 
* 	resizes the table by amt 
* parameters: amt - int in which the table increases amt much in size.
* return value: N/A
*/
template <class type1, class type2>
void hashMap<type1, type2>::resize(int amt)
{
	list * oldTable = table;
	int oldSize = tableSize;
	tableSize += amt;
	filledEntries = 0;
	table = new list[tableSize];

	for (int i = 0; i < tableSize; i++)
	{
		table[i].head = NULL;
		table[i].middleElement = NULL;
		table[i].amount = 0;
	}

	node * it;

	//goes through each table entry of the oldTable (obsolete table)
	//and maps them to an element of the new table and stores the same
	//value into the location where it's found in the new table
	for (int i = 0; i < oldSize; i++)
		for (it = oldTable[i].head; it != NULL; it = it->next)
			(*this)[it->key] = it->value;


	//Deallocate old table
	for (int i = 0; i < oldSize; i++)
	{
		node * del1, * del2;
		del1 = oldTable[i].head;

		while (del1 != NULL)
		{
			del2 = del1->next;
			delete del1;
			del1 = del2;
		}
	}
	delete [] table;
	delete [] oldTable;
}

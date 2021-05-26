/*
* Name: Cicelia Siu, 5005247749, Assignment 5
* Description: binaryTree.h for Assignment 5 ; 
* 	gives function declaration and implementation for binaryTree object
* Input: N/A
* Output: N/A
*/

#include <fstream>
#include <cstdlib>
using namespace std;

template <class type>
struct binTreeNode
{
	// binTreeNode();
	type item; //stores the data in the node of the tree
	binTreeNode<type> * left;
	binTreeNode<type> * right;
};

template <class type>
void readLISP(binTreeNode<type>*,  ifstream&);

binTreeNode<int>* createNode(ifstream&);

template <class type>
bool evaluate(binTreeNode<type>*, int, int, myStack<type>&);

template <class type>
void destroyTree(binTreeNode<type>*);

////////////////////////////////////////////////////////////////////

/*
* readLISP(binTreeNode<type> * r,  ifstream& infile): 
*	will read the inner nodes (excluding the root) of a LISP lanuage 
*	and put them into a binary tree
* parameters: 
*	r - the node root of a binary tree or subtree
*	infile - the file of where the LISP expression will be read from
* return value: N/A
*/
template <class type>
void readLISP(binTreeNode<type> * r,  ifstream& infile)
{
	binTreeNode<int> * tmp;
	char parenthesis;
	int value;

	//get
	infile >> parenthesis;
	if (parenthesis == '(')
	{
		// left
		infile >> parenthesis; //get right parenthesis, but
		if (parenthesis != ')')	// if it is a digit, put value in tree
		{
			infile.putback(parenthesis);
			infile >> value;
			r->left = new binTreeNode<int>;
			tmp = r->left;
			tmp->item = value;
			readLISP(r->left, infile);
			infile >> parenthesis; // get right parenthesis
		}
		else
		{
			r->left = nullptr;
		}

		//right
		infile >> parenthesis; // get left parenthesis
		if (parenthesis == '(')
		{
			infile >> parenthesis; //get right parenthesis, but
			if (parenthesis != ')')	// if it is a digit, put value in tree
			{
				infile.putback(parenthesis);
				infile >> value;
				r->right = new binTreeNode<int>;
				tmp = r->right;
				tmp->item = value;
				readLISP(r->right, infile);
				infile >> parenthesis; // get right parenthesis
			}
			else
			{
				r->right = nullptr;
			}
		}
	}
}

/*
* evaluate(binTreeNode<type> * r, int runningSum, int targetSum , myStack<type>& path): 
*	will look for a path from root to leaf that the sum along the path 
*	is equal to the target sum. 
* parameters: 
*	r - the node root of a binary tree or subtree
*	runningSum - an integer that shows the sum of the path at the node to the root
*	targetSum - an integer that shows what number that is wanted to be equivalent to the running sum.
* 	path - a myStack object by reference that has the current items along the path.
* return value: N/A
*/
template <class type>
bool evaluate(binTreeNode<type> * r, int runningSum, int targetSum , myStack<type>& path)
{
	if ( r == NULL) // reached the leaf
	{
		if (runningSum != targetSum)
		{
			path.pop();
			return 0;
		}
		else
		{
			return 1;
		}
	}
	runningSum = runningSum + r->item;
	if ((evaluate(r->left, runningSum, targetSum, path)) || (evaluate(r->right, runningSum, targetSum, path)))
	{
		path.push(r->item);
		return 1;
	}
	else
	{
		runningSum = runningSum - r->item;
		return 0;
	}
}

/*
* destroyTree(binTreeNode<type> * r): 
*	
* parameters: 
*	r - the node root of a binary tree or subtree
* return value: N/A
*/
template <class type>
void destroyTree(binTreeNode<type> * r) 
{
	if ( r == NULL)
		return;
	destroyTree(r->left);
	destroyTree(r->right);
	//cout<< "post order r item: " << r->item << endl;	// Debug purposes
	delete r;
}
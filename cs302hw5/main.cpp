/*
* Name: Cicelia Siu, 5005247749, Assignment 5
* Description: main.cpp ; Using simplified LISP language to build a 2 sub expression binary tree. 
* 	Then evaluating the tree if the sum of one of the paths are equivalent to a number.
* Input: a .txt file with test cases. Each case starts with an integer that the path is checking
*	for equivalency. The following is a LISP expression to be processed into a binary tree.
* Output: Each case will output if a path is equivalent to the intger or not. If there is a solution,
* 	terminal will output the numbers along the path and the equivalent number. If no solution, terminal 
*	will ouput, no solution.
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "myStack.h"
#include "binaryTree.h"
using namespace std;


int main()
{
	string inputStr;
	ifstream infile;
	int equivalent;
	char huh;
	int sum = 0;
	myStack<int> list;
	myStack<int> tmp;
	
	// open file
	cout << endl << "Enter LIPS file (All those parenthesis...): ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "Enter LIPS file (All those parenthesis...): ";
		cin >> inputStr;
		infile.open (inputStr);
	}

	while (true)
	{
		//get equivalency. break while loop when end of file
		if (!(infile >> equivalent))
		{
			break;
		}
		
		// build binary tree
		binTreeNode<int> * root;
		char chara;	 	//for paraenthesis
		int rootInt;
		infile >> chara; //get left parenthesis
		infile >> rootInt; //get root
		root = new binTreeNode<int>;
		root->item = rootInt;
		root->left = nullptr;
		root->right = nullptr;
		readLISP(root, infile);
		infile >> chara; //right parenthesis

		// check if there is path and print results
		if (evaluate(root, sum, equivalent, list))
		{
			cout << "\nPath in tree exists\n";
			while (!list.isEmpty())
			{
				cout <<list.top();
				list.pop();
				if (!list.isEmpty())
				{
					cout << " + ";
				}
			}
			cout << " = " << equivalent;
			
			cout << endl;
		}
		else 
		{
			cout << "\nNo such path exists, LISP is a pain anyway." << endl;
		}
		destroyTree(root);
	}
	infile.close();
	return 0;
}
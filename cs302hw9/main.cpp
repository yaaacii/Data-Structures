/*
* Name: Cicelia Siu, 5005247749, Assignment 9
* Description: main.cpp for Assignment 9 ; 
*   
* Input: N/A
* Output: N/A
*/

// #include "hashMap.h"
#include "vertex.h"
#include "myStack.h"
#include <fstream>
#include <unordered_map>
using namespace std;

// bool DFSBack(string current, string beginning, hashMap <string, vertex <string > > graph, hashMap <string, bool>& nodesInPath);
// bool getPaths(string current, string finalDestination, hashMap <string, vertex <string > > graph, hashMap <string, bool>& nodesInPath, myStack <string >& recStack, int& pathNo);

bool DFSBack(string current, string beginning, unordered_map <string, vertex <string > > graph);
bool getPaths(string current, string finalDestination, unordered_map <string, vertex <string > > graph, unordered_map <string, bool>& nodesInPath, myStack <string >& recStack, int& pathNo);


int main()
{
     // file 
    string inputStr;
    ifstream infile;
    // open lander input file
	cout << endl << "Last One :( : ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "Last One :( : ";
		cin >> inputStr;
		infile.open (inputStr);
	}

    //declare data structure and edgeIterators
    // hashMap<string, vertex<string>> adjLists;
	// hashMap<string, bool> nodesInPaths;
	unordered_map <string, vertex<string>> adjLists;
	unordered_map <string, bool> nodesInPaths;
	myStack<string> recStacks;
	int pathNos = 0;
	string start, end;
	string currentS, edgeS;
	infile >> start;
	infile >> end; 
	
	
	// create adjacency List 
	while (infile >> currentS)
	{
		infile >> edgeS;
		adjLists[currentS].addEdge(edgeS);
		//cout << "Here" <<endl;
		
	}
	 infile.close();

	// call get Path on each of them output each path
	 if(getPaths(start, end, adjLists, nodesInPaths, recStacks, pathNos) == true)
	{
	 	return 0;
	}
	else
	{
		cout << "No paths lead to the destination. Goodbye~" << endl;
		return 0;
	}

	//DEBUG: print hashMap (note not sure if .end() is right)
	// vertex<string>::edgeIterator it;
	// vertex<string>::edgeIterator nil(NULL)
	// for (it = adjList["North"].begin(); it != nil; it++)
	// 	{
	// 		cout << "Here" <<endl;
	// 		cout << *it << " ";
	// 	}
	// 	cout <<endl;
}


/*
* bool DFSBack(string current, string previous, unordered_map <string, vertex <string > > 
* graph, unordered_map <string, bool>& nodesInPath): check for reverse way
* parameters: current - node name of current street name
*			previous- node name of street we are trying to find a path to
*			graph - adjacency List
* return value: true or false.
*/
bool DFSBack(string current, string previous, unordered_map <string, vertex <string > > graph)
{
	//cout << "back\n";
	vertex<string>::edgeIterator back;
	vertex<string>::edgeIterator nil(NULL);
	for(back = graph[current].begin(); back != nil; back++)
	{
        //cout << "Check if neighbor: "<<*back << " is equal to " << previous << endl;
        if (*back == previous)
            return true;
	}
	//if back is not a neighbor of current, return false
	return false;
	
}

/*
* getPaths(string current, string finalDestination, hashMap 
* <string, vertex <string > > graph, hashMap <string, bool>& 
* nodesInPath, myStack <string >& recStack, int& pathNo): DFS type traversal
* parameters: current - node name of current street name
*			finalDestintion - node name of street we are trying to find a path to
*			graph - adjacency List
*			nodesInPath - hashMap that maps a node to a bool value, check if nodes are in current path
*			recStack - stores the order of nodes in current path
* 			pathNo - amount of paths from start node to end node so far
* return value: true or false.
*/
bool getPaths(string current, string finalDestination, unordered_map <string, vertex <string > > graph, unordered_map <string, bool>& nodesInPath, myStack <string >& recStack, int& pathNo)
{
    //cout << endl<< "getPaths"<< endl << current <<endl;
	bool result;
	    
	if (nodesInPath[current])
	    return true;
    //DFS traversal
    //update nodesInPath and recStack
    nodesInPath[current] = true;
    recStack.push(current);
    
    // continue DFS traversal
	vertex<string>::edgeIterator i;
	vertex<string>::edgeIterator nil(NULL);
	unordered_map<string, bool> nodesInBackPath;
	//for (i = graph[current].begin(); i != graph[current].end(); i++)
	for (i = graph[current].begin(); i != nil; i++)  // because hash table/map cannot run tranverse its entire thing, correct me if I'm wrong
	{
		//cout << "try path: " << *i << endl;
		//go back the other way to check if it works two ways
		if (!nodesInPath[*i])
		{
			if(DFSBack(*i, current, graph))
			{
			    //cout << result <<" getPaths6 " << *i << endl;
			    bool temp_result = getPaths(*i, finalDestination, graph, nodesInPath, recStack, pathNo);
			    result = result || temp_result;   // as long as we have a good result
			    //cout << "getPaths7 OUT " << *i << endl; 
			}
		}
		
	}
	if (current == finalDestination)
	{   
		//cout << "MATCHES!!!!!!!!!!!!!!!!!!!!" << endl;
		//once two way is found, output nodes in path (update pathNo)
		cout << "Path " << pathNo+1 << ": ";
		myStack<string> tmp;
		while (!recStack.isEmpty())
		{
			tmp.push(recStack.top());
			recStack.pop();
		}
		while(!tmp.isEmpty())
		{
			cout << tmp.top();
			recStack.push(tmp.top());
			if (tmp.top() != finalDestination)
				cout << " <=> ";
			tmp.pop();	
		}
		cout << endl;
		pathNo++;
		result = true;
	}
    
    //leave node: 
    nodesInPath[current] = false;
    recStack.pop();
    return result;
}


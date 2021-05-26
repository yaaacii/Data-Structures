/*
* Name: Cicelia Siu, 5005247749, Assignment 6
* Description: This will find duplicate assignments and the number of missing 
*   assignments for each student, using unordered_maps.
* Input: You will be given two files, one that has all the students’ 
*   names and the other with a set of assignments,each assignment will 
*   contain the following stringstudentName_A#where # will be a number from 1-9
* Output: Output the amount of missing assignments for each student
*/

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

int main()
{
    string inputStr;
    ifstream infile;
    vector <string> names;
    unordered_map <string, int> missingAssigns;
    string name;
    vector <string> condensedAssigns;
    unordered_map <string, bool> duplicate;
    string assignment;

    // open name file
	cout << endl << "Enter students file: ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "Enter students file: ";
		cin >> inputStr;
		infile.open (inputStr);
	}

    // fill names into vector
    while ((infile >> name))
    {
        names.push_back(name);
    }
    infile.close();
    
    //fill unordered map of missing Assings with names:
    //O(n)
    for (int i = 0; i < names.size(); i++)
    {
        // 9 total assignments
        missingAssigns[names[i]] = 9;
    }
    
    //open assignments file
	cout << endl << "Enter assignments file: ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "Enter assignments file: ";
		cin >> inputStr;
		infile.open (inputStr);
	}

    //look for duplications and subtract missing assignments
    //O(2n) = O(n)
    for (int i = 0; infile >> assignment ; i++)
    {
        if (!duplicate[assignment])
        {
            //mark as seen
            condensedAssigns.push_back(assignment);
            duplicate[assignment] = true;
            name = assignment.erase(assignment.find("_"), assignment.size());
            missingAssigns[name] = missingAssigns[name] - 1; // subtract # of missing assignments
            
        }
    }
    infile.close();
    
    // print out
    cout << "\nName" << setw(34) << "Missing Assignments" << endl;
    for (int i = 0; i < names.size(); i++)
    {
        cout << names[i] << setw(20 - names[i].length()) << missingAssigns[names[i]] << endl;
    }
}

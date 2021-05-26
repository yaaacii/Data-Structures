/*
* Name: Cicelia Siu, 5005247749, Assignment 7
* Description: main.cpp Use a hashMap: You have to
*   analyze the document and separate the words first.  Words are consecutive 
*   sequences of lower case letters.  After listing the words, in the order 
*   same as they occurred in the document, you have to number them from 
*   1,2, ...,3.  After that you have to find the range p and q(p≤q) in the 
*   list such that all of words occur between p and q(inclusive). If there 
*   are multiple such solutions you have to find the one where the difference 
*   of p and qis smallest.  If still there is a tie, then find the solution where
*   pis smallest.
* Input: a .txt file, consisting of lowercase letters, numbers and punctuations.
*   Each test case ends with "END".
* Output: Output the range p and q(p≤q) in the 
*   list such that all of words occur between p and q(inclusive)
*/


#include "hashMap.h"
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    // file 
    string inputStr;
    ifstream infile;
    // open file
	cout << endl << "You know the drill: ";
	cin >> inputStr;
	infile.open (inputStr);
	while (infile.fail())
	{
		cout << "You know the drill: ";
		cin >> inputStr;
		infile.open (inputStr);
	}

    cout << endl;
    int testCase = 1;
    do
    {
        string fileString;
        vector <string> stringArr;
        hashMap <string, int> countWords;

        while (infile >> fileString)
        {
            if (fileString == "END")
            {
                break;
            }
            // analyze document and separate strings into the vector
            for (int i =0; i < fileString.size(); i++) //delete punctuation 
            {
                if (!isalpha(fileString[i]))
                {
                    /* need to figure out a way to make
                    the strings separate on case 3 */
                    //debug: cout << " got rid of " <<fileString[i] << endl;
                    string firstString;
                    firstString = fileString.substr(0, i);
                    if (isalpha(firstString[0]))
                        stringArr.push_back(firstString);
                    fileString = fileString.substr(i+1);
                    i = -1;
                }
            }
            // cout << fileString <<endl;
            if (!fileString.empty())
                stringArr.push_back(fileString);
        }
        

        // list words in countWords (no duplicates) and unique
        int count = 0;
        hashMap<string, int> unique;
        for (vector<string>::const_iterator i = stringArr.begin(); i != stringArr.end(); i++ )
        {
            //debug : cout << *i << endl;
            countWords[*i] = 0;
            unique[*i] = unique[*i] + 1;
            if(unique[*i] < 2)
                count++;
            //Debug:
            //cout << *i  << countWords[*i] << endl;
        }

        //sliding window technique to find p and q
        bool goodBounds = true;
        int windowSize = count;
        if (windowSize < 1)
            break;
        //debug: cout << "window : "<< windowSize<< endl;
        int p = 0;      //lower bound
        int q = p + windowSize -1;  //upper bound
        for (int i = 0; i <= stringArr.size() - windowSize; i++)
        {
            //debug: cout << stringArr.size() << " what " << stringArr.size() - windowSize << endl;
            hashMap <string, int> currentWindow;
            currentWindow = countWords;
            goodBounds = true;
            for (int currentIndex = p; currentIndex <= q; currentIndex++)
            {
                //check if all of them are unique and
                currentWindow[stringArr[currentIndex]] = currentWindow[stringArr[currentIndex]] + 1;
                //have all the words in them
                //debug : cout << p << " " << q << stringArr[currentIndex] << currentWindow[stringArr[currentIndex]] << endl;
                if (currentWindow[stringArr[currentIndex]] > 1)
                    goodBounds = false;
            }
            // debug: currentWindow.test();
            if(goodBounds == true)
            {
                cout << "Test Case " << testCase <<": ";
                cout << p+1 << "  " << q+1 << endl;
                break;
            }
            p++;
            q++;
        }
        //debug: cout << "try 2 : " << testCase<< endl;
        testCase++;
    }
    while (!infile.eof());
    infile.close();
    cout << endl <<"Before this program ends, just remember...\nWords can in fact hurt >:(" << endl;
    return 0;
}
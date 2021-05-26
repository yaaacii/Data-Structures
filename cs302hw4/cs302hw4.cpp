/*
* Name: Cicelia Siu, 5005247749, Assignment 4
* Description: a brief description of the program.
* Input: A number between 0 and 512 for list size. 
*       Another for threads > 0. (Max depends on hardware)
* Output: Sorted Vector of Numbers
*/

#include <iostream>
#include <thread>
#include <string>
#include <vector>
#include <chrono>
using namespace std;

vector <int> integerVector;

void insertionSort(int, int);
void mergeLists(int, int, int, int);


int main()
{
    int goodSize, goodThreadCount;
    vector <thread> threadPool;
    string input;
    int listSize, numThreads;
    int sublistSize;
    int indexL, indexR;
    int indexLL, indexLR, indexRL, indexRR;
    int numSublist;
    int maxNumThreads = thread::hardware_concurrency();

    // ---------"Randomizing"--------------  // need to fix if listSize is a non-numerical type
    // ask for listSize and num of Threads
    cout <<endl;
    do
    {     
        cout << "Size of the list: ";
        cin >> input;
        if (isdigit(input[0]))
        {
            listSize = stoi(input);
            goodSize = 1;
        }
        else
        {
            goodSize = 0;
        }
    } while ((listSize<=0) || (!goodSize));

    do
    {
        numThreads = 0;
        cout << "Amount of Threads: ";
        cin >> input;
        if (isdigit(input[0]))
        {
            numThreads = stoi(input);
            goodThreadCount = 1;
        }
        else
        {
            goodThreadCount = 0;
        }
    } while ((numThreads < 1)||(numThreads > maxNumThreads)|| (!goodThreadCount));

    // fill vector with random numbers
    // Note: put in time if want it fully random, but take it out for writeup
    srand ((unsigned) /*time*/ (NULL));
    for (int i = 0; i< listSize; i++)
    {
        int randomNum = rand () % listSize + 1;
        integerVector.push_back(randomNum);
        //.pushback - pushes a thread object on the vector. 
    }

    // start timer
    auto start = chrono::steady_clock::now();

    /*
    // -------------------------Sort for Sequential Sorting-----------------------
    sort(integerVector.begin(), integerVector.end());
    
    // -------------------------End of Sequential Sorting-----------------------
    */


    //----------------------------Parallel Sorting------------------------------
    
    // ---------InsertionSort--------------
    sublistSize = listSize / numThreads;
    // find indices for each sublist
    indexL = 0;
    indexR = indexL+sublistSize-1;
    //create threads for insertionSOrt
    for (int i = 0; i < numThreads; i++)
    {
        threadPool.push_back(thread (insertionSort, indexL, indexR));
        indexL = indexL + sublistSize;
        indexR = indexR + sublistSize;
    }
    // check if all threads are done
    for (unsigned long long i = 0 ; i < threadPool.size(); i++)
    {
        threadPool[i].join();
    }
    threadPool.clear();

    
    // ---------MergeLists--------------
    // set indexes for first mergeList
    indexLL = 0;
    indexLR = indexLL + sublistSize - 1;
    indexRL = indexLR + 1;
    indexRR = indexRL + sublistSize - 1;
    numSublist = numThreads/2;

    //loop until number of sublists is = 1
    for (int i = 0; 1 <= numSublist; i++)
    {
        //make threads for mergeLists
        for (int j = 0; j < numSublist; j++)
        {
            threadPool.push_back(thread (mergeLists, indexLL, indexLR, indexRL, indexRR));
            indexLL = indexLL + (sublistSize*2);
            indexLR = indexLR + (sublistSize*2);
            indexRL = indexRL + (sublistSize*2);
            indexRR = indexRR + (sublistSize*2);
        }

        // check if all threads are done
        for (int j = 0 ; j < numSublist; j++)
        {
            threadPool[j].join();
        }
        threadPool.clear();

        //next indexes
        
        numSublist = numSublist/2;
        sublistSize = sublistSize * 2;
        indexLL = 0;
        indexLR = indexLL + sublistSize - 1;
        indexRL = indexLR + 1;
        indexRR = indexRL + sublistSize - 1;
    }
    // -------------------------End of Parallel Sorting-----------------------
    
    
    if (listSize <= 512) 
    {   
        cout << "Sorted : ";
        for (unsigned long long int j=0; j<integerVector.size(); j++) 
        {
            cout << integerVector[j] << " ";
        }
        cout<<endl;
    }
    else
    {
        cout << endl<< "The list size is above 512 numbers. (over max)" << endl;
    }
    //end timer
    auto end = chrono::steady_clock::now();
    //output time in nanoseconds
    //cout << "Elapsed time in seconds : " << chrono::duration_cast<chrono::nanoseconds>(end - start).count() << " nanoseconds" << endl;
    cout << endl;
    return 0; 
}

/*
* insertionSort: uses Insertion sort to sort integerVector within the parameters
* parameters: 
*   left: the left most index of the integerVector that needs to be sorted
*   right: the right most index of the integerVector that needs to be sorted
* return value: N/A
*/
void insertionSort(int left, int right)
{   
    for (int i = left+1; i <= right; i++)  //i maintains the steps
    {
        int key = integerVector[i];
        int j = i-1;    // j is used for shuffling until it is -1 
        //move elements that are greater than key to next position
        while ((j >= left ) && (key <= integerVector[j]))
        {
            (integerVector[j+1] =  integerVector[j]);
            j--;
        }
        integerVector[j+1] = key;
    }
}

/*
* mergeLists: merges two sorted sublists in integerVector 
* parameters: 
*   leftLeft: the left most index of the left sublist that needs to be merged
*   leftRight: the right most index of the left sublist that needs to be merged
*   rightLeft: the left most index of the right sublist that needs to be merged
*   rightRight: the right most index of the right sublist that needs to be merged
* return value: N/A
*/

void mergeLists(int leftLeft, int leftRight, int rightLeft, int rightRight)
{    
    vector <int> tmpLeft;
    vector <int> tmpRight;
    int currentPos = leftLeft;
    int currentLeft, currentRight;
    int tempLeftSize, tempRightSize;

    //fill temporary vectors
    for (int i = leftLeft; i<= leftRight ; i++)
    {
        tmpLeft.push_back(integerVector[i]);
        //.pushback - pushes a thread object on the vector. 
    }
    
    for (int i = rightLeft; i<= rightRight ; i++)
    {
        tmpRight.push_back(integerVector[i]);
        //.pushback - pushes a thread object on the vector. 
    }

    // merge sort
    currentLeft = 0;
    currentRight = 0;
    tempLeftSize = tmpLeft.size();
    tempRightSize = tmpRight.size();
    while ((currentLeft<tempLeftSize) && (currentRight < tempRightSize))
    {
        if (tmpLeft[currentLeft] <= tmpRight[currentRight])
        {
            //the one in rightList stays there and goes to next one in list
            integerVector[currentPos] = tmpLeft[currentLeft];
            currentLeft++;
        }
        else
        {
            // the one in right List gets put in places of current position
            integerVector[currentPos] = tmpRight[currentRight];
            currentRight++;
        }
        currentPos++;
    }
    
    //fill in the rest of left
    tempLeftSize = tmpLeft.size()-1;
    while (currentLeft <= tempLeftSize)
    {
        integerVector[currentPos] = tmpLeft[currentLeft];
        currentLeft++;
        currentPos++;
    }
    //fill in the rest of right
    tempRightSize = tmpRight.size()-1;
    while(currentRight <= tempRightSize)
    {
        integerVector[currentPos] = tmpRight[currentRight];
        currentRight++;
        currentPos++;
    }
}
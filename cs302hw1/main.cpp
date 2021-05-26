/*
Name: Cicelia Siu
Class: CS 302
Assignment 1 - CS 202 Review - Make a 15 Puzzle

main.cpp file
*/


#include "ass01.h"
using namespace std;

int main()
{
    //whole game declaration
    bool gameEnd = 0;
    do
    {  
        //get file declarations
        int intInFile;
        string inFile;
        ifstream input;
        //choice declarations
        string choice;
        LL<int>::iterator it;
        LL<int>::iterator zeroIt;
        int zeroRow, zeroColumn;
        int swapItem;
        int checkWonInt;
        bool win = 0;
        
        
        
        //get file and input into boards
        cout << endl <<"Enter Puzzle File: ";
        cin >> inFile;
        input.open (inFile);
        while (input.fail())
        {
            cout << "Enter Puzzle File: ";
            cin >> inFile;
            input.open (inFile);
        }
        LL<int> board[4];
        if (input.is_open())
        {
            for (int row = 0; row <4; row++)
            {
                for (int column = 0; column<4 ; column++)
                {
                    input >> intInFile;
                    board[row].tailInsert(intInFile);
                }
            }
        }
        input.close();
    
    //print first board and find where 0 is
        cout << endl << endl;
        for (int row = 0; row<4 ; row++)
        {
            it = board[row].begin();
            for (int column = 0; column<4 ; column++)
            {
                if (*it == 0)
                {
                    cout << "-"; 
                    zeroColumn = column;    // save row and column of zero
                    zeroRow = row;
                    zeroIt = it;        //copies it's item and current into zeroIt
                }
                else
                {
                    cout<<*it;
                }
                cout<< "\t";
                it++;
            }
            cout << endl;
        }
        do
        {
            // ask and make decision
            cout << "Please  make  your  choice , (L)eft , (R)ight , (U)p, (D)own , (Q)uit: ";
            cin >> choice;
            if (choice == "q"||choice == "Q")
            {
                cout << endl <<"Quitter.... " <<endl;
                return 0;
            }
            
            if (choice == "u"||choice == "U")
            {
                //switch with the one below
                if (zeroRow+1 > 3)
                {
                    cout << "There is nothing below this row." << endl;
                }
                //save the item/element of the one below 0
                else
                {
                    it = board[zeroRow+1].begin();
                    for (int i = 0; i < zeroColumn; i++)
                    {
                        it++;
                    }
                    swapItem = *it;
                    //update
                    board[zeroRow].update(zeroIt, swapItem);
                    board[zeroRow+1].update(it, 0);
                }
            }
            else if (choice == "d"||choice == "D")
            {
                //switch with the one above
                if (zeroRow-1 < 0)
                {
                    cout << "There is nothing above this row." << endl;
                }
                //save the item/element of the one above 0
                else
                {
                    it = board[zeroRow-1].begin();
                    for (int i = 0; i < zeroColumn; i++)
                    {
                        it++;
                    }
                    swapItem = *it;
                    //update/swap
                    board[zeroRow].update(zeroIt, swapItem);
                    board[zeroRow+1].update(it, 0);
                }
            }
            else if (choice == "l"||choice == "L")
            {
                //switch with the one to the right
                if (zeroColumn+1 > 3)
                {
                    cout << "There is nothing to the right of this column."<< endl;
                }
                //save the item/element of the one right of 0
                else
                {
                    it = board[zeroRow].begin();
                    for (int i = 0; i < zeroColumn+1; i++)
                    {
                        it++;
                    }
                    swapItem = *it;
                    //update/swap
                    board[zeroRow].update(zeroIt, swapItem);
                    board[zeroRow].update(it, 0);
                }
            }
            else if (choice == "r"||choice == "R")
            {
                //switch with the one to the left
                if (zeroColumn-1 < 0)
                {
                    cout << "There is nothing to the left of this column."<< endl;
                }
                //save the item/element of the one right of 0
                else
                {
                    it = board[zeroRow].begin();
                    for (int i = 0; i < zeroColumn-1; i++)
                    {
                        it++;
                    }
                    swapItem = *it;
                    //update/swap
                    board[zeroRow].update(zeroIt, swapItem);
                    board[zeroRow].update(it, 0);
                }
            }
            else
            {
                cout << "Invalid Selection!" << endl;
            }
        
        //print board and save where 0 is
            cout << endl;
            for (int row = 0; row<4 ; row++)
            {
                it = board[row].begin();
                for (int column = 0; column<4 ; column++)
                {
                    if (*it == 0)
                    {
                        cout << "-"; 
                        zeroColumn = column;    // save row and column of zero
                        zeroRow = row;
                        zeroIt = it;        //copies it's item and current into zeroIt
                    }
                    else
                    {
                        cout<<*it;
                    }
                    cout<< "\t";
                    it++;
                }
                cout << endl;
            }
            
            if (zeroColumn == 3 && zeroRow == 3)
            {
                //check if game has been game won
                checkWonInt = 1;
                for (int row = 0; row<4 ; row++)
                {
                    it = board[row].begin();
                    for (int column = 0; column<4 ; column++)
                    {
                        if (checkWonInt == *it || checkWonInt == 16)
                        {
                            checkWonInt++;
                            it++;
                            win = 1;
                        } 
                        else
                        {
                            win = 0;
                        }
                        
                    }
                }
            }
            
        } while(!win);
        
        do
        {
            cout << "Would you like to play again (y/n)? : ";
            cin >> choice;
            if (choice == "n" || choice == "N")
            {
                return 0;
            }
            else if (choice == "y" || choice == "Y")
            {
                break;
            }
            else
            {
                cout << "Invalid Selection";
                return 0;
            }
        } while (choice != "y" || choice != "Y");
    }while (gameEnd==0);
    
    return 0;
}
    
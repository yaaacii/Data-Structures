/*
Name: Cicelia Siu
Class: CS 302.1003
Assignment 2 - CS 202 Review - Sudoku Solver using backtracking recursion

*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void printBoard(int board[][9])
{
    for (int row = 0; row < 9; row++)
    {
        if (row%3 == 0)
        {
            cout <<" ---------------------------------- " << endl;
        }
        for (int column = 0; column < 9; column++)
        {
            if (column%3 == 0){
                cout << "|  ";
            }
            if (board[row][column] == 0)
            {
                cout << "-  ";
            }
            else
            {
                cout << board[row][column] << "  ";
            }
        }
         cout << "|" <<endl;
    }
    cout <<" ---------------------------------- " << endl;
}

bool isFound (int board [][9], int row, int column, int checker)
{
    //check same row
    for (int columnCheckIndex = 0; columnCheckIndex < 9; columnCheckIndex++)
    {
        if(board[row][columnCheckIndex] == checker)
        {
            return true; // one in the same row is found so break for loop
        }
    }
    //check same column
    for (int rowCheckIndex = 0; rowCheckIndex < 9; rowCheckIndex++)
    {
        if(board[rowCheckIndex][column] == checker)
        {
            return true; // one in the same column is found so break for loop
        }
    }
    //check same section
    int rowSectionStart = row % 3;
    rowSectionStart = row - rowSectionStart;           //get where the row of the section starts (0,3,6)
    int columnSectionStart = column % 3;
    columnSectionStart = column - columnSectionStart;    //get where the column of the section starts (0,3,6)

    for (int rowIndex = 0; rowIndex < 3; rowIndex++)
    {
        for (int columnIndex = 0; columnIndex < 3; columnIndex++)
        {
            if(board[rowIndex+rowSectionStart][columnIndex +columnSectionStart] == checker)     //add section start to indices
            {
                return true; // one in the same section is found 
            }
        }
    }
    //if not found, isFound is false
    return false;
        
}


bool sudoku (int board [][9], int row, int column /*can add more if needed*/)
{
    int numToCheck = 0;
    //if row 9 is hit then the board is complete
    if (row == 9)
    {
        return true;
    }
    //if not blank go to next cell
    if (board[row][column] != 0)
    {
        if (column == 8)
        {
            return sudoku(board, row+1, 0);
        } 
        else
        {
            return sudoku(board, row, column+1);
        }
    }
    //otherwise fill the blank
    else
    {
        for (numToCheck = 1; numToCheck < 10; numToCheck++)
        {
            //check if number is in row, column, or section. if found, go to next number, if not, assign
            if (!isFound(board, row, column, numToCheck))
            {
                //once found one thats not in the same row, column, section assign it to board
                board[row][column] = numToCheck;
                //recursive call until board is filled
                if(sudoku(board, row, column))
                {
                    return true;
                }
                //break;  //from for loop of 1-9
            }
            board[row][column] = 0;     // will be unassigned until a number works
        } 
        //return false and backtrack to the previous cell
        return false;      
    }
}

int main()
{
    bool keepGoing = 1;
    string no = "NO";
    //get file declarations
    string inFile;
    ifstream input;
    //array declarations
    int sudokuBoard[9][9];

    do 
    {
        //get sudoku board file and put into sudoku array
        cout << endl << "Enter initial sudoku board file: ";
        cin >> inFile;
        input.open(inFile);
        while (input.fail())
        {
            //if NO is entered, end main
            if (inFile.compare(no) == 0)
            {
                return 0;
            }
            cout << endl << "Enter initial sudoku board file: ";
            cin >> inFile;
            input.open(inFile);
        }
        for (int row = 0; row < 9; row++)
        {
            for (int column = 0; column < 9; column++)
            {
                input >> sudokuBoard[row][column];
            }
        }
        input.close();

        // print initial board
        cout << endl <<"Inital board read in\n" << endl;
        printBoard(sudokuBoard);

        //solve using backtracking recursion
        if (sudoku(sudokuBoard, 0, 0) == true){
            cout<< "\n\nSudoku Puzzle Solved\n\n" <<endl;
            printBoard(sudokuBoard);
        }
        else
        {
            cout << "Can't find a solution"<<endl;
        }
    } while (keepGoing);
}
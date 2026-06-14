/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
#include <fstream>    //File I/O Library
using namespace std;

//User libraries
#include "Player.h"
#include "Board.h"
#include "Square.h"
#include "City.h"
#include "Railroad.h"
#include "Utility.h"
#include "ActionSpace.h"


//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void writeToFile(); //Function to write data to an external binary file for testing purposes
Board readFromFile(); //Function to read the board data from an external binary file and initialize the board with that data

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    
    //Initialize Variables
    cout << "This program demonstrates how to write data to an external binary file in C++." << endl;

    //Mapping Process -> Inputs to Outputs
    writeToFile(); //Write data to an external binary file for testing purposes

    //Display Inputs/Outputs
    cout << "Data has been written to the file." << endl;

    Board board; //Create a Board object
    board = readFromFile(); //Initialize the board by reading data from the file
    for (int i = 0; i < 40; i++) {
        Square* square = board.getSquare(i);
        if (square != nullptr) {
            square->toString(); //Print the details of each square on the board
        } else {
            cout << "Square " << i << ": [Error reading square data]" << endl;
        }
    }
    //Exit the program
    return 0;
};
Board readFromFile() {
    //Create an input file stream
    ifstream inFile;

    inFile.open("BoardData.bin", ios::in | ios::binary); //Open the file for reading in binary mode

    //Read data from the file
    Board board;
    inFile.read(reinterpret_cast<char*>(&board), sizeof(Board)); //Read the board data from the file

    //Close the file
    inFile.close();
    return board;
}
void writeToFile(){
    //Create an output file stream
    ofstream outFile;

    outFile.open("BoardData.bin", ios::out | ios::binary); //Open the file for writing in binary mode

    //Write data to the file
    Board board;
    
    board.initializeBoardManually();

    outFile.write(reinterpret_cast<char*>(&board), sizeof(Board)); //Write the board data to the file


    //Close the file
    outFile.close();
}
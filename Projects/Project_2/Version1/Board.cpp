/*
Filename:  Board.cpp
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class implementation file
*/

//System libraries
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

//User libraries
#include "Board.h"
#include "Square.h"
#include "Property.h"

// ============ Constructors ============

Board::Board() {
    index = 0;
    initializeBoard();
}

// ============ Destructors ============

Board::~Board() {
    // Cleanup if needed (Squares are static array, so no dynamic memory to delete)
}

// ============ Accessors ============

Square* Board::getSquare(int idx) const {
    if (idx < 0 || idx >= 40) {
        return nullptr; // Return null if index is out of bounds
    }
    return squares_array[idx];
}

// ============ Member Functions ============

void Board::initializeBoard() {
    for (int i = 0; i < 40; i++) {
        squares_array[i] = readSquareFromFile("board_data.bin", i); // Read each square from the file
    }

}
Square* Board::readSquareFromFile(string fileName, int id){
    //Open the file for reading in binary mode
    fstream inFile;
    inFile.open(fileName, ios::in | ios::binary); //Open the file for reading in binary mode

    Square* sq = new Property; // Allocate memory for the Square object at the specified index

    long cursor = 0L;

    cursor = id * sizeof(Property); //Calculate the byte offset for the board with the given ID

    inFile.seekg(cursor, ios::beg); //Move the file pointer to the correct position
    inFile.read(reinterpret_cast<char*>(sq), sizeof(Property)); //Read the square data into the current Board object
    inFile.close();

    //inFile.close(); // Already closed above
    return sq;
}

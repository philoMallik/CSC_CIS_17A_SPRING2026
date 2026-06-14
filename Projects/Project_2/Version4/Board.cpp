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
#include "City.h"
#include "Railroad.h"
#include "Utility.h"
#include "ActionSpace.h"

// ============ Constructors ============

Board::Board() {
    index = 0;
    for (int i = 0; i < 40; i++) {
        squares_array[i] = nullptr; // Initialize all squares to nullptr
    }
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

void Board::setSquare(int idx, Square* square) {
    if (idx >= 0 && idx < 40) {
        squares_array[idx] = square;
    }
}
void Board::setIndex(int newIndex) {
    if (newIndex >= 0 && newIndex < 40) {
        index = newIndex;
    }
}

int Board::getIndex() const {
    return index;
}

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

void Board::initializeBoardManually() {
    //city = new city(index, name, type, price, mortgageValue, colourGroup, houseCost, rent0, rent1, rent2, rent3, rent4)
    squares_array[0] = new ActionSpace(39, "Go", 0);
    squares_array[1]  = new City(0, "Mediterranean Avenue", 1, 60, 30, 1, 50, 2, 30, 90, 160, 250);
    squares_array[2]  = new ActionSpace(1, "Community Chest", 0);
    squares_array[3]  = new City(2, "Baltic Avenue", 1, 60, 30, 1, 50, 4, 60, 180, 320, 450);
    squares_array[4]  = new ActionSpace(3, "Income Tax", 0);
    squares_array[5]  = new Railroad(4, "Reading Railroad");
    squares_array[6]  = new City(5, "Oriental Avenue", 1, 100, 50, 2, 50, 6, 90, 270, 400, 550);
    squares_array[7]  = new ActionSpace(6, "Chance", 0);
    squares_array[8]  = new City(7, "Vermont Avenue", 1, 100, 50, 2, 50, 6, 90, 270, 400, 550);
    squares_array[9]  = new City(8, "Connecticut Avenue", 1, 120, 60, 2, 50, 8, 100, 300, 450, 600);
    squares_array[10] = new ActionSpace(9, "Just Visiting / In Jail", 0);
    squares_array[11] = new City(10, "St. Charles Place", 1, 140, 70, 3, 100, 10, 150, 450, 625, 750);
    squares_array[12] = new Utility(11, "Electric Company");
    squares_array[13] = new City(12, "States Avenue", 1, 140, 70, 3, 100, 10, 150, 450, 625, 750);
    squares_array[14] = new City(13, "Virginia Avenue", 1, 160, 80, 3, 100, 12, 180, 500, 700, 900);
    squares_array[15] = new Railroad(14, "Pennsylvania Railroad");
    squares_array[16] = new City(15, "St. James Place", 1, 180, 90, 4, 100, 14, 200, 550, 750, 950);
    squares_array[17] = new ActionSpace(16, "Community Chest", 0);
    squares_array[18] = new City(17, "Tennessee Avenue", 1, 180, 90, 4, 100, 14, 200, 550, 750, 950);
    squares_array[19] = new City(18, "New York Avenue", 1, 200, 100, 4, 100, 16, 220, 600, 800, 1000);
    squares_array[20] = new ActionSpace(19, "Free Parking", 0);
    squares_array[21] = new City(20, "Kentucky Avenue", 1, 220, 110, 5, 150, 18, 250, 700, 875, 1050);
    squares_array[22] = new ActionSpace(21, "Chance", 0);
    squares_array[23] = new City(22, "Indiana Avenue", 1, 220, 110, 5, 150, 18, 250, 700, 875, 1050);
    squares_array[24] = new City(23, "Illinois Avenue", 1, 240, 120, 5, 150, 20, 300, 750, 925, 1100);
    squares_array[25] = new Railroad(24, "B&O Railroad");
    squares_array[26] = new City(25, "Atlantic Avenue", 1, 260, 130, 6, 150, 22, 330, 800, 975, 1150);
    squares_array[27] = new City(26, "Ventnor Avenue", 1, 260, 130, 6, 150, 22, 330, 800, 975, 1150);
    squares_array[28] = new Utility(27, "Water Works");
    squares_array[29] = new City(28, "Marvin Gardens", 1, 280, 140, 6, 150, 24, 360, 850, 1025, 1200);
    squares_array[30] = new ActionSpace(29, "Go To Jail", 0);
    squares_array[31] = new City(30, "Pacific Avenue", 1, 300, 150, 7, 200, 26, 390, 900, 1100, 1275);
    squares_array[32] = new City(31, "North Carolina Avenue", 1, 300, 150, 7, 200, 26, 390, 900, 1100, 1275);
    squares_array[33] = new ActionSpace(32, "Community Chest", 0);
    squares_array[34] = new City(33, "Pennsylvania Avenue", 1, 320, 160, 7, 200, 28, 450, 1000, 1200, 1400);
    squares_array[35] = new Railroad(34, "Short Line");
    squares_array[36] = new ActionSpace(35, "Chance", 0);
    squares_array[37] = new City(36, "Park Place", 1, 350, 175, 8, 200, 35, 500, 1100, 1300, 1500);
    squares_array[38] = new ActionSpace(37, "Luxury Tax", 0);
    squares_array[39] = new City(38, "Boardwalk", 1, 400, 200, 8, 200, 50, 600, 1400, 1700, 2000);
}
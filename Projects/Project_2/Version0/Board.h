/*
Filename:  Board.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef BOARD_H
#define BOARD_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Square.h"


class Board;  //Forward declaration

class Board{
  private:
    Square* squares_array[40]; //array to hold the spaces on the board, size 40
    int index; //to keep track of the current space index for players

  public:
    //constructors
    Board(); //Default constructor
    
    //destructors
    ~Board();

    //Accessors
    Square* getSquare(int index) const; //function to get the Square object at a specific index on the board

    //Mutators

    //Operator overloads

    //Member functions
    void initializeBoard(); //function to initialize the board with the appropriate spaces and properties
    Square* readSquareFromFile(string fileName, int id); //function to read the board data from an external binary file and initialize the board with that data
};

#endif  // BOARD_H
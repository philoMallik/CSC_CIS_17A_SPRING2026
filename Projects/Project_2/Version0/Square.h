/*
Filename:  Square.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef SQUARE_H
#define SQUARE_H

//System libraries
#include  <iostream>
using namespace std;

class Player;

class Square;  //Forward declaration

class Square{
  private:
    //Private variables defined here
    int index; //Unique ID for each space on the board (0-39)
    char name[50];


  public:
    //constructors
    Square(); //Default constructor

    //destructors
    ~Square();
    
    //Accessors
    int getIndex() const;
    const char* getName() const;

    //Mutators
    void setIndex(int newIndex); //function to set the index of the square
    void setName(const char* newName); //function to set the name of the square

    //Operator overloads

    //Member functions
    void toString() const; //function to print the details of the square
    virtual void onLand(Player* player) = 0; //function to handle the action when a player lands on the square (to be overridden by derived classes)
};

#endif  // SQUARE_H
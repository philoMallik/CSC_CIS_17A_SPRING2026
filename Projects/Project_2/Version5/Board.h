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
#include "Deck.h"
#include "Card.h"


class Board;  //Forward declaration

class Board{
  private:
    Square* squares_array[40]; //array to hold the spaces on the board, size 40
    int index; //to keep track of the current space index for players
    Deck<Card> chanceDeck; //Pointer to the Chance deck, used to draw a card when a player lands on a Chance space
    Deck<Card> communityChestDeck; //Pointer to the Community Chest deck, used to draw

  public:
    //constructors
    Board(); //Default constructor
    
    //destructors
    ~Board();

    //Accessors
    Square* getSquare(int index) const; //function to get the Square object at a specific index on the board

    //Mutators
    void setSquare(int index, Square* square); //function to set a Square object at a specific index on the board
    void setIndex(int newIndex); //function to set the current space index for players
  
    int getIndex() const; //function to get the current space index for players
    //Operator overloads

    //Member functions
    void initializeBoardManually(); //function to initialize the board with the appropriate spaces
    void initializeDeckManually(); //function to initialize the Chance and Community Chest decks with the appropriate cards

  };

#endif  // BOARD_H
/*
Filename:  Card.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef CARD_H
#define CARD_H

//System libraries
#include  <iostream>
using namespace std;

class Card;  //Forward declaration

class Card{
  private:
    //Private variables defined here
    char description[100];
    int actionType; //action type of the card, used to determine the effect of the card when drawn by a player
                    /*  0 for Move to a specific square
                        1 for Move forward/backward a certain number of spaces
                        2 for Pay or receive money
                        3 for Get out of Jail Free
                        4 for Go to Jail
                        5 for Advance to Go (Collect $200)
                    */
    int value; //Value associated with the card, used to determine the amount of money to pay/receive or the number of spaces to move, etc.
  public:
    //constructors
    Card(); //Default constructor required for Deck<Card> storage
    Card(const char* description, int actionType, int value); //Constructor to initialize the card with a description, action type, and value

    //destructors
    ~Card(); //Destructor

    //Accessors
    const char* getDescription() const;
    int getActionType() const;
    int getValue() const;

     //Mutators
    
    //Mutators

    //Operator overloads

    //Other functions

};

#endif  // CARD_H
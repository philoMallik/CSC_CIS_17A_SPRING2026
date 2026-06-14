/*
Filename:  ActionSpace.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef ACTIONSPACE_H
#define ACTIONSPACE_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Square.h"
#include "Player.h"

class ActionSpace;  //Forward declaration

class ActionSpace : public Square { //Inherit from Square class
  private:
    //Private variables defined here
    int type; //Type of action space
    /*  0 for Go
        1 for Chance
        2 for Community Chest
        3 for Income Tax
        4 for Luxury Tax
        5 for Free Parking
        6 for Go To Jail
    */
    char name[50]; //Name of the action space

    void onGo(Player* player); //function to handle the action when a player lands on Go
    void onChance(Player* player); //function to handle the action when a player lands on Chance
    void onCommunityChest(Player* player); //function to handle the action when a player lands on Community Chest
    void onIncomeTax(Player* player); //function to handle the action when a player lands on Income Tax
    void onLuxuryTax(Player* player); //function to handle the action when a player lands
    void onGoToJail(Player* player); //function to handle the action when a player lands on Go To Jail

  public:
    //constructors
    ActionSpace(int id, const char* name, int type); //Constructor to initialize the action space with a specific type
    
    //Accessors
    int getType() const;
    const char* getName() const;

    //Mutators
    void setName(const char* newName); //function to set the name of the action space

    //Operator overloads

    //Member functions
    void onLand(Player* player); //function to handle the action when a player lands on the action space (e.g., draw a card, pay tax, etc.)
    void toString() const; //function to print the details of the action space

};

#endif  // ACTIONSPACE_H
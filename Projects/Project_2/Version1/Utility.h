/*
Filename:  Utility.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef UTILITY_H
#define UTILITY_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Property.h"

class Utility;  //Forward declaration

class Utility : public Property { //Inherit from Property class
  private:
    //Private variables defined here
    int rentMultiplier[2]; //Rent multiplier for utilities, used to calculate rent based on the number of utilities owned by the player


  public:
    //constructors
    Utility(int index, char name[]); //Constructor
    
    //Accessors
    int getRentMultiplier(int index) const; //function to get the rent multiplier for the utility
    
    //Mutators

    //Operator overloads

    //Member functions
    int  calculateRent(Player* player, int diceRoll); //function to calculate the rent based on the number of utilities owned by the player and the dice roll, and charge the player accordingly

    void toString() const; //function to print the details of the utility
    void onLand(Player* player, int diceRoll); //function to handle the action when a player lands on the utility (e.g., buy property, pay rent, etc.)

};

#endif  // UTILITY_H
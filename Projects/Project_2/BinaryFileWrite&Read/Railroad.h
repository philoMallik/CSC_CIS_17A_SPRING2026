/*
Filename:  Railroad.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef RAILROAD_H
#define RAILROAD_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Property.h"

class Railroad;  //Forward declaration

class Railroad : public Property { //Inherit from Property class
  private:
    //Private variables defined here
    int rent[4]; //Rent of the railroad. The rent increases based on the number of railroads owned by the player. 
                 //rent[0] is the rent with 1 railroad, rent[1] is the rent with 2 railroads, and so on up to rent[3] for owning all 4 railroads.
  public:
    //constructors
    Railroad(int index, const char* name); //Constructor
    //Accessors
    
    //Mutators

    //Operator overloads

    //Member functions
    int  calculateRent(); //function to calculate the rent based on the number of railroads owned by the player and charge the player accordingly
    void toString() const; //function to print the details of the railroad
    void onLand(Player* player); //function to handle the action when a player lands on the railroad (e.g., buy property, pay rent, etc.)

};

#endif  // RAILROAD_H
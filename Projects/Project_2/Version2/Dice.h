/*
Filename:  Dice.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef DICE_H
#define DICE_H

//System libraries
#include  <iostream>
using namespace std;

class Dice;  //Forward declaration

class Dice{
  private:
    //Private variables defined here
    int die1;
    int die2;
    int consecutiveDoubles; //Counter to track the number of consecutive doubles rolled by a player, resets to 0 when a non-double is rolled or when the player goes to jail after rolling three doubles in a row

  public:
    //constructors
    Dice(); //Default constructor
    
    //destructors
    ~Dice();

    //Accessors
    int getDie1() const;
    int getDie2() const;
    int getDice1() const;
    int getDice2() const;
    int getConsecutiveDoubles() const;
    int getTotalRoll() const; //Function to get the total value of the dice roll (die1 + die2)

    //Mutators

    //Operator overloads

    //Member functions
    void Roll(); //function to simulate rolling two six-sided dice and return the total roll value (2-12), also updates the consecutiveDoubles counter based on whether the roll is a double or not
    
    bool isDouble() const; //function to check if the current roll is a double (die1 == die2) and return true if it is, false otherwise
    bool rolledThreeDoubles() const; //function to check if the player has rolled doubles three times in a row (consecutiveDoubles == 3) and return true if they have, false otherwise
    void resetConsecutiveDoubles(); //function to reset the consecutiveDoubles counter to 0, typically called when a player rolls a non-double or goes to jail after rolling three doubles in a row

};

#endif  // DICE_H
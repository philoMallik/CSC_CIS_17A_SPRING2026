/*
Filename:  Property.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef PROPERTY_H
#define PROPERTY_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Square.h"

class Player;

class Property;  //Forward declaration

class Property : public Square { //Inherit from Square class
  private:
    //Private variables defined here
    int type; //Type of property (1 for City, 2 for Railroad, 3 for Utility)
    int price; //Price of the property
    int mortgageValue; //Mortgage value of the property
    Player* ownerID; //ID of the player who owns the property, -1 if unowned
    int baseRent; //Base rent of the property, used for calculating rent based on the number of houses/hotels for cities and the number of properties owned for railroads/utilities
    bool isMortgaged; //Flag to indicate if the property is currently mortgaged

  public:
    //constructors
    Property(); //Default constructor

    //destructors
    ~Property();

    //Accessors
    int getType() const;
    int getPrice() const;
    Player* getOwnerID() const; //function to get the ID of the player who owns the property, returns -1 if unowned
    int getMortgageValue() const; //function to get the mortgage value of the property
    bool getIsMortgaged() const; //function to check if the property is currently
    virtual int getHouseCost() const; //function to get the cost of building a house on the property, returns 0 for non-city properties

    //Mutators
    void setType(int newType); //function to set the type of the property
    void setPrice(int newPrice); //function to set the price of the property
    void setMortgageValue(int newMortgageValue); //function to set the mortgage value of the property
    void setOwner(Player* newOwner); //function to set the owner of the property, updates ownerID to the new owner's ID
    void setBaseRent(int newBaseRent); //function to set the base rent of the property
    
    //Operator overloads

    //member functions
    virtual void toString() const; //function to print the details of the property
    virtual void onLand(Player* player); //function to handle the action when a player lands on the property (e.g., buy property, pay rent, etc.)
    virtual int calculateRent(Player* player) const; //function to calculate the rent based on the type of property and the player's ownership status, returns the rent amount that the player needs to pay if they land on the property
    void mortgageProperty(); //function to mortgage the property
    void unmortgageProperty(); //function to unmortgage the property
    virtual bool canUpgrade() const; //function to check if the property can be upgraded (only returns true for cities that are not already at max level)
    virtual void BuildHouse(); //function to build a house on the property, increases the level of the property and updates rent accordingly (only applicable for cities)
};

#endif  // PROPERTY_H
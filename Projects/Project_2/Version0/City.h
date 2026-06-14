/*
Filename:  City.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef CITY_H
#define CITY_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Property.h"
#include "Player.h"

class City;  //Forward declaration

class City : public Property { //Inherit from Property class
  private:
    //Private variables defined here
    int colorGroup;     //Color group of the city (1 for Brown, 2 for Light Blue, 3 for Pink, 4 for Orange, 5 for Red, 6 for Yellow, 7 for Green, 8 for Dark Blue)
    int rent[5];        //Rent of the city. The rent increases based on the number of houses/hotels built on the city. 
                        //rent[0] is the rent with no houses, rent[1] is the rent with 1 house, and so on up to rent[4] for a hotel.
    int houseCount;      //Number of houses currently built on the city (0-4, where 4 represents a hotel)
    int houseCost;      //Cost to build a house on the city
    int numHouses;      //Number of houses currently built on the city (0-4, where 4 represents a hotel)

  public:
    //constructors
    City(int index, char name[], int type, int price, int mortgageValue, int colourGroup, int houseCost, int rent0, int rent1, int rent2, int rent3, int rent4);

    //destructors
    ~City();

    //Accessors
    int getColorGroup() const;
    int getHouseCost() const;
    int getNumHouses() const;
    int getRent(int numHouses) const; //function to get the current rent based on the number of houses/hotels built on the city
    
    //Mutators

    //Operator overloads

    //Member functions
    void toString() const; //function to print the details of the city
    void buildHouse(); //function to build a house on the city, increases houseCount by 1 and updates rent accordingly
    void sellHouse(); //function to sell a house from the city, decreases houseCount by 1 and updates rent accordingly
    int calculateRent() const; //function to calculate the rent based on the number of houses/hotels and return the rent amount
    void onLand(Player* player); //function to handle the action when a player lands on the city (e.g., buy property, pay rent, etc.)
};

#endif  // CITY_H

#ifndef Cities_H
#define Cities_H

#include <iostream>
using namespace std;

struct City{
    int id; //Unique ID for each property(0-21), railroad(22-25), and utility
    int boardPosition; //Position on the board (0-39)
    string name;
    int baseRent;
    int currentRent;     
    int houseRent[5];   //Rent with 0-4 houses and hotel
    int cost;
    int ownerIndex;
    int upgradeLevel;  //0 for no buildings, 1-4 for houses, 5 for hotel
                        //if railroad or utility, buildingLevel represents the number of railroads/utilities owned by the player (1-4 for railroads, 1-2 for utilities)
    int groupMinimumUpgradeLevel; //Minimum upgrade level required for all properties in the group to be upgraded (0-4 for properties, 1-4 for railroads, 1-2 for utilities)                    
    int groupID; //ID for color group (0-7 for properties, 8 for railroads, 9 for utilities)
/*
    0 for Brown
    1 for Light Blue
    2 for Pink
    3 for Orange
    4 for Red
    5 for Yellow
    6 for Green
    7 for Dark Blue
    8 for Railroads
    9 for Utilities
*/    
    int upgradeCost[2];//Cost to build houses (index 0) and hotels (index 1)
    bool isOwned;
    bool isMortgaged;    
};

#endif
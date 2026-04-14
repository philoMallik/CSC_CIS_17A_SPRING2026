
#ifndef Board_H
#define Board_H

#include <iostream>
using namespace std;

struct Board{
    //int id; //Unique ID for each space on the board (0-39)
    string name;
    int propertyID; //ID of the property associated with this space (if applicable), -1 if not a property
    int position[4]; //location where a player can be
    int type;

/*  -2 for bunkrupt
    -1 for in jail prisioner
    0 for Go
    1 for Cities
    2 for Railroads
    3 for Utilities
    4 for Chance
    5 for Community Chest
    6 for Income Tax (200)
    7 for Luxury Tax (100)
    8 for Jail visiting
    9 for Free Parking
    10 for Go To Jail
*/
/*
    bool isGo;
    bool isJail;
    bool isFreeParking;
    bool isGoToJail;
    bool isCity;
    bool isRailroad;
    bool isUtility;
    bool isChance;
    bool isCommunityChest;
*/
};

#endif
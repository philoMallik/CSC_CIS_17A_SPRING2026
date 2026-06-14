
#ifndef Players_H
#define Players_H

#include <iostream>
using namespace std;

struct Player{
    int id;
    string name;
    int token;           //ID for the player's token 
    int balance;          
    int position;        //0-39 for board positions
    int* citiesOwned;    //Array of property IDs owned by the
    int* railroadsOwned; //Array of railroad IDs owned by the player 
    int* utilitiesOwned; //Array of utility IDs owned by the player
    int* groupOwned;     //Array to track how many properties in each color group the player owns (index 0-7 for color groups, 8 for railroads, 9 for utilities)
    int numRailroads;     //Number of railroads owned (for rent calculation)
    int numUtilities;     //Number of utilities owned (for rent calculation)
    int numProperties;   //Number of properties owned
    bool inJail;
    int netWorth;//Calculated as balance + value of owned properties if liquidated
    bool isBankrupt;
};

#endif
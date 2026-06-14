
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
    bool* groupOwned;     //Array to track how many properties in each color group the player owns (index 0-7 for color groups, 8 for railroads, 9 for utilities)
    int* upgradesOwned;   //Array to track the upgrade level of each property owned by the player (first value for houses, second value for hotels)
    int numCities;      //Number of cities owned (for tracking the size of the citiesOwned array)
    int numRailroads;     //Number of railroads owned (for rent calculation)
    int numUtilities;     //Number of utilities owned (for rent calculation)
    int numProperties;   //Number of properties owned
    bool inJail;
    int jailTurns;       //Number of turns the player has been in jail
    int netWorth;//Calculated as balance + value of owned properties if liquidated
    bool isBankrupt;
};

#endif
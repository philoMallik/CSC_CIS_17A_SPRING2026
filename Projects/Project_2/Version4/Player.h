/*
Filename:  Player.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef PLAYER_H
#define PLAYER_H

//System libraries
#include  <iostream>
using namespace std;

class Property;
class Board;

class Player;  //Forward declaration

class Player{
  private:
    //Private variables defined here
    char name[50];
    int id;
    int token;           //ID for the player's token
    int balance;
    int position;        //0-39 for board positions
    Property* propertiesOwned[28]; //Array of pointers to properties owned by the player, size 28 to accommodate all properties in the game
    int numberOfPropertiesOwned; //To keep track of how many properties the player owns
    bool inJail;
    int jailTurns;       //Number of turns the player has been in jail
    int hasGetOutOfJailCard; //Number of Get Out of Jail Free cards the player has (0, 1, or 2)
    bool bankrupt;       //Flag to indicate if the player is bankrupt

  public:
    //constructors
    Player(); //Default constructor
    Player(const char* playerName, int playerId, int playerToken); //Constructor with parameters to initialize the player's name, ID, and token

    //Accessors
    char* getName() const;
    int getId() const;
    int getToken() const;
    int getBalance() const;
    int getPosition() const;
    Property* getPropertiesOwned(int index) const;
    bool isInJail() const;
    int getJailTurns() const;
    int getHasGetOutOfJailCard() const;
    bool isBankrupt() const; //function to check if the player's balance is less than or equal to 0, indicating bankruptcy

    //Mutators
    void setHasGetOutOfJailCard(int count); //function to set the number of Get Out of Jail Free cards the player has
    void setBalance(int newBalance); //function to set the player's balance to a specific amount

    //Operator overloads
    void incrementJailTurns(); //function to increment the number of turns the player has been in jail by 1
    Player& operator+=(int amount); //Overload the += operator to add a certain amount to the player's balance
    Player& operator-=(int amount); //Overload the -= operator to deduct a certain amount from the player's balance

    //Member functions
    void toString() const; //function to print the details of the player

    void move(int spaces); //function to move the player a certain number of spaces on the board, updates position accordingly and handles passing Go
    void moveTo(int newPosition); //function to move the player directly to a specific position on the board, updates position accordingly and handles passing Go if necessary
    
    void goToJail(); //function to send the player to jail, updates position to jail and sets inJail flag to true
    void getOutOfJail(); //function to get the player out of jail, updates inJail flag to false and resets jailTurns to 0
    void useGetOutOfJailCard(); //function to use a Get Out of Jail Free card, updates hasGetOutOfJailCard flag to false and gets the player out of jail

    void buyProperty(Property* property); //function to buy a property, updates balance and adds the property to propertiesOwned
    void receiveProperty(Property* property); //function to receive a property (e.g., from a trade or bankruptcy transfer), adds the property to propertiesOwned without deducting balance 

    void UpgradeProperty(Board& board); //function to upgrade a property with a house or hotel, updates balance and the property's rent accordingly
    void mortgageProperty(Board& board); //function to mortgage a property, updates balance and the property's rent accordingly
    void unmortgageProperty(Board& board); //function to unmortgage a property, updates balance and the property's rent accordingly
    void tradeProperty(Player* plyrs, Board& board); //function to trade properties with another player, updates both players' propertiesOwned and balances accordingly
    void declareBankruptcy(); //function to declare bankruptcy, sets balance to 0 and clears propertiesOwned
    
    void BankruptcyTransfer(Player* creditor); //function to transfer all properties and remaining balance to the creditor player when declaring bankruptcy

    //void addBalance(int amount); //function to add a certain amount to the player's balance
    //void deductBalance(int amount); //function to deduct a certain amount from the player's balance


};

#endif  // PLAYER_H
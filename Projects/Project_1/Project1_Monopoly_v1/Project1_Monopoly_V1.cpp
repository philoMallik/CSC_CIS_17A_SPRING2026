/*
Author: Philopatair Mallik
Date: 04/01/2026
purpose: Project 1 - Monopoly Game Simulation
*/

/*
* Version 1 - 04/01/2026
* made the menu function for the player's turn which will allow them to choose their action during their turn (rolling dice, buying properties, upgrading properties, etc.)
* made the handleMenuChoice function which will execute the action based on the player's menu choice and will allow them to take multiple actions during their turn until they choose to end their turn or they go bankrupt or go to jail
* made the movePlayer function which simulates rolling the dice and moving the player around the board, including handling double rolls and passing Go. It also calls the locationAction function to handle the action for landing on the new position.
* made the locationAction function which will direct the flow to different functions based on the type of space the player lands on (e.g., buy property, pay rent, draw card, etc.)
* The main game loop was updated to incorporate the menu and player movement logic, allowing players to take actions and move around the board during their turns.
* made the different functions for handling the various actions a player can take during their turn (e.g., buying properties, upgrading properties, mortgaging properties, etc.) and the various actions that can occur when a player lands on a space (e.g., paying rent, drawing cards, etc.)
    * Pay rent function will handle rent payment when a player lands on an owned property, including calculating the rent based on the property's attributes and the number of houses/hotels, and transferring the money from the player to the owner.
      it will also handle tax payment when a player lands on a tax space, including calculating the tax amount and transferring the money from the player to the bank.
    * Buy property function will handle the process of buying a property when a player lands on an unowned property, including checking if the player has enough money, transferring the money from the player to the bank, and updating the property's ownership.
    * Draw Chance card function will handle drawing a Chance card and executing its effect, including moving the player to a different space, giving or taking money, etc. (will be implemented in version 2)
    * Draw Community Chest card function will handle drawing a Community Chest card and executing its effect, including moving the player to a different space, giving or taking money, etc. (will be implemented in version 2)
    
    * Money transaction functions will handle money transactions between players (e.g., rent payment, property purchase, etc.) and between players and the bank (e.g., salary collection, property purchase, etc.), including updating the players' balances and handling low balance situations (e.g., selling property, mortgaging property, declaring bankruptcy, etc.)
    * Upgrade property function will handle upgrading properties with houses and hotels, including checking for the required conditions (owning all properties in a color group, having enough money, etc.) and updating the property's attributes and the player's balance accordingly.
    * Mortgage property function will handle mortgaging properties, including calculating the mortgage value, updating the property's status, and transferring money from the player to the bank.
    * Unmortgage property function will handle unmortgaging properties, including calculating the unmortgage cost (including interest), updating the property's status, and transferring money from the player to the bank.
    * Sell property function will handle selling properties to other players or back to the bank, including updating the property's ownership and the player's balance accordingly.(will be implemented in version 2)
    * Trade property function will handle trading properties between players, including allowing players to negotiate and agree on the terms of the trade, and updating the properties' ownership and the players' balances accordingly. (will be implemented in version 2)
    * Declare bankruptcy function will handle bankruptcy declaration, including transferring the bankrupt player's assets to their creditors (other players or the bank) and removing the player from the game.
* Jail turn function will handle a player's turn when they are in jail, including allowing them to attempt to roll doubles to get out of jail, pay a fine to get out of jail, or use a Get Out of Jail Free card if they have one. (will be implemented in version 2)
* Go to Jail function will handle sending a player to jail when they land on the Go To Jail space or when they roll doubles three times in a row, including updating their position and jail status.
      also can be called from the locationAction function when a player lands on the Go To Jail space or from the movePlayer function when a player rolls doubles three times in a row.
      or from chance/community chest card effects that send the player to jail.

Next steps:
-Implement the logic for Chance and Community Chest cards, including the various effects they can have on players (moving them to different spaces, giving or taking money, etc.)
-Implement the logic for selling properties, including allowing players to sell properties to other players or back to the bank, and updating the properties' ownership and the player's balance accordingly.
-Implement the logic for trading properties between players, including allowing players to negotiate and agree on the terms of the trade, and updating the properties' ownership and the players' balances accordingly.
-Implement the logic for jail turns, including allowing players to attempt to roll doubles to get out of jail, pay a fine to get out of jail, or use a Get Out of Jail Free card if they have one.
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
#include <fstream>    //File I/O Library
using namespace std;

//User libraries
#include "Cities.h"
#include "Players.h"
#include "Board.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
int const MAX_BOARD_SPACES = 40; //Total number of spaces on the board
int const MAX_PLAYERS = 4;     //Maximum number of players
int const MAX_CITIES = 22+4+2; //22 properties + 4 railroads + 2 utilities
int const MAX_CHANCE_CARDS = 16; //Number of Chance cards
int const MAX_COMMUNITY_CHEST_CARDS = 16; //Number of Community Chest cards
int const BOARD_SIZE = 40;         //Total number of spaces on the board

int const STARTINGBALANCE = 1500;  //Starting balance for each players
int const SALARY = 200;            //Amount collected when passing Go

//Function Prototype
void initialization(City* cities, Board* board, int* chanceCards, int* communityChestCards); //Initialize cities, board, chance cards, and community chest cards from external files
void deallocateMemory(Player* players, City* cities, Board* board, int* chanceCards, int* communityChestCards); //Deallocate all dynamically allocated memory
void deallocateMemory(int* array); //Deallocate a dynamically allocated integer array

int  initializePlayers(Player* players, int nOfPlyrs); //get number of players and their names and initialize their starting data
void getOrderOfPlay(Player* players, int nOfPlyrs); //determine the order in which players will take their turns

void sortParallelArray(int *arr, Player* players, int size); //Sort an array and a parallel array of players based on the values in the first array
int binarySearch(int * array, int value); //search an array for value and return index
void sortArray(int *array, int size); //Sort an array
void randomizeArray(int *array, int size); //Randomize an array

void rollDice(int* diceRoll); //Simulate rolling two six-sided dice and return the results (1-6)

void mainGameLoop(Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs);
int showMenu(int menuTemplateIndex); //Display a menu based on the provided template index and return the user's choice
void handleMenuChoice(int choice,int menuTemplateIndex, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs); //Handle the action based on the user's menu choice
void movePlayer(bool* doubleRoll, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs); //Move a player a specified number of steps on the board

void locationAction(int playerIndex, int rollTotal, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards); //Handle the action when a players lands on a city (e.g., buy property, pay rent, draw card, etc.)

void payRentOrTax(int playerIndex, int ownerIndex, Player* players, Board* board, City* cities); //Handle rent payment when a players lands on an owned property
void buyProperty(int playerIndex, Player* players, Board* board, City* cities); //Handle the process of buying a property when a players lands on an unowned property
void drawChanceCard(int playerIndex, Player* players, int* chanceCards, Board* board, City* cities); //Handle drawing a Chance card and executing its effect
void drawCommunityChestCard(int playerIndex, Player* players, int* communityChestCards, Board* board, City* cities); //Handle drawing a Community Chest card and executing its effect
void goToJail(int playerIndex, Player* players); //Handle sending a players to jail

void jailTurn(int playerIndex, Player* players, Board* board, City* cities); //Handle a players's turn when they are in jail (e.g., attempt to roll doubles, pay fine, use Get Out of Jail Free card, etc.)

void moneyTransaction(int fromPlayerIndex, int toPlayerIndex, Player* players, int amount); //Handle money transactions between players (e.g., rent payment, property purchase, etc.) 
void moneyTransaction(int playerIndex, Player* players, int amount); //Handle money transactions between players and bank (e.g., salary collection, property purchase, etc.)
void handleLowBalance(int playerIndex, int amount, Player* players, Board* board, City* cities); //Handle situations where a players has low balance and needs to sell property, mortgage property, or declare bankruptcy

void upgradeProperty(int playerIndex, int* housesAvailable, int* hotelsAvailable, Player* players, Board* board, City* cities);
void mortgageProperty(int playerIndex, Player* players, Board* board, City* cities);
void unmortgageProperty(int playerIndex, Player* players, Board* board, City* cities);
void sellProperty(int playerIndex, Player* players, Board* board, City* cities);
void tradeProperty(int playerIndex, Player* players, Board* board, City* cities); //Handle trading properties between players
int declareBankruptcy(int playerIndex, int* housesAvailable, int* hotelsAvailable, Player* players, Board* board, City* cities); //Handle bankruptcy declaration

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    Player* players = new Player[MAX_PLAYERS];
    City* cities = new City[MAX_CITIES];
    Board* board = new Board[BOARD_SIZE];
    int* chanceCards = new int[MAX_CHANCE_CARDS];
    int* communityChestCards = new int[MAX_COMMUNITY_CHEST_CARDS];

    int noOfPlayers = MAX_PLAYERS;
    int housesAvailable = 32;
    int hotelsAvailable = 12;

    string* filenames = new string[4];
    filenames[0] = "CityData.bin";
    filenames[1] = "BoardData.bin";
    filenames[2] = "ChanceCardsData.bin";
    filenames[3] = "CommunityChestCardsData.bin";

    //Initialize Variables and game components
    initialization(cities, board, chanceCards, communityChestCards);


    //Start new game
    cout << "Welcome to Monopoly!" << endl;
    cout << "Starting a new game of Monopoly!" << endl;
    
    cout << "Press Enter to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    noOfPlayers = initializePlayers(players, noOfPlayers);
    cout << "Number of players: " << noOfPlayers << endl;

    cout << "----------------------------------------" << endl;

    cout << "First, let's determine the order of play." << endl;
    cout << "Press Continue to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    getOrderOfPlay(players, noOfPlayers);

    //Enter main game loop
    mainGameLoop(players, board, cities, chanceCards, communityChestCards, &housesAvailable, &hotelsAvailable, noOfPlayers);

    //Deallocate all dynamically allocated memory at the end of the game
    deallocateMemory(players, cities, board, chanceCards, communityChestCards);

    //Exit the program
    return 0;
};
void initialization(City* cities, Board* board, int* chanceCards, int* communityChestCards){
    //read city data from file and print to console
    //read chance cards data from file and print to console (will be implemented in version 3)
}  

void printCityData(City* city, int index){
    cout << "City No." << city[index].id << endl;
    cout << "Board Position: " << city[index].boardPosition << endl;
    cout << "Name: " << city[index].name << endl;
    cout << "Group ID: " << city[index].groupID << endl;
    cout << "Cost: " << city[index].cost << endl;
    cout << "upgradeCost: " << city[index].upgradeCost[0] << " for house, " << city[index].upgradeCost[1] << " for hotel" << endl;
    cout << "Rent with no houses/hotel: " << city[index].houseRent[0] << endl;
    cout << "Rent with 1 house: " << city[index].houseRent[1] << endl;
    cout << "Rent with 2 houses: " << city[index].houseRent[2] << endl;
    cout << "Rent with 3 houses: " << city[index].houseRent[3] << endl;
    cout << "Rent with 4 houses/hotel: " << city[index].houseRent[4] << endl;
    cout << "Is Owned: " << (city[index].isOwned ? "Yes" : "No")<< endl;
    cout << "Is Mortgaged: " << (city[index].isMortgaged ? "Yes" : "No")<< endl;
    cout<< endl; //Add an extra line for better readability
}
void deallocateMemory(Player* players, City* cities, Board* board, int* chanceCards, int* communityChestCards){
    for(int i=0; i<MAX_PLAYERS; i++){
        delete[] players[i].citiesOwned;
        delete[] players[i].railroadsOwned;
        delete[] players[i].utilitiesOwned;
    }
    delete[] players;
    delete[] cities;
    delete[] board;
    delete[] chanceCards;
    delete[] communityChestCards;
}
void deallocateMemory(int* array){
    delete[] array;
}
int initializePlayers(Player* players, int nOfPlyrs){
    //Declare Variables
    int noOfPlayers;

    //Get number of players and their names, initialize their attributes
    cout<< "How many players are playing? (2-4): ";
    cin>> nOfPlyrs;
    for(int i=0; i<nOfPlyrs; i++){
        cout<< "Enter name for Player " << (i+1) << ": ";
        cin>> players[i].name;
        cin.ignore(); //Ignore the newline character left in the input buffer
        players[i].id = i;
        players[i].balance = STARTINGBALANCE;
        players[i].position = 0; //Start at Go
        players[i].citiesOwned = new int[22]; //Dynamically allocate array for owned cities
        players[i].railroadsOwned = new int[4]; //Dynamically allocate array for owned railroads
        players[i].utilitiesOwned = new int[2]; //Dynamically allocate array for owned utilities
        players[i].numProperties = 0;
        players[i].inJail = false;
        players[i].netWorth = STARTINGBALANCE; //Initial net worth is just the starting balance
        players[i].isBankrupt = false;
    } 
    return nOfPlyrs; 
}
void getOrderOfPlay(Player* players, int nOfPlyrs){
    //Declare Variables
    int *rolls = new int[MAX_PLAYERS];
    int* diceRoll = new int[2];

    //Roll dice for each player to determine order of play
    cout<< "Determining order of play by rolling dice..." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

    for(int i=0; i<nOfPlyrs; i++){
        cout << players[i].name << " is rolling the dice..." << endl;
        cout<< "Press Enter to roll the dice...";
        cin.get(); //Wait for user input to roll the dice
        rollDice(diceRoll);
        rolls[i] = diceRoll[0] + diceRoll[1]; //Sum of the two dice
        cout<< players[i].name << " rolled a " << rolls[i] << endl;
        cout << "----------------------------------------" << endl;
    }
    //Sort the rolls to determine order of play
    sortParallelArray(rolls, players, nOfPlyrs); //Sort the rolls and the players array in parallel based on the rolls
    cout<< "Order of play based on dice rolls: " << endl;
    for(int i=0; i<nOfPlyrs; i++){
        cout<< players[i].name << " (" << rolls[i] << ")" << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

    deallocateMemory(rolls); //Deallocate the dynamically allocated rolls array    
    deallocateMemory(diceRoll); //Deallocate the dynamically allocated diceRoll array
}
void rollDice(int* diceRoll){ //Simulate rolling two six-sided dice and store the results in the provided array
    diceRoll[0] = rand() % 6 + 1; //Random number between 1 and 6
    diceRoll[1] = rand() % 6 + 1; //Random number between 1 and 6
}
void sortParallelArray(int *arr, Player* players, int size){ //Sort an array and a parallel array of players based on the values in the first array
    //Declare a temporary variable for swapping
    int temp;
    Player tempPlayer;
    
    //Bubble sort algorithm to sort the array in descending order
    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-i-1; j++){
            if(arr[j] < arr[j+1]){ //Sort in descending order
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;

                //Swap the corresponding players in the parallel array
                tempPlayer = players[j];
                players[j] = players[j+1];
                players[j+1] = tempPlayer;
            }
        }
    }
}
void sortArray(int *arr, int size){
    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-i-1; j++){
            if(arr[j] < arr[j+1]){ //Sort in descending order
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int binarySearch(int *array, int value){ //search an array for value and return index
    int left = 0;
    int right = MAX_PLAYERS - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (array[mid] == value) {
            return mid; //Value found at index mid
        }
        else if (array[mid] < value) {
            right = mid - 1; //Search in the left half
        }
        else {
            left = mid + 1; //Search in the right half
        }
    }
    return -1; //Value not found in the array
}
void randomizeArray(int *arr, int size){ //Randomize an array
    //declare variables
    int randomIndex; //Random index for swapping
    int temp; //Temporary variable for swapping
    
    //Randomly shuffle the array
    for(int i=0; i<size; i++){
        randomIndex = rand() % size; //Random index between 0 and size-1
        temp = arr[i];
        arr[i] = arr[randomIndex];
        arr[randomIndex] = temp;
    }
}
void mainGameLoop(Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs){
    //Declare variables for the main game loop
    bool gameOver = false;
    bool doubleRoll = false;

    //Main game loop logic will be implemented here
    do{
        for(int i=0; i<nOfPlyrs; i++){
            if(!players[i].isBankrupt){
                if(players[i].inJail){
                    //do jail turn logic
                    cout << "IN JAIL" << endl;
                    cout << "----------------------------------------" << endl;
                    cout << "Press Enter to continue..." << endl;
                    cin.get(); //Wait for user to press Enter
                }
                else{
                    cout << "It's " << players[i].name << "'s turn." << endl;
                    cout << "----------------------------------------" << endl;

                    do{
                        handleMenuChoice(showMenu(0), 0, i, players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, nOfPlyrs);
                        movePlayer(&doubleRoll, i, players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, nOfPlyrs);
                    }while(doubleRoll);
                    handleMenuChoice(showMenu(1), 1, i, players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, nOfPlyrs);
                    cout << "End of " << players[i].name << "'s turn." << endl;
                    cout << "----------------------------------------" << endl;
                }
            }
            //else skip
        }
        cout << "Press Enter to continue..." << endl;
        cin.get(); //Wait for user to press Enter

    }while(!gameOver);

}
int showMenu(int menuTemplateIndex){
    //Declare Variables
    int choice;

    //Display menu options based on the menu template index
    cout<<"0. " << (menuTemplateIndex==0 ? "Roll the dice" : "End turn") << endl;
    cout<<"1. Upgrade a property" << endl;
    cout<<"2. Mortgage a property" << endl;
    cout<<"3. Unmortgage a property" << endl;
    cout<<"4. Sell a property" << endl;
    cout<<"5. Declare bankruptcy" << endl;
    do{
        cin >> choice;
        if(choice < 0 || choice > 5){
            cout<< "Invalid choice. Please enter a number between 0 and 5: ";
        }
    }while(choice < 0 || choice > 5);
    return choice;
}
void handleMenuChoice(int choice,int menuTemplateIndex, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs){ //Handle the action based on the user's menu choice
    bool endTurn = false;

    do{
        switch(choice){
            case 0: //return to main where case 0 is done
                break;
            case 1:
                upgradeProperty(playerIndex, housesAvailable, hotelsAvailable, players, board, cities); //Handle upgrade property action
                break;
            case 2:
                mortgageProperty(playerIndex, players, board, cities); //Handle mortgage property action
                break;
            case 3:
                unmortgageProperty(playerIndex, players, board, cities); //Handle unmortgage property action
                break;
            case 4:
                sellProperty(playerIndex, players, board, cities); //Handle sell property action
                break;
            case 5:
                declareBankruptcy(playerIndex, housesAvailable, hotelsAvailable, players, board, cities); //Handle declare bankruptcy action
                break;
            default:
                //Handle invalid choice
                cout << "Error: Invalid choice in handleMenuChoice function." << endl;

                break;
        }
        if(choice != 0){
            choice = showMenu(menuTemplateIndex);
        } 
        if (players[playerIndex].isBankrupt) endTurn = true;
        if (players[playerIndex].inJail) endTurn = true;
    }while(choice!=0 && !endTurn);
}
void movePlayer(bool* doubleRoll, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs){
    //Declare variables
    int* diceRoll = new int[2];
    int rollTotal;
    int doubleCount = 0;

    //Roll the dice
    cout << players[playerIndex].name << " is rolling the dice." << endl;
    cout << "Press Enter to Roll the dice..." << endl;
    cin.get(); //Wait for user to press Enter
    rollDice(diceRoll);
    cout << "Rolled a " << diceRoll[0] << " and a " << diceRoll[1] << "." << endl;
    rollTotal = diceRoll[0] + diceRoll[1];

    //Check for double roll
    if (diceRoll[0] == diceRoll[1]){
        cout << "Double roll! You rolled a " << diceRoll[0] << " and a " << diceRoll[1] << "." << endl;
        doubleCount++;
        if (doubleCount == 3){
            //go to jail
            cout << "You rolled doubles three times in a row and are going to jail!" << endl;
            players[playerIndex].inJail = true;
        }
        else{
            *doubleRoll = true;
        }
    }
    else *doubleRoll = false;

    //Move a player a specified number of steps on the board
    if (!players[playerIndex].inJail){
        players[playerIndex].position += rollTotal;

        cout << "And you moved " << rollTotal << " spaces to position ";
        if (players[playerIndex].position >= BOARD_SIZE){
            players[playerIndex].position -= BOARD_SIZE;
            cout << players[playerIndex].position << "." << endl;
            if (players[playerIndex].position == 0){ //If the players lands exactly on Go, they collect salary for passing Go
                cout<< "You landed on Go! Collect $200." << endl;
            }
            else{
                cout<< "You passed Go! Collect $200." << endl;
            }
            players[playerIndex].balance += 200; //Collect $200 for passing Go
        }
        else cout << players[playerIndex].position << "." << endl;
        locationAction(playerIndex, rollTotal, players, board, cities, chanceCards, communityChestCards); //Handle the action for landing on the new position
    }
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

}
void locationAction(int playerIndex, int rollTotal, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards){
    //Declare Variables
        int propertyID; //ID of the property the players landed on
        char choice; //User choice for buying property
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
    
    switch (board[players[playerIndex].position].type){
        case 0: //already handled on movePlayer function
            break;
        case 1:
        case 2:
        case 3:
            propertyID = board[players[playerIndex].position].propertyID;
            if(cities[propertyID].isOwned){
                if(cities[propertyID].ownerIndex != playerIndex){
                    payRentOrTax(playerIndex, rollTotal, players, board, cities); //Pay rent to the owner (to be implemented)
                }
                else{
                    cout<< "You landed on your own property." << endl;
                }
            }
            else{
                cout<< "This property is unowned. Would you like to buy it? (y/n): " << endl;
                cin>> choice;
                if(choice == 'y' || choice == 'Y'){
                    buyProperty(playerIndex, players, board, cities); //Handle buying the property (to be implemented)
                }
            }
            break;
        case 4:
            drawChanceCard(playerIndex, players, chanceCards, board, cities); //Handle drawing a Chance card (to be implemented)
            break;
        case 5:
            drawCommunityChestCard(playerIndex, players, communityChestCards, board, cities); //Handle drawing a Community Chest card (to be implemented)
            break;
        case 6:
            payRentOrTax(playerIndex, rollTotal, players, board, cities); //Handle paying income tax (to be implemented)
            break;
        case 7:
            payRentOrTax(playerIndex, rollTotal, players, board, cities); //Handle paying luxury tax (to be implemented)
            break;
        case 8:
            cout<< "Visiting jail, Say Hi if anyone there." << endl;
            break;
        case 9:
            cout<< "Free Parking." << endl;
            break;
        case 10:
            goToJail(playerIndex, players);
            break;
        default:
            cout<< "Error: wrong type of board location (error in locationAction function)" << endl;
            break;
    }
}
void payRentOrTax(int playerIndex, int rollTotal, Player* player, Board* board, City* cities){
    //declare variables
    int rentAmount; //Amount of rent to be paid
    int ownerIndex; //Index of the owner of the property
    int propertyType; //Type of the property the players landed on

    //initrialize variables
    rentAmount = cities[board[player[playerIndex].position].propertyID].currentRent;
    ownerIndex = cities[board[player[playerIndex].position].propertyID].ownerIndex;
    propertyType = board[player[playerIndex].position].type;

    //Handle rent payment when a players lands on an owned property
    switch(propertyType){
        case 1: //City
            cout<< "You landed on " << cities[board[player[playerIndex].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
            rentAmount = cities[board[player[playerIndex].position].propertyID].currentRent;
            break;
        case 2: //Railroad
            cout<< "You landed on " << cities[board[player[playerIndex].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
            switch(player[ownerIndex].numRailroads){ //Check how many railroads the owner owns to determine rent amount
                case 1:
                    rentAmount = 25;
                    break;
                case 2:
                    rentAmount = 50;
                    break;
                case 3:
                    rentAmount = 100;
                    break;
                case 4:
                    rentAmount = 200;
                    break;
                default:
                    cout<< "Error: wrong number of railroads owned for rent calculation" << endl;
            }
            break;
        case 3: //Utility
            cout<< "You landed on " << cities[board[player[playerIndex].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
            if(player[ownerIndex].numUtilities == 1){
                rentAmount = (rollTotal * 4);
            }
            else if(player[ownerIndex].numUtilities == 2){
                rentAmount = (rollTotal * 10);
            }
            break;
        case 6: //Income Tax
            cout<< "You landed on Income Tax. You must pay $200 or 10% of your total worth in tax." << endl;
            rentAmount = 200;
            break;
        case 7: //Luxury Tax
            cout<< "You landed on Luxury Tax. You must pay $100 in tax." << endl;
            rentAmount = 100;
            break;
        default:
            cout<< "Error: wrong type of property for rent payment" << endl;
            break;
    }
    if (propertyType == 6 || propertyType == 7){ //If the players landed on a tax space, they pay the bank instead of another players
        moneyTransaction(playerIndex, player, rentAmount); //Handle money transaction with the bank (to be implemented)
    }
    else{
        cout<< "You landed on " << cities[board[player[playerIndex].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
        moneyTransaction(playerIndex, ownerIndex, player, -1*rentAmount); //Handle money transaction with the property owner (to be implemented)
        if (!player[playerIndex].isBankrupt){
            cout<< "You paid $" << rentAmount << " in rent to " << player[ownerIndex].name << "." << endl;
        }
    }
}
void drawChanceCard(int playerIndex, Player* players, int* chanceCards, Board* board, City* cities){
    cout << "YOU ARE IN DRAW CHANCE CARD FUNCTION" << endl;
}
void drawCommunityChestCard(int playerIndex, Player* players, int* communityChestCards, Board* board, City* cities){
    cout << "YOU ARE IN DRAW COMMUNITY CHEST CARD FUNCTION" << endl;
}
void moneyTransaction(int playerIndex, int recipientIndex, Player* players, int amount){ //Handle money transactions between players (e.g., rent payment, property purchase, etc.) 
    if (players[playerIndex].balance < amount){
        cout<< "You cannot afford to pay. You must sell property or declare bankruptcy." << endl;
        handleLowBalance(playerIndex, amount, players, nullptr, nullptr); //Handle low balance situation (to be implemented)
    }
    if (players[playerIndex].isBankrupt){
        cout<< "You are bankrupt and cannot pay what you owe." << endl;
    }
    else{
    players[playerIndex].balance -= amount; //Deduct the amount from the payer's balance
    players[recipientIndex].balance += amount; //Add the amount to the recipient's balance
    }
}
void moneyTransaction(int playerIndex, Player* players, int amount){ //Handle money transactions between players and bank (e.g., salary collection, property purchase, etc.)
    if (players[playerIndex].balance < amount){
        cout<< "You cannot afford to pay. You must sell property or declare bankruptcy." << endl;
        handleLowBalance(playerIndex, amount, players, nullptr, nullptr); //Handle low balance situation (to be implemented)
    }
    if (players[playerIndex].isBankrupt){
        cout<< "You are bankrupt and cannot pay what you owe." << endl;
    }
    else{
    players[playerIndex].balance += amount; //Add the amount to the player's balance (for salary collection) or deduct the amount from the player's balance (for property purchase)
    }
}
void handleLowBalance(int playerIndex, int amount, Player* players, Board* board, City* cities){
    cout << "YOU ARE IN HANDLE LOW BALANCE FUNCTION"<<endl<<endl;
}
void buyProperty(int playerIndex, Player* players, Board* board, City* cities){
    //declare variables
    int propertyID; //ID of the property the players wants to buy
    int propertyCost; //Cost of the property the players wants to buy

    //Handle the process of buying a property when a players lands on an unowned property
    propertyID = board[players[playerIndex].position].propertyID;
    propertyCost = cities[propertyID].cost;
    if (players[playerIndex].isBankrupt){
        cout<< "You are bankrupt and cannot buy this property." << endl;
    }
    else if (players[playerIndex].balance < propertyCost){
        cout<< "You cannot afford to buy this property." << endl;
    }
    else{
        moneyTransaction(playerIndex, players, -1*propertyCost); //Handle money transaction with the bank for property purchase (to be implemented)
        cities[propertyID].isOwned = true; //Mark the city as owned
        cities[propertyID].ownerIndex = playerIndex; //Set the owner index for the city
        players[playerIndex].numProperties++; //Increment the number of properties owned by the player
        players[playerIndex].citiesOwned[players[playerIndex].numProperties - 1] = propertyID; //Add the property to the player's owned properties array
        cout<< "You bought " << cities[propertyID].name << " for $" << propertyCost << "." << endl;
    }
}
void upgradeProperty(int playerIndex, int* housesAvailable, int* hotelsAvailable, Player* players, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to upgrade
    int propertyID; //ID of the property the players wants to upgrade
    int upgradeCost; //Cost of upgrading the property
    int groupID; //Group ID of the property the players wants to upgrade
    int index; //Index for checking if the player owns all properties in the group to determine if they can upgrade

    //Handle the process of upgrading a property when a players owns it and has enough money
    cout<< "Your properties: " << endl;
    for(int i=0; i<players[playerIndex].numProperties; i++){
        cout<< i <<". " << cities[players[playerIndex].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to upgrade?" << endl;
    cin>> propertyNumber;
    propertyID = players[playerIndex].citiesOwned[propertyNumber];
    groupID = cities[propertyID].groupID;
    index = binarySearch(players[playerIndex].groupOwned, groupID); //Check if the player owns all properties in the group to determine if they can upgrade (to be implemented)
    if (index == -1){
        cout<< "You do not own all properties in this group and cannot upgrade." << endl;
    }
    else{
        if (cities[propertyID].upgradeLevel > 4){
            cout << "This property already has a hotel and cannot be upgraded further." << endl;
        }
        else if (cities[propertyID].upgradeLevel == 4){
            if (*hotelsAvailable <= 0){
                cout<< "There are no hotels available to upgrade this property." << endl;
            }
            else{
                if (cities[propertyID].upgradeLevel > cities[propertyID].groupMinimumUpgradeLevel){
                    cout<< "You must upgrade the other properties in this group to the same level before upgrading this property." << endl;
                }
                else{
                    moneyTransaction(playerIndex, players, -1*cities[propertyID].upgradeCost[1]); //Handle money transaction with the bank for property upgrade (to be implemented)
                    cities[propertyID].upgradeLevel++; //Upgrade the property
                    (*hotelsAvailable)--; //Decrement the number of hotels available
                    (*housesAvailable) += 4; //Return the 4 houses used for the upgrade back to the pool of available houses
                    cout<< "You upgraded " << cities[propertyID].name << " to a hotel for $" << cities[propertyID].upgradeCost[1] << "." << endl;
                }
            }
        }
        else{
            if (*housesAvailable <= 0){
                cout<< "There are no houses available to upgrade this property." << endl;
            }
            else{
                if (cities[propertyID].upgradeLevel > cities[propertyID].groupMinimumUpgradeLevel){
                    cout<< "You must upgrade the other properties in this group to the same level before upgrading this property." << endl;
                }
                else{
                    moneyTransaction(playerIndex, players, -1*cities[propertyID].upgradeCost[0]); //Handle money transaction with the bank for property upgrade (to be implemented)
                    cities[propertyID].upgradeLevel++; //Upgrade the property
                    (*housesAvailable)--; //Decrement the number of houses available
                    cout<< "You upgraded " << cities[propertyID].name << " to a house for $" << cities[propertyID].upgradeCost[0] << "." << endl;
                }
            }
        }
    }

}
void mortgageProperty(int playerIndex, Player* players, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to mortgage
    int propertyID; //ID of the property the players wants to mortgage
    int mortgageValue; //Amount of money the player receives from mortgaging the property

    //Handle the process of mortgaging a property when a players owns it and needs money
    cout<< "Your properties: " << endl;
    for(int i=0; i<players[playerIndex].numProperties; i++){
        cout<< i <<". " << cities[players[playerIndex].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to mortgage?" << endl;
    cin>> propertyNumber;
    propertyID = players[playerIndex].citiesOwned[propertyNumber];
    if (cities[propertyID].isMortgaged){
        cout<< "This property is already mortgaged." << endl;
    }
    else{
        mortgageValue = cities[propertyID].cost / 2; //Mortgage value is typically half the cost of the property
        moneyTransaction(playerIndex, players, mortgageValue); //Handle money transaction with the bank for mortgaging the property (to be implemented)
        cities[propertyID].isMortgaged = true; //Mark the city as mortgaged
        cout<< "You mortgaged " << cities[propertyID].name << " for $" << mortgageValue << "." << endl;
    }
}
void unmortgageProperty(int playerIndex, Player* players, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to unmortgage
    int propertyID; //ID of the property the players wants to unmortgage
    int unmortgageCost; //Amount of money the player must pay to unmortgage the property

    //Handle the process of unmortgaging a property when a players owns it and has enough money
    cout<< "Your properties: " << endl;
    for(int i=0; i<players[playerIndex].numProperties; i++){
        cout<< i <<". " << cities[players[playerIndex].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to unmortgage?" << endl;
    cin>> propertyNumber;
    propertyID = players[playerIndex].citiesOwned[propertyNumber];
    if (!cities[propertyID].isMortgaged){
        cout<< "This property is not mortgaged." << endl;
    }
    else{
        unmortgageCost = (cities[propertyID].cost / 2) * 1.1; //Unmortgage cost is typically the mortgage value plus 10% interest
        if (players[playerIndex].balance < unmortgageCost){
            cout<< "You cannot afford to unmortgage this property." << endl;
        }
        else{
            moneyTransaction(playerIndex, players, -1*unmortgageCost); //Handle money transaction with the bank for unmortgaging the property (to be implemented)
            cities[propertyID].isMortgaged = false; //Mark the city as unmortgaged
            cout<< "You unmortgaged " << cities[propertyID].name << " for $" << unmortgageCost << "." << endl;
        }
    }
}
void sellProperty(int playerIndex, Player* players, Board* board, City* cities){
    cout << "YOU ARE IN SELL PROPERTY FUNCTION"<<endl<<endl;
}
void tradeProperty(int playerIndex, Player* players, Board* board, City* cities){
    cout << "YOU ARE IN TRADE PROPERTY FUNCTION"<<endl<<endl;
}
int declareBankruptcy(int playerIndex, int* housesAvailable, int* hotelsAvailable, Player* players, Board* board, City* cities){
    //declare variables
    int propertyID; //ID of the property the players wants to sell
    int totalAssetsPrice = 0; //Total value of the player's assets (cash + properties) to determine if they can pay what they owe or if they must declare bankruptcy
    
    //Handle the process of declaring bankruptcy and removing the player from the game when they cannot afford to pay what they owe
    players[playerIndex].isBankrupt = true; //Mark the player as bankrupt
    //Transfer the player's properties back to the bank and mark them as unowned
    for(int i=0; i<players[playerIndex].numProperties; i++){
        propertyID = players[playerIndex].citiesOwned[i];
        cities[propertyID].isOwned = false;
        cities[propertyID].ownerIndex = -1;
        if (cities[propertyID].isMortgaged){
            cities[propertyID].isMortgaged = false; //Unmortgage the property when transferring it back to the bank
            totalAssetsPrice -= cities[propertyID].cost / 2 * 1.1; //remove the mortgage value from the total assets price
        }
        if (cities[propertyID].upgradeLevel > 0){
            if (cities[propertyID].upgradeLevel == 5){
                (*hotelsAvailable)++; //Return the hotel used for the upgrade back to the pool of available hotels
                (*housesAvailable) += 4; //Return the 4 houses used for the upgrade back to the pool of available houses
                totalAssetsPrice += (cities[propertyID].upgradeCost[0] * 4) + cities[propertyID].upgradeCost[1]; //Add the value of the upgrades to the total assets price
            }
            else{
                (*housesAvailable) += cities[propertyID].upgradeLevel; //Return the houses used for the upgrade back to the pool of available houses
                totalAssetsPrice += cities[propertyID].upgradeCost[0] * cities[propertyID].upgradeLevel; //Add the value of the upgrades to the total assets price
            }
        }
        cities[propertyID].upgradeLevel = 0; //Reset the upgrade level of the property
        totalAssetsPrice += cities[propertyID].cost; //Add the property's cost to the total assets price
    }
    cout<< "You declared bankruptcy and are out of the game." << endl;
    return totalAssetsPrice; //Return the total value of the player's assets to determine if they can pay what they owe or if they must declare bankruptcy
}
void goToJail(int playerIndex, Player* players){
    players[playerIndex].position = 10; //Move the player to the Jail space
    players[playerIndex].inJail = true; //Mark the player as being in jail
    cout<< "You are now in jail." << endl;
}
void jailTurn(int playerIndex, Player* players, Board* board, City* cities){
    cout << "YOU ARE IN JAIL TURN FUNCTION" << endl;
}
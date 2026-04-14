/*
Author: Philopatair Mallik
Date: 04/01/2026
purpose: Project 1 - Monopoly Game Simulation
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library

//User libraries
#include "Cities.h"
#include "Players.h"
#include "Board.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
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

void sortParallelArr(int *arr, Player* players, int size); //Sort an array and a parallel array of players based on the values in the first array
void rollDice(int* diceRoll); //Simulate rolling two six-sided dice and return the results (1-6)

void mainGameLoop(Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int housesAvailable, int hotelsAvailable, int nOfPlyrs);
int showMenu(int menuTemplateIndex); //Display a menu based on the provided template index and return the user's choice
void handleMenuChoice(int choice,int menuTemplateIndex, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int housesAvailable, int hotelsAvailable, int nOfPlyrs); //Handle the action based on the user's menu choice
void movePlayer(bool* doubleRoll, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int housesAvailable, int hotelsAvailable, int nOfPlyrs); //Move a player a specified number of steps on the board

void locationAction(int, int,Player*, Board*, City*, int*, int*); //Handle the action when a players lands on a city (e.g., buy property, pay rent, draw card, etc.)


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
    mainGameLoop(players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, noOfPlayers);

    //Deallocate all dynamically allocated memory at the end of the game
    deallocateMemory(players, cities, board, chanceCards, communityChestCards);

    //Exit the program
    return 0;
};
void initialization(City* cities, Board* board, int* chanceCards, int* communityChestCards){
    //Initialize players, cities, board, chance cards, and community chest cards
    //to be implemented
    //import data for players, cities, board, chance cards, and community chest cards from external files
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
    sortParallelArr(rolls, players, nOfPlyrs); //Sort the rolls and the players array in parallel based on the rolls
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
void sortParallelArr(int *arr, Player* players, int size){ //Sort an array and a parallel array of players based on the values in the first array
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
void mainGameLoop(Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int housesAvailable, int hotelsAvailable, int nOfPlyrs){
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
    cout<<"1. Buy a property" << endl;
    cout<<"2. Upgrade a property" << endl;
    cout<<"3. Mortgage a property" << endl;
    cout<<"4. Unmortgage a property" << endl;
    cout<<"5. Sell a property" << endl;
    cout<<"6. Declare bankruptcy" << endl;
    do{
        cin >> choice;
        if(choice < 0 || choice > 6){
            cout<< "Invalid choice. Please enter a number between 0 and 6: ";
        }
    }while(choice < 0 || choice > 6);
    return choice;
}
void handleMenuChoice(int choice,int menuTemplateIndex, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int housesAvailable, int hotelsAvailable, int nOfPlyrs){ //Handle the action based on the user's menu choice
    bool endTurn = false;

    do{
        switch(choice){
            case 0: //return to main where case 0 is done
                break;
            case 1:
                //Handle buy property action
                break;
            case 2:
                //Handle upgrade property action
                break;
            case 3:
                //Handle mortgage property action
                break;
            case 4:
                //Handle unmortgage property action
                break;
            case 5:
                //Handle sell property action
                break;
            case 6:
                //Handle declare bankruptcy action
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
void movePlayer(bool* doubleRoll, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int housesAvailable, int hotelsAvailable, int nOfPlyrs){
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
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            break;
        default:
            break;
    }
}
/*
Author: Philopatair Mallik
Date: 05/05/2026
purpose: Project 1 - Monopoly Game Simulation
*/
/*
version 2 updates:
-Added the initialization function to read city and board data from external files
-added the jailturn function to handle a players's turn when they are in jail
-Added the tradeProperty function to handle trading properties between players
-Added two functions to display a player's properties and to display a one-liner description of a property
-Fixed various bugs and edge cases related to property ownership, rent calculation, and bankruptcy declaration
- removed the sellProperty function for now to simplify the implementation, will be added back in version 3

Next steps:
-Implement the logic for Chance and Community Chest cards, including the various effects they can have on players (moving them to different spaces, giving or taking money, etc.)
-Implement a display function to show the current state of the game, including the board, players' positions and balances, and properties owned.
-Finish the handlelowBalance function to allow players to sell properties, mortgage properties, or declare bankruptcy when they have low balance and need to pay money.



*/



//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
#include <fstream>    //File I/O Library

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
void initialization(string* filesNames, City* cities, Board* board, int* chanceCards, int* communityChestCards); //Initialize cities, board, chance cards, and community chest cards from external files
City* readCityFromFile(string fileName, int id); //Read data for cities from external files
Board* readBoardFromFile(string fileName, int id); //Read data for board from external files

void deallocateMemory(Player* players, City* cities, Board* board, int* chanceCards, int* communityChestCards); //Deallocate all dynamically allocated memory
void deallocateMemory(int* array); //Deallocate a dynamically allocated integer array
void deallocateMemory(string* array); //Deallocate a dynamically allocated string array

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
void movePlayer(int* doublecount, bool* doubleRoll, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int nOfPlyrs); //Move a player a specified number of steps on the board

void locationAction(int playerIndex, int rollTotal, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards); //Handle the action when a players lands on a city (e.g., buy property, pay rent, draw card, etc.)

void payRentOrTax(int playerIndex, int rollTotal, Player* player, Board* board, City* cities); //Handle rent or tax payment when a players lands on a property owned by another player or on a tax space
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

void calculateGroupOwned(int propertyID, int playerIndex, Player* players, City* cities); //Calculate how many properties in each color group a player owns and update the player's groupOwned array accordingly
void listPlayerProperties(int playerIndex, Player* players, City* cities); //List the properties owned by a player
void displayPropertyOneLiner(int propertyID, City* cities); //Display a one-liner description of a property (e.g., name, rent, upgrade level, etc.) 

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
        cout << "Welcome to Monopoly!" << endl;

    initialization(filenames, cities, board, chanceCards, communityChestCards);


    //Start new game
    cout << "Welcome to Monopoly!" << endl;
    cout << "Starting a new game of Monopoly!" << endl;
    
    cout << "Press Enter to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    noOfPlayers = initializePlayers(players, noOfPlayers);
    cout << "Number of players: " << noOfPlayers << endl;
    cin.ignore(); //Ignore the newline character left in the input buffer


    cout << "----------------------------------------" << endl;

    cout << "First, let's determine the order of play." << endl;
    cout << "Press Continue to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    getOrderOfPlay(players, noOfPlayers);

    //Enter main game loop
    mainGameLoop(players, board, cities, chanceCards, communityChestCards, &housesAvailable, &hotelsAvailable, noOfPlayers);

    //Deallocate all dynamically allocated memory at the end of the game
    deallocateMemory(players, cities, board, chanceCards, communityChestCards);
    deallocateMemory(filenames);

    //Exit the program
    return 0;
};
void initialization(string* fileNames, City* cities, Board* board, int* chanceCards, int* communityChestCards){
    //read city data from file and print to console
    for (int i=0; i<MAX_CITIES; i++){
        City* cityFromFile = readCityFromFile(fileNames[0], i);
        cities[i] = *cityFromFile; //Store the read city data in the cities array
        delete cityFromFile;
    }
    //read board data from file and print to console
    for (int i=0; i<MAX_BOARD_SPACES; i++){
        Board* boardFromFile = readBoardFromFile(fileNames[1], i);
        board[i] = *boardFromFile; //Store the read board data in the board array
        delete boardFromFile;
    }
}
City* readCityFromFile(string fileName, int id){
    //Open the file for reading in binary mode
    fstream inFile;
    inFile.open(fileName, ios::in | ios::binary); //Open the file for reading in binary mode
    
    //Declare a City struct to hold the read data
    City* city = new City;
    long cursor = 0L;

    //Find the correct position in the file based on the city ID and read the city data
    cursor = id * sizeof(City); //Calculate the byte offset for the city with the given ID

    //read the city data from the file
    inFile.seekg(cursor, ios::beg); //Move the file pointer to the correct position
    inFile.read(reinterpret_cast<char*>(city), sizeof(City)); //Read the city data into the city struct

    inFile.close();
    return city;
}
Board* readBoardFromFile(string fileName, int id){
    //Open the file for reading in binary mode
    fstream inFile;
    inFile.open(fileName, ios::in | ios::binary); //Open the file for reading in binary mode
    
    //Declare a Board struct to hold the read data
    Board* board = new Board;
    long cursor = 0L;

    //Find the correct position in the file based on the board ID and read the board data
    cursor = id * sizeof(Board); //Calculate the byte offset for the board with the given ID

    //read the board data from the file
    inFile.seekg(cursor, ios::beg); //Move the file pointer to the correct position
    inFile.read(reinterpret_cast<char*>(board), sizeof(Board)); //Read the board data into the board struct

    inFile.close();
    return board;
}
void deallocateMemory(Player* players, City* cities, Board* board, int* chanceCards, int* communityChestCards){
    for(int i=0; i<MAX_PLAYERS; i++){
        delete[] players[i].citiesOwned;
        delete[] players[i].railroadsOwned;
        delete[] players[i].utilitiesOwned;
        delete[] players[i].groupOwned;
        delete[] players[i].upgradesOwned;
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
void deallocateMemory(string* array){
    delete[] array;
}
int initializePlayers(Player* players, int noOfPlyrs){
    //Get number of players and their names, initialize their attributes
    cout<< "How many players are playing? (2-4): ";
    cin>> noOfPlyrs;
    for(int i=0; i<noOfPlyrs; i++){
        cout<< "Enter name for Player " << (i+1) << ": ";
        cin>> players[i].name;
        players[i].id = i;
        players[i].balance = STARTINGBALANCE;
        players[i].position = 0; //Start at Go
        players[i].citiesOwned = new int[22]; //Dynamically allocate array for owned cities
        for (int j=0; j<22; j++){
            players[i].citiesOwned[j] = -1; //Initialize all city ownership to -1 (indicating no ownership)
        }
        players[i].railroadsOwned = new int[4]; //Dynamically allocate array for owned railroads
        for (int j=0; j<4; j++){
            players[i].railroadsOwned[j] = -1; //Initialize all railroad ownership to -1 (indicating no ownership)
        }
        players[i].utilitiesOwned = new int[2]; //Dynamically allocate array for owned utilities
        for (int j=0; j<2; j++){
            players[i].utilitiesOwned[j] = -1; //Initialize all utility ownership to -1 (indicating no ownership)
        }
        players[i].groupOwned = new bool[10]; //Dynamically allocate and initialize array to track group ownership
        for (int j=0; j<10; j++){
            players[i].groupOwned[j] = false; //Initialize all group ownership counts to false
        }
        players[i].upgradesOwned = new int[2]; //Dynamically allocate and initialize array to track upgrades owned
        for (int j=0; j<2; j++){
            players[i].upgradesOwned[j] = 0; //Initialize all upgrade counts to 0
        }
        players[i].numRailroads = 0;
        players[i].numUtilities = 0;
        players[i].numCities = 0;
        players[i].inJail = false;
        players[i].jailTurns = 0;
        players[i].netWorth = STARTINGBALANCE; //Initial net worth is just the starting balance
        players[i].isBankrupt = false;
 
    } 
    return noOfPlyrs; 
}
void getOrderOfPlay(Player* players, int noOfPlyrs){
    //Declare Variables
    int *rolls = new int[MAX_PLAYERS];
    int* diceRoll = new int[2];

    //Roll dice for each player to determine order of play
    cout<< "Determining order of play by rolling dice..." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

    for(int i=0; i<noOfPlyrs; i++){
        cout << players[i].name << " is rolling the dice..." << endl;
        cout<< "Press Enter to roll the dice...";
        cin.get(); //Wait for user input to roll the dice
        rollDice(diceRoll);
        rolls[i] = diceRoll[0] + diceRoll[1]; //Sum of the two dice
        cout<< players[i].name << " rolled a " << rolls[i] << endl;
        cout << "----------------------------------------" << endl;
    }
    //Sort the rolls to determine order of play
    sortParallelArray(rolls, players, noOfPlyrs); //Sort the rolls and the players array in parallel based on the rolls
    cout<< "Order of play based on dice rolls: " << endl;
    for(int i=0; i<noOfPlyrs; i++){
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
            left = mid + 1; //Search in the right half
        }
        else {
            right = mid - 1; //Search in the left half
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
void mainGameLoop(Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int noOfPlyrs){
    //Declare variables for the main game loop
    bool gameOver = false;
    bool doubleRoll = false;
    int doublecount = 0;

    //Main game loop logic will be implemented here
    do{
        for(int i=0; i<noOfPlyrs; i++){
            if(!players[i].isBankrupt){
                if(players[i].inJail){
                    //do jail turn logic
                    cout << "IN JAIL" << endl;
                    jailTurn(i, players, board, cities);
                    cout << "----------------------------------------" << endl;
                }
                else{
                    doublecount = 0;
                    cout << "It's " << players[i].name << "'s turn." << endl;
                    cout << "----------------------------------------" << endl;

                    do{
                        handleMenuChoice(showMenu(0), 0, i, players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, noOfPlyrs);
                        movePlayer(&doublecount, &doubleRoll, i, players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, noOfPlyrs);
                    }while(doubleRoll);
                    handleMenuChoice(showMenu(1), 1, i, players, board, cities, chanceCards, communityChestCards, housesAvailable, hotelsAvailable, noOfPlyrs);
                    cout << "End of " << players[i].name << "'s turn." << endl;
                    cout << "----------------------------------------" << endl;
                }
            }
            else{
                int count =0;
                int winnerIndex;
                for(int j=0; j<noOfPlyrs; j++){
                    if(!players[j].isBankrupt){
                        count++;
                        winnerIndex = j;
                    }
                }
                if(count == 1){
                    gameOver = true;
                    cout << "Game Over! " << players[winnerIndex].name << " wins!" << endl;
                    break;
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
    cout<<"4. Trade properties" << endl;
    cout<<"5. Declare bankruptcy" << endl;
    do{
        cin >> choice;
        cout << "Test: " << choice << endl;
        if(choice < 0 || choice > 5){
            cout<< "Invalid choice. Please enter a number between 0 and 5: ";
        }
    }while(choice < 0 || choice > 5);
    return choice;
}
void handleMenuChoice(int choice,int menuTemplateIndex, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int noOfPlyrs){ //Handle the action based on the user's menu choice
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
                tradeProperty(playerIndex, players, board, cities); //Handle trade properties action
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
void movePlayer(int* doublecount, bool* doubleRoll, int playerIndex, Player* players, Board* board, City* cities, int* chanceCards, int* communityChestCards, int* housesAvailable, int* hotelsAvailable, int noOfPlyrs){
    //Declare variables
    int* diceRoll = new int[2];
    int rollTotal;

    //Roll the dice
    cin.ignore(); //Ignore the newline character left in the input buffer
    cout << players[playerIndex].name << " is rolling the dice." << endl;
    cout << "Press Enter to Roll the dice..." << endl;
    cin.get(); //Wait for user to press Enter
    rollDice(diceRoll);
    cout << "Rolled a " << diceRoll[0] << " and a " << diceRoll[1] << "." << endl;
    rollTotal = diceRoll[0] + diceRoll[1];

    //Check for double roll
    if (diceRoll[0] == diceRoll[1]){
        cout << "Double roll! You rolled a " << diceRoll[0] << " and a " << diceRoll[1] << "." << endl;
        (*doublecount)++;
        if (*doublecount == 3){
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

        cout << "And you moved " << rollTotal << " spaces to ";
        if (players[playerIndex].position >= BOARD_SIZE){
            players[playerIndex].position -= BOARD_SIZE;
            cout << players[playerIndex].name << " at position " << players[playerIndex].position << "." << endl;
            if (players[playerIndex].position == 0){ //If the players lands exactly on Go, they collect salary for passing Go
                cout<< "You landed on Go! Collect $200." << endl;
            }
            else{
                cout<< "You passed Go! Collect $200." << endl;
            }
            players[playerIndex].balance += 200; //Collect $200 for passing Go
        }
        else cout << players[playerIndex].name << " at position " << players[playerIndex].position << "." << endl;
        locationAction(playerIndex, rollTotal, players, board, cities, chanceCards, communityChestCards); //Handle the action for landing on the new position
    }
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter
    deallocateMemory(diceRoll); //Deallocate the dynamically allocated diceRoll array
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
                    if (players[cities[propertyID].ownerIndex].inJail){
                        cout<< "You landed on " << cities[propertyID].name << " owned by " << players[cities[propertyID].ownerIndex].name << ", but they are currently in jail. No rent is due." << endl;
                    }
                    else if(cities[propertyID].isMortgaged){
                        cout<< "You landed on " << cities[propertyID].name << " owned by " << players[cities[propertyID].ownerIndex].name << ", but it is currently mortgaged. No rent is due." << endl;
                    }
                    else{
                        payRentOrTax(playerIndex, rollTotal, players, board, cities); //Pay rent to the owner (to be implemented)
                    }
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
            rentAmount = -200;
            break;
        case 7: //Luxury Tax
            cout<< "You landed on Luxury Tax. You must pay $100 in tax." << endl;
            rentAmount = -100;
            break;
        default:
            cout<< "Error: wrong type of property for rent payment" << endl;
            break;
    }
    if (propertyType == 6 || propertyType == 7){ //If the players landed on a tax space, they pay the bank instead of another players
        moneyTransaction(playerIndex, player, rentAmount); //Handle money transaction with the bank (to be implemented)
    }
    else{
        moneyTransaction(playerIndex, ownerIndex, player, rentAmount); //Handle money transaction with the property owner (to be implemented)
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
    if (players[playerIndex].balance + amount < 0){
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
    if (players[playerIndex].balance + amount < 0){
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
        if (cities[propertyID].groupID == 8){
            players[playerIndex].numRailroads++;
            players[playerIndex].railroadsOwned[players[playerIndex].numRailroads - 1] = propertyID; //Add the property to the player's owned properties array
        }
        else if (cities[propertyID].groupID == 9){
            players[playerIndex].numUtilities++;
            players[playerIndex].utilitiesOwned[players[playerIndex].numUtilities - 1] = propertyID; //Add the property to the player's owned properties array
        }
        else{
            players[playerIndex].numCities++;
            players[playerIndex].citiesOwned[players[playerIndex].numCities - 1] = propertyID; //Add the property to the player's owned properties array
            calculateGroupOwned(propertyID, playerIndex, players, cities); //Check if the player now owns all properties in the group and update group ownership status (to be implemented)
        }
        cout<< "You bought " << cities[propertyID].name << " for $" << propertyCost << "." << endl;
    }
}
void calculateGroupOwned(int propertyID, int playerIndex, Player* players, City* cities){
    int groupID = cities[propertyID].groupID;
    // Check if the player owns all properties in the group and update group ownership status
    bool ownsAllInGroup = true;
    for (int i=0; i<MAX_CITIES; i++){
        if (cities[i].groupID == groupID){
            if (!cities[i].isOwned || cities[i].ownerIndex != playerIndex){
                ownsAllInGroup = false;
                break;
            }
        }
    }
    if (ownsAllInGroup){
        players[playerIndex].groupOwned[groupID] = true; //Player owns all properties in the group
    }
    else{
        players[playerIndex].groupOwned[groupID] = false; //Player does not own all properties in the group
    }
}
void upgradeProperty(int playerIndex, int* housesAvailable, int* hotelsAvailable, Player* players, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to upgrade
    int propertyID; //ID of the property the players wants to upgrade
    int upgradeCost; //Cost of upgrading the property
    int groupID; //Group ID of the property the players wants to upgrade

    //Handle the process of upgrading a property when a players owns it and has enough money
    cout<< "Your properties: " << endl;
    for(int i=0; i<players[playerIndex].numCities; i++){
        cout<< i <<". " << cities[players[playerIndex].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to upgrade?" << endl;
    cin>> propertyNumber;
    propertyID = players[playerIndex].citiesOwned[propertyNumber];
    groupID = cities[propertyID].groupID;
    if (!players[playerIndex].groupOwned[groupID]){
        cout<< "You do not own all properties in this group and cannot upgrade." << endl;
    }
    else{
        if (cities[propertyID].upgradeLevel >= 5){
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
    for(int i=0; i<players[playerIndex].numCities; i++){
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
    float unmortgageCost; //Amount of money the player must pay to unmortgage the property

    //Handle the process of unmortgaging a property when a players owns it and has enough money
    cout<< "Your properties: " << endl;
    for(int i=0; i<players[playerIndex].numCities; i++){
        cout<< i <<". " << cities[players[playerIndex].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to unmortgage?" << endl;
    cin>> propertyNumber;
    propertyID = players[playerIndex].citiesOwned[propertyNumber];
    if (!cities[propertyID].isMortgaged){
        cout<< "This property is not mortgaged." << endl;
    }
    else{
        unmortgageCost = (cities[propertyID].cost / 2) * 1.1f; //Unmortgage cost is typically the mortgage value plus 10% interest
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
    //not sure if this function will be necessary since players can just mortgage properties to get money instead of selling them, but I will implement it just in case
    cout << "YOU ARE IN SELL PROPERTY FUNCTION"<<endl<<endl;
}
void tradeProperty(int playerIndex, Player* players, Board* board, City* cities){
    //declare variables
    int tradePartnerIndex; //Index of the player the current player wants to trade with
    char choice; //User choice for trading options
    int input; //General variable for user input in trading options
    int cashOffer = 0; //Amount of cash the player wants to offer in the trade
    int cashRequest = 0; //Amount of cash the player wants to request in return for the offer in the trade
    int* offeredPropertyID = new int[players[playerIndex].numCities]; //ID of the property the player wants to offer in the trade
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to offer in the trade

    //Handle the process of trading properties between players
    cout << "You chose to trade properties." << endl;
    cout << "Which player would you like to trade with?" << endl;
    cin >> tradePartnerIndex; //Get the index of the player to trade with (to be implemented)
    int* requestedPropertyID = new int[players[tradePartnerIndex].numCities]; //ID of the property the player wants to request in return for the offer in the trade

    cout << "You chose to trade with " << players[tradePartnerIndex].name << "." << endl;

    cout << "Here is your options for trading:" << endl;
    cout << "first: " << "would you like to see the list of your properties? (y/n)" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        listPlayerProperties(playerIndex, players, cities); //List the current player's properties (to be implemented)
    }
    cout << "second: " << "would you like to see the list of " << players[tradePartnerIndex].name << "'s properties? (y/n)" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        listPlayerProperties(tradePartnerIndex, players, cities); //List the trade partner player's properties (to be implemented)
    }
    cout << "third: ";

    char moreOffers;
    int offeredCounter = 0;
    do{
        cout << "what would you like to offer in the trade? " << endl;
        cout << "1. Cash" << endl;
        cout << "2. Property" << endl;
        cin >> choice;
        switch(choice){
            case '1':
                cout << "How much cash would you like to offer?" << endl;
                cin >> input;
                cashOffer += input;
                if (cashOffer > players[playerIndex].balance){
                    cout << "You cannot offer more cash than you have." << endl;
                    cashOffer -= input;
                }
                else{
                    cout << "Your total cash offer is $" << cashOffer << "." << endl;
                }
                break;
            case '2':
                cout << "Which property would you like to offer?" << endl;
                cin >> propertyNumber;
                if (propertyNumber < 0 || propertyNumber >= players[playerIndex].numProperties){
                    cout << "Invalid property number." << endl;
                }
                else{
                    offeredPropertyID[offeredCounter] = players[playerIndex].citiesOwned[propertyNumber];
                    cout << "You offered " << cities[offeredPropertyID[offeredCounter]].name << " in the trade." << endl;
                    offeredCounter++;
                }
                break;
            default:
                cout << "Invalid choice for trading options." << endl;
        }
        cout << "Would you like to offer more in the trade? (y/n)" << endl;
        cin >> moreOffers;
    }while(moreOffers == 'y' || moreOffers == 'Y');
    cout << "You offered a total of $" << cashOffer << " and the following properties in the trade:" << endl;
    for (int i=0; i<offeredCounter; i++){
        cout << "- " << cities[offeredPropertyID[i]].name << endl;
    }
    //Get the trade partner's response to the offer and handle the trade accordingly
    cout << "fourth: ";
     //Handle the process of requesting cash or properties in return for the offer and finalizing the trade based on the trade partner's response
    int requestedCounter = 0;
    do{
        cout << "What would you like to request in return for your offer?" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Property" << endl;
        cin >> choice;
        switch(choice){
            case '1':
                cout << "How much cash would you like to request?" << endl;
                cin >> input;
                cashRequest += input;
                if (cashRequest > players[tradePartnerIndex].balance){
                    cout << "You cannot request more cash than the trade partner has." << endl;
                    cashRequest -= input;
                }
                else{
                    cout << "Your total cash request is $" << cashRequest << " in return for your offer." << endl;
                }
                break;
            case '2':
                cout << "Which property would you like to request?" << endl;
                cin >> propertyNumber;
                if (propertyNumber < 0 || propertyNumber >= players[tradePartnerIndex].numProperties){
                    cout << "Invalid property number." << endl;
                }
                else{
                    cout << "You requested " << cities[players[tradePartnerIndex].citiesOwned[propertyNumber]].name << " in return for your offer." << endl;
                    requestedPropertyID[requestedCounter] = players[tradePartnerIndex].citiesOwned[propertyNumber];
                    cout << "You requested " << cities[requestedPropertyID[requestedCounter]].name << " in the trade." << endl;
                    requestedCounter++;
                }
                break;
            default:
                cout << "Invalid choice for trading options." << endl;
        }
        cout << "Would you like to request more in return for your offer? (y/n)" << endl;
        cin >> moreOffers;
    }while(moreOffers == 'y' || moreOffers == 'Y');
    //Handle the process of requesting cash or properties in return for the offer and finalizing the trade based on the trade partner's response
    cout << "You requested $" << cashRequest << " and the following properties in return for your offer:" << endl;
    for (int i=0; i<requestedCounter; i++){
        cout << "- " << cities[requestedPropertyID[i]].name << endl;
    }
     //Get the trade partner's response to the offer and handle the trade accordingly
     cout << "Does " << players[tradePartnerIndex].name << " accept this trade? (y/n)" << endl;
     cin >> choice;
     if (choice == 'y' || choice == 'Y'){
        //Handle the process of finalizing the trade by transferring cash and properties between the players based on the offer and request
        cout << players[tradePartnerIndex].name << " accepted the trade." << endl;
        moneyTransaction(playerIndex, tradePartnerIndex, players, cashOffer); //Handle cash transaction from current player to trade partner (to be implemented)
        moneyTransaction(tradePartnerIndex, playerIndex, players, cashRequest); //Handle cash transaction from trade partner to current player (to be implemented)
        for (int i=0; i<offeredCounter; i++){
            cities[offeredPropertyID[i]].ownerIndex = tradePartnerIndex; //Transfer ownership of offered properties to trade partner
            cout << "You transferred " << cities[offeredPropertyID[i]].name << " to " << players[tradePartnerIndex].name << "." << endl;
        }
        for (int i=0; i<requestedCounter; i++){
            cities[requestedPropertyID[i]].ownerIndex = playerIndex; //Transfer ownership of requested properties to current player
            cout << "You received " << cities[requestedPropertyID[i]].name << " from " << players[tradePartnerIndex].name << "." << endl;
        }
    }
    else{
        cout << players[tradePartnerIndex].name << " rejected the trade." << endl;
    }
    deallocateMemory(offeredPropertyID); //Deallocate the dynamically allocated offeredPropertyID array
    deallocateMemory(requestedPropertyID); //Deallocate the dynamically allocated requestedPropertyID array
}
void listPlayerProperties(int playerIndex, Player* players, City* cities){
    int counter = 0;
    cout << "Your properties: " << endl;
    for(int i=0; i<players[playerIndex].numCities; i++){
        cout<< counter <<". ";
        displayPropertyOneLiner(players[playerIndex].citiesOwned[i], cities);
        cout << endl;
        counter++;
    }
    for(int i=0; i<players[playerIndex].numRailroads; i++){
        cout<< counter <<". ";
        displayPropertyOneLiner(players[playerIndex].railroadsOwned[i], cities);
        cout << endl;
        counter++;
    }
    for(int i=0; i<players[playerIndex].numUtilities; i++){
        cout<< counter <<". ";
        displayPropertyOneLiner(players[playerIndex].utilitiesOwned[i], cities);
        cout << endl;
        counter++;
    }   
}
void displayPropertyOneLiner(int propertyID, City* cities){
    cout << cities[propertyID].name << " - " << cities[propertyID].cost << "$ - Rent: " << cities[propertyID].baseRent << "$ - Upgrade Cost: " << cities[propertyID].upgradeCost[0] << ", " << cities[propertyID].upgradeCost[1] << "$ - Group Id: " << cities[propertyID].groupID;
}
int declareBankruptcy(int playerIndex, int* housesAvailable, int* hotelsAvailable, Player* players, Board* board, City* cities){
    //declare variables
    int propertyID; //ID of the property the players wants to sell
    int totalAssetsPrice = 0; //Total value of the player's assets (cash + properties) to determine if they can pay what they owe or if they must declare bankruptcy
    
    //Handle the process of declaring bankruptcy and removing the player from the game when they cannot afford to pay what they owe
    players[playerIndex].isBankrupt = true; //Mark the player as bankrupt
    //Transfer the player's properties back to the bank and mark them as unowned
    for(int i=0; i<players[playerIndex].numCities; i++){
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
        cities[propertyID].isOwned = false; //Reset the group ownership status of the property
        cities[propertyID].ownerIndex = -1;
        totalAssetsPrice += cities[propertyID].cost; //Add the property's cost to the total assets price
    }
    for(int i=0; i<players[playerIndex].numRailroads; i++){
        propertyID = players[playerIndex].railroadsOwned[i];
        cities[propertyID].isOwned = false; //Reset the group ownership status of the property
        cities[propertyID].ownerIndex = -1;
    }
    for(int i=0; i<players[playerIndex].numUtilities; i++){
        propertyID = players[playerIndex].utilitiesOwned[i];
        cities[propertyID].isOwned = false; //Reset the group ownership status of the property
        cities[propertyID].ownerIndex = -1;
    }
    cout<< "You declared bankruptcy and are out of the game." << endl;
    return totalAssetsPrice; //Return the total value of the player's assets to determine if they can pay what they owe or if they must declare bankruptcy
}
void goToJail(int playerIndex, Player* players){
    players[playerIndex].position = 10; //Move the player to the Jail space
    players[playerIndex].inJail = true; //Mark the player as being in jail
    players[playerIndex].jailTurns = 0; //Reset the player's jail turn count
    cout << "You are now in jail." << endl;
}
void jailTurn(int playerIndex, Player* players, Board* board, City* cities){
    //Declare variables
    int choice; //User choice for how to get out of jail
    bool getoutOfJail = false; //Flag to indicate if the player has gotten out of jail
    int* diceRoll = new int[2]; //Array to store the results of rolling the dice

    do{
        cout << "You are in jail." << endl;
        cout << "Here are your options:" << endl;
        cout << "1. Try to roll doubles to get out of jail." << endl;
        cout << "2. Pay the fine to get out of jail." << endl;
        cout << "3. Use a 'Get Out of Jail Free' card. (if you have one)" << endl;
        cin  >> choice;
        switch(choice){
            case 1:
                //Handle trying to roll doubles to get out of jail
                cout << "You chose to try to roll doubles to get out of jail." << endl;
                cout << "Press Enter to roll the dice..." << endl;
                cin.ignore(); // Wait for the user to press Enter
                cin.get();
                rollDice(diceRoll); //Roll the dice
                cout << "You rolled a " << diceRoll[0] << " and a " << diceRoll[1] << "." << endl;
                if (diceRoll[0] == diceRoll[1]){ //Check if the player rolled doubles
                    cout << "You rolled doubles and got out of jail!" << endl;
                    getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                    players[playerIndex].jailTurns = 0; //Reset the player's jail turn count
                }
                else{
                    if (players[playerIndex].jailTurns == 2){ //If this is the player's third turn in jail, they must pay the fine and get out of jail
                        cout << "This is your third turn in jail. You must pay the fine to get out of jail." << endl;
                        moneyTransaction(playerIndex, players, -50); //Handle money transaction with the bank for paying the fine (to be implemented)
                        getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                        players[playerIndex].jailTurns = 0; //Reset the player's jail turn count
                    }
                    else{
                            cout << "You did not roll doubles." << endl;
                            players[playerIndex].jailTurns++; //Increment the player's jail turn count
                    }
                }
                break;
            case 2:
                //Handle paying the fine to get out of jail (to be implemented)
                cout << "You chose to pay the fine to get out of jail." << endl;
                moneyTransaction(playerIndex, players, -50); //Handle money transaction with the bank for paying the fine
                players[playerIndex].jailTurns = 0; //Reset the player's jail turn count
                getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                break;
            case 3:
                //Handle using a 'Get Out of Jail Free' card to get out of jail (to be implemented)
                cout << "You chose to use a 'Get Out of Jail Free' card." << endl;
                players[playerIndex].jailTurns = 0; //Reset the player's jail turn count
                getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                break;
        }
        if (getoutOfJail){
            players[playerIndex].inJail = false; //Mark the player as no longer being in jail
            cout << "You are now out of jail." << endl;
        }
    }while(choice < 1 || choice > 3); //Continue to prompt the player until they make a valid choice
    deallocateMemory(diceRoll); //Deallocate memory for the dice roll array    
}
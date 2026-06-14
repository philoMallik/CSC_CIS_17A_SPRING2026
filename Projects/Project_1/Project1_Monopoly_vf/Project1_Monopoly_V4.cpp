/*
Author: Philopatair Mallik
Date: 05/05/2026
purpose: Project 1 - Monopoly Game Simulation
*/
/*
version 4 updates:
changed names of some variables and functions for clarity and consistency
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
int const MAX_PLAYERS = 4;     //Maximum number of plyrs
int const MAX_CITIES = 22+4+2; //22 properties + 4 railroads + 2 utilities
int const MAX_CHANCE_CARDS = 16; //Number of Chance cards
int const MAX_COMMUNITY_CHEST_CARDS = 16; //Number of Community Chest cards
int const BOARD_SIZE = 40;         //Total number of spaces on the board

int const STARTINGBALANCE = 1500;  //Starting balance for each plyrs
int const SALARY = 200;            //Amount collected when passing Go


//Function Prototype
void initialization(string* files, City* cities, Board* board, int* chnceCrds, int* comuntyCrds); //Initialize cities, board, chance cards, and community chest cards from external files
City readCityFromFile(fstream &inFile, int id); //Read data for cities from external files
Board readBoardFromFile(fstream &inFile, int id); //Read data for board from external files

void deallocateMemory(Player* plyrs, City* cities, Board* board, int* chnceCrds, int* comuntyCrds); //Deallocate all dynamically allocated memory
void deallocateMemory(int* array); //Deallocate a dynamically allocated integer array
void deallocateMemory(string* array); //Deallocate a dynamically allocated string array

int  initializePlayers(Player* plyrs, int nOfPlyrs); //get number of plyrs and their names and initialize their starting data
void getOrderOfPlay(Player* plyrs, int nOfPlyrs); //determine the order in which plyrs will take their turns

void sortParallelArray(int *arr, Player* plyrs, int size); //Sort an array and a parallel array of plyrs based on the values in the first array
int binarySearch(int * array, int value); //search an array for value and return index
void sortArray(int *array, int size); //Sort an array
void randomizeArray(int *array, int size); //Randomize an array

void rollDice(int* diceR); //Simulate rolling two six-sided dice and return the results (1-6)

void mainGameLoop(Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds, int* nHouses, int* nHotels, int nOfPlyrs);
int showMenu(int nMenu); //Display a menu based on the provided template index and return the user's choice
void handleMenuChoice(int choice,int nMenu, int plyrInd, Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds, int* nHouses, int* nHotels, int nOfPlyrs); //Handle the action based on the user's menu choice
void movePlayer(int* dblcnt, bool* dblR, int plyrInd, Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds, int* nHouses, int* nHotels, int nOfPlyrs); //Move a player a specified number of steps on the board

void locationAction(int plyrInd, int rollTotal, Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds); //Handle the action when a plyrs lands on a city (e.g., buy property, pay rent, draw card, etc.)

void payRentOrTax(int plyrInd, int rollTotal, Player* player, Board* board, City* cities); //Handle rent or tax payment when a plyrs lands on a property owned by another player or on a tax space
void buyProperty(int plyrInd, Player* plyrs, Board* board, City* cities); //Handle the process of buying a property when a plyrs lands on an unowned property
void drawChanceCard(int plyrInd, Player* plyrs, int* chnceCrds, Board* board, City* cities); //Handle drawing a Chance card and executing its effect
void drawCommunityChestCard(int plyrInd, Player* plyrs, int* comuntyCrds, Board* board, City* cities); //Handle drawing a Community Chest card and executing its effect
void goToJail(int plyrInd, Player* plyrs); //Handle sending a plyrs to jail

void jailTurn(int plyrInd, Player* plyrs, Board* board, City* cities); //Handle a plyrs's turn when they are in jail (e.g., attempt to roll doubles, pay fine, use Get Out of Jail Free card, etc.)

void moneyTransaction(int frPlyrInd, int toPlyrInd, Player* plyrs, int amount); //Handle money transactions between plyrs (e.g., rent payment, property purchase, etc.) 
void moneyTransaction(int plyrInd, Player* plyrs, int amount); //Handle money transactions between plyrs and bank (e.g., salary collection, property purchase, etc.)
void handleLowBalance(int plyrInd, int amount, Player* plyrs, Board* board, City* cities); //Handle situations where a plyrs has low balance and needs to sell property, mortgage property, or declare bankruptcy

void upgradeProperty(int plyrInd, int* nHouses, int* nHotels, Player* plyrs, Board* board, City* cities);
void mortgageProperty(int plyrInd, Player* plyrs, Board* board, City* cities);
void unmortgageProperty(int plyrInd, Player* plyrs, Board* board, City* cities);
void sellProperty(int plyrInd, Player* plyrs, Board* board, City* cities);
void tradeProperty(int plyrInd, Player* plyrs, Board* board, City* cities); //Handle trading properties between plyrs
int declareBankruptcy(int plyrInd, int* nHouses, int* nHotels, Player* plyrs, Board* board, City* cities); //Handle bankruptcy declaration

void calculateGroupOwned(int propId, int plyrInd, Player* plyrs, City* cities); //Calculate how many properties in each color group a player owns and update the player's groupOwned array accordingly
void listPlayerProperties(int plyrInd, Player* plyrs, City* cities); //List the properties owned by a player
void displayPropertyOneLiner(int propId, City* cities); //Display a one-liner description of a property (e.g., name, rent, upgrade level, etc.) 

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    Player* plyrs = new Player[MAX_PLAYERS];
    City* cities = new City[MAX_CITIES];
    Board* board = new Board[BOARD_SIZE];
    int* chnceCrds = new int[MAX_CHANCE_CARDS];
    int* comuntyCrds = new int[MAX_COMMUNITY_CHEST_CARDS];

    int nPlyrs = MAX_PLAYERS;
    int nHouses = 32;
    int nHotels = 12;

    string* files = new string[4];
    files[0] = "CityData.bin";
    files[1] = "BoardData.bin";
    files[2] = "ChanceCardsData.bin";
    files[3] = "CommunityChestCardsData.bin";

    //Initialize Variables and game components
    initialization(files, cities, board, chnceCrds, comuntyCrds);


    //Start new game
    cout << "Welcome to Monopoly!" << endl;
    cout << "Starting a new game of Monopoly!" << endl;
    
    cout << "Press Enter to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    nPlyrs = initializePlayers(plyrs, nPlyrs);
    cout << "Number of plyrs: " << nPlyrs << endl;
    cin.ignore(); //Ignore the newline character left in the input buffer


    cout << "----------------------------------------" << endl;

    cout << "First, let's determine the order of play." << endl;
    cout << "Press Continue to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    getOrderOfPlay(plyrs, nPlyrs);

    //Enter main game loop
    mainGameLoop(plyrs, board, cities, chnceCrds, comuntyCrds, &nHouses, &nHotels, nPlyrs);

    //Deallocate all dynamically allocated memory at the end of the game
    deallocateMemory(plyrs, cities, board, chnceCrds, comuntyCrds);
    deallocateMemory(files);

    //Exit the program
    return 0;
};

void initialization(string* fileNames, City* cities, Board* board,
                    int* chnceCrds, int* comuntyCrds) {
    // Open once, read all cities
    fstream cityFile(fileNames[0], ios::in | ios::binary);
    if (!cityFile) {
        cerr << "Error: could not open " << fileNames[0] << endl;
        return;
    }
    for (int i = 0; i < MAX_CITIES; i++) {
        cities[i] = readCityFromFile(cityFile, i);
    }
    cityFile.close();

    // Open once, read all boards
    fstream boardFile(fileNames[1], ios::in | ios::binary);
    if (!boardFile) {
        cerr << "Error: could not open " << fileNames[1] << endl;
        return;
    }
    for (int i = 0; i < MAX_BOARD_SPACES; i++) {
        board[i] = readBoardFromFile(boardFile, i);
    }
    boardFile.close();
}
City readCityFromFile(fstream& inFile, int id) {
    City city;
    long cursor = id * sizeof(City);
    inFile.seekg(cursor, ios::beg);
    inFile.read(reinterpret_cast<char*>(&city), sizeof(City));
    return city;
}

Board readBoardFromFile(fstream& inFile, int id) {
    Board board;
    long cursor = id * sizeof(Board);
    inFile.seekg(cursor, ios::beg);
    inFile.read(reinterpret_cast<char*>(&board), sizeof(Board));
    return board;
}
void deallocateMemory(Player* plyrs, City* cities, Board* board, int* chnceCrds, int* comuntyCrds){
    for(int i=0; i<MAX_PLAYERS; i++){
        delete[] plyrs[i].citiesOwned;
        delete[] plyrs[i].railroadsOwned;
        delete[] plyrs[i].utilitiesOwned;
        delete[] plyrs[i].groupOwned;
        delete[] plyrs[i].upgradesOwned;
    }
    delete[] plyrs;
    delete[] cities;
    delete[] board;
    delete[] chnceCrds;
    delete[] comuntyCrds;
}
void deallocateMemory(int* array){
    delete[] array;
}
void deallocateMemory(string* array){
    delete[] array;
}
int initializePlayers(Player* plyrs, int nPlyrs){
    //Get number of plyrs and their names, initialize their attributes
    cout<< "How many plyrs are playing? (2-4): ";
    cin>> nPlyrs;
    for(int i=0; i<nPlyrs; i++){
        cout<< "Enter name for Player " << (i+1) << ": ";
        cin>> plyrs[i].name;
        plyrs[i].id = i;
        plyrs[i].balance = STARTINGBALANCE;
        plyrs[i].position = 0; //Start at Go
        plyrs[i].citiesOwned = new int[22]; //Dynamically allocate array for owned cities
        for (int j=0; j<22; j++){
            plyrs[i].citiesOwned[j] = -1; //Initialize all city ownership to -1 (indicating no ownership)
        }
        plyrs[i].railroadsOwned = new int[4]; //Dynamically allocate array for owned railroads
        for (int j=0; j<4; j++){
            plyrs[i].railroadsOwned[j] = -1; //Initialize all railroad ownership to -1 (indicating no ownership)
        }
        plyrs[i].utilitiesOwned = new int[2]; //Dynamically allocate array for owned utilities
        for (int j=0; j<2; j++){
            plyrs[i].utilitiesOwned[j] = -1; //Initialize all utility ownership to -1 (indicating no ownership)
        }
        plyrs[i].groupOwned = new bool[10]; //Dynamically allocate and initialize array to track group ownership
        for (int j=0; j<10; j++){
            plyrs[i].groupOwned[j] = false; //Initialize all group ownership counts to false
        }
        plyrs[i].upgradesOwned = new int[2]; //Dynamically allocate and initialize array to track upgrades owned
        for (int j=0; j<2; j++){
            plyrs[i].upgradesOwned[j] = 0; //Initialize all upgrade counts to 0
        }
        plyrs[i].numRailroads = 0;
        plyrs[i].numUtilities = 0;
        plyrs[i].numCities = 0;
        plyrs[i].inJail = false;
        plyrs[i].jailTurns = 0;
        plyrs[i].netWorth = STARTINGBALANCE; //Initial net worth is just the starting balance
        plyrs[i].isBankrupt = false;
 
    } 
    return nPlyrs; 
}
void getOrderOfPlay(Player* plyrs, int nPlyrs){
    //Declare Variables
    int *rolls = new int[MAX_PLAYERS];
    int* diceR = new int[2];

    //Roll dice for each player to determine order of play
    cout<< "Determining order of play by rolling dice..." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

    for(int i=0; i<nPlyrs; i++){
        cout << plyrs[i].name << " is rolling the dice..." << endl;
        cout<< "Press Enter to roll the dice...";
        cin.get(); //Wait for user input to roll the dice
        rollDice(diceR);
        rolls[i] = diceR[0] + diceR[1]; //Sum of the two dice
        cout<< plyrs[i].name << " rolled a " << rolls[i] << endl;
        cout << "----------------------------------------" << endl;
    }
    //Sort the rolls to determine order of play
    sortParallelArray(rolls, plyrs, nPlyrs); //Sort the rolls and the plyrs array in parallel based on the rolls
    cout<< "Order of play based on dice rolls: " << endl;
    for(int i=0; i<nPlyrs; i++){
        cout<< plyrs[i].name << " (" << rolls[i] << ")" << endl;
    }
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

    deallocateMemory(rolls); //Deallocate the dynamically allocated rolls array    
    deallocateMemory(diceR); //Deallocate the dynamically allocated diceR array
}
void rollDice(int* diceR){ //Simulate rolling two six-sided dice and store the results in the provided array
    diceR[0] = rand() % 6 + 1; //Random number between 1 and 6
    diceR[1] = rand() % 6 + 1; //Random number between 1 and 6
}
void sortParallelArray(int *arr, Player* plyrs, int size){ //Sort an array and a parallel array of plyrs based on the values in the first array
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

                //Swap the corresponding plyrs in the parallel array
                tempPlayer = plyrs[j];
                plyrs[j] = plyrs[j+1];
                plyrs[j+1] = tempPlayer;
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
    int randInd; //Random index for swapping
    int temp; //Temporary variable for swapping
    
    //Randomly shuffle the array
    for(int i=0; i<size; i++){
        randInd = rand() % size; //Random index between 0 and size-1
        temp = arr[i];
        arr[i] = arr[randInd];
        arr[randInd] = temp;
    }
}
void mainGameLoop(Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds, int* nHouses, int* nHotels, int nPlyrs){
    //Declare variables for the main game loop
    bool gameOver = false;
    bool dblR = false;
    int dblcnt = 0;

    //Main game loop logic will be implemented here
    do{
        for(int i=0; i<nPlyrs; i++){
            if(!plyrs[i].isBankrupt){
                if(plyrs[i].inJail){
                    //do jail turn logic
                    cout << "IN JAIL" << endl;
                    jailTurn(i, plyrs, board, cities);
                    cout << "----------------------------------------" << endl;
                }
                else{
                    dblcnt = 0;
                    cout << "It's " << plyrs[i].name << "'s turn." << endl;
                    cout << "----------------------------------------" << endl;

                    do{
                        handleMenuChoice(showMenu(0), 0, i, plyrs, board, cities, chnceCrds, comuntyCrds, nHouses, nHotels, nPlyrs);
                        movePlayer(&dblcnt, &dblR, i, plyrs, board, cities, chnceCrds, comuntyCrds, nHouses, nHotels, nPlyrs);
                    }while(dblR);
                    handleMenuChoice(showMenu(1), 1, i, plyrs, board, cities, chnceCrds, comuntyCrds, nHouses, nHotels, nPlyrs);
                    cout << "End of " << plyrs[i].name << "'s turn." << endl;
                    cout << "----------------------------------------" << endl;
                }
            }
            else{
                int count =0;
                int wnrInd;
                for(int j=0; j<nPlyrs; j++){
                    if(!plyrs[j].isBankrupt){
                        count++;
                        wnrInd = j;
                    }
                }
                if(count == 1){
                    gameOver = true;
                    cout << "Game Over! " << plyrs[wnrInd].name << " wins!" << endl;
                    break;
                }
            }
            //else skip
        }
        cout << "Press Enter to continue..." << endl;
        cin.get(); //Wait for user to press Enter

    }while(!gameOver);

}
int showMenu(int nMenu){
    //Declare Variables
    int choice;

    //Display menu options based on the menu template index
    cout<<"0. " << (nMenu==0 ? "Roll the dice" : "End turn") << endl;
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
void handleMenuChoice(int choice,int nMenu, int plyrInd, Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds, int* nHouses, int* nHotels, int nPlyrs){ //Handle the action based on the user's menu choice
    bool endTurn = false;

    do{
        switch(choice){
            case 0: //return to main where case 0 is done
                break;
            case 1:
                upgradeProperty(plyrInd, nHouses, nHotels, plyrs, board, cities); //Handle upgrade property action
                break;
            case 2:
                mortgageProperty(plyrInd, plyrs, board, cities); //Handle mortgage property action
                break;
            case 3:
                unmortgageProperty(plyrInd, plyrs, board, cities); //Handle unmortgage property action
                break;
            case 4:
                tradeProperty(plyrInd, plyrs, board, cities); //Handle trade properties action
                break;
            case 5:
                declareBankruptcy(plyrInd, nHouses, nHotels, plyrs, board, cities); //Handle declare bankruptcy action
                break;
            default:
                //Handle invalid choice
                cout << "Error: Invalid choice in handleMenuChoice function." << endl;
                break;
        }
        if(choice != 0){
            choice = showMenu(nMenu);
        } 
        if (plyrs[plyrInd].isBankrupt) endTurn = true;
        if (plyrs[plyrInd].inJail) endTurn = true;
    }while(choice!=0 && !endTurn);
}
void movePlayer(int* dblcnt, bool* dblR, int plyrInd, Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds, int* nHouses, int* nHotels, int nPlyrs){
    //Declare variables
    int* diceR = new int[2];
    int rollTot;

    //Roll the dice
    cin.ignore(); //Ignore the newline character left in the input buffer
    cout << plyrs[plyrInd].name << " is rolling the dice." << endl;
    cout << "Press Enter to Roll the dice..." << endl;
    cin.get(); //Wait for user to press Enter
    rollDice(diceR);
    cout << "Rolled a " << diceR[0] << " and a " << diceR[1] << "." << endl;
    rollTot = diceR[0] + diceR[1];

    //Check for double roll
    if (diceR[0] == diceR[1]){
        cout << "Double roll! You rolled a " << diceR[0] << " and a " << diceR[1] << "." << endl;
        (*dblcnt)++;
        if (*dblcnt == 3){
            //go to jail
            cout << "You rolled doubles three times in a row and are going to jail!" << endl;
            plyrs[plyrInd].inJail = true;
        }
        else{
            *dblR = true;
        }
    }
    else *dblR = false;

    //Move a player a specified number of steps on the board
    if (!plyrs[plyrInd].inJail){
        plyrs[plyrInd].position += rollTot;

        cout << "And you moved " << rollTot << " spaces to ";
        if (plyrs[plyrInd].position >= BOARD_SIZE){
            plyrs[plyrInd].position -= BOARD_SIZE;
            cout << board[plyrs[plyrInd].position].name << " at position " << plyrs[plyrInd].position << "." << endl;
            if (plyrs[plyrInd].position == 0){ //If the plyrs lands exactly on Go, they collect salary for passing Go
                cout<< "You landed on Go! Collect $200." << endl;
            }
            else{
                cout<< "You passed Go! Collect $200." << endl;
            }
            plyrs[plyrInd].balance += 200; //Collect $200 for passing Go
        }
        else cout << board[plyrs[plyrInd].position].name << " at position " << plyrs[plyrInd].position << "." << endl;
        locationAction(plyrInd, rollTot, plyrs, board, cities, chnceCrds, comuntyCrds); //Handle the action for landing on the new position
    }
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter
    deallocateMemory(diceR); //Deallocate the dynamically allocated diceR array
}
void locationAction(int plyrInd, int rollTot, Player* plyrs, Board* board, City* cities, int* chnceCrds, int* comuntyCrds){
    //Declare Variables
        int propId; //ID of the property the plyrs landed on
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
    
    switch (board[plyrs[plyrInd].position].type){
        case 0: //already handled on movePlayer function
            break;
        case 1:
        case 2:
        case 3:
            propId = board[plyrs[plyrInd].position].propertyID;
            if(cities[propId].ownerIndex != -1){ //If the property is owned by another player, pay rent
                if(cities[propId].ownerIndex != plyrInd){
                    if (plyrs[cities[propId].ownerIndex].inJail){
                        cout<< "You landed on " << cities[propId].name << " owned by " << plyrs[cities[propId].ownerIndex].name << ", but they are currently in jail. No rent is due." << endl;
                    }
                    else if(cities[propId].isMortgaged){
                        cout<< "You landed on " << cities[propId].name << " owned by " << plyrs[cities[propId].ownerIndex].name << ", but it is currently mortgaged. No rent is due." << endl;
                    }
                    else{
                        payRentOrTax(plyrInd, rollTot, plyrs, board, cities); //Pay rent to the owner (to be implemented)
                    }
                }
                else{
                    cout<< "You landed on your own property." << endl;
                }
            }
            else{
                cout << "You landed on " << cities[propId].name << ", which is unowned." << endl;
                cout << "Would you like to buy it for $" << cities[propId].cost << "? (y/n): " << endl;
                cin >> choice;
                if(choice == 'y' || choice == 'Y'){
                    buyProperty(plyrInd, plyrs, board, cities); //Handle buying the property (to be implemented)
                }
            }
            break;
        case 4:
            drawChanceCard(plyrInd, plyrs, chnceCrds, board, cities); //Handle drawing a Chance card (to be implemented)
            break;
        case 5:
            drawCommunityChestCard(plyrInd, plyrs, comuntyCrds, board, cities); //Handle drawing a Community Chest card (to be implemented)
            break;
        case 6:
            payRentOrTax(plyrInd, rollTot, plyrs, board, cities); //Handle paying income tax (to be implemented)
            break;
        case 7:
            payRentOrTax(plyrInd, rollTot, plyrs, board, cities); //Handle paying luxury tax (to be implemented)
            break;
        case 8:
            cout<< "Visiting jail, Say Hi if anyone there." << endl;
            break;
        case 9:
            cout<< "Free Parking." << endl;
            break;
        case 10:
            goToJail(plyrInd, plyrs);
            break;
        default:
            cout<< "Error: wrong type of board location (error in locationAction function)" << endl;
            break;
    }
}
void payRentOrTax(int plyrInd, int rollTot, Player* player, Board* board, City* cities){
    //declare variables
    int rentAmount; //Amount of rent to be paid
    int ownerIndex; //Index of the owner of the property
    int propertyType; //Type of the property the plyrs landed on

    //initrialize variables
    rentAmount = cities[board[player[plyrInd].position].propertyID].houseRent[cities[board[player[plyrInd].position].propertyID].upgradeLevel]; //Base rent amount based on the property's upgrade level
    ownerIndex = cities[board[player[plyrInd].position].propertyID].ownerIndex;
    propertyType = board[player[plyrInd].position].type;

    //Handle rent payment when a plyrs lands on an owned property
    switch(propertyType){
        case 1: //City
            cout<< "You landed on " << cities[board[player[plyrInd].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
            rentAmount = cities[board[player[plyrInd].position].propertyID].houseRent[cities[board[player[plyrInd].position].propertyID].upgradeLevel];
            break;
        case 2: //Railroad
            cout<< "You landed on " << cities[board[player[plyrInd].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
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
            cout<< "You landed on " << cities[board[player[plyrInd].position].propertyID].name << " owned by " << player[ownerIndex].name << ". You must pay $" << rentAmount << " in rent." << endl;
            if(player[ownerIndex].numUtilities == 1){
                rentAmount = (rollTot * 4);
            }
            else if(player[ownerIndex].numUtilities == 2){
                rentAmount = (rollTot * 10);
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
    if (propertyType == 6 || propertyType == 7){ //If the plyrs landed on a tax space, they pay the bank instead of another plyrs
        moneyTransaction(plyrInd, player, rentAmount); //Handle money transaction with the bank (to be implemented)
    }
    else{
        moneyTransaction(plyrInd, ownerIndex, player, rentAmount); //Handle money transaction with the property owner (to be implemented)
        if (!player[plyrInd].isBankrupt){
            cout<< "You paid $" << rentAmount << " in rent to " << player[ownerIndex].name << "." << endl;
        }
    }
}
void drawChanceCard(int plyrInd, Player* plyrs, int* chnceCrds, Board* board, City* cities){
    cout << "YOU ARE IN DRAW CHANCE CARD FUNCTION" << endl;
}
void drawCommunityChestCard(int plyrInd, Player* plyrs, int* comuntyCrds, Board* board, City* cities){
    cout << "YOU ARE IN DRAW COMMUNITY CHEST CARD FUNCTION" << endl;
}
void moneyTransaction(int plyrInd, int recipientIndex, Player* plyrs, int amount){ //Handle money transactions between plyrs (e.g., rent payment, property purchase, etc.) 
    if (plyrs[plyrInd].balance + amount < 0){
        cout<< "You cannot afford to pay. You must sell property or declare bankruptcy." << endl;
        handleLowBalance(plyrInd, amount, plyrs, nullptr, nullptr); //Handle low balance situation (to be implemented)
    }
    if (plyrs[plyrInd].isBankrupt){
        cout<< "You are bankrupt and cannot pay what you owe." << endl;
    }
    else{
    plyrs[plyrInd].balance -= amount; //Deduct the amount from the payer's balance
    plyrs[recipientIndex].balance += amount; //Add the amount to the recipient's balance
    }
}
void moneyTransaction(int plyrInd, Player* plyrs, int amount){ //Handle money transactions between plyrs and bank (e.g., salary collection, property purchase, etc.)
    if (plyrs[plyrInd].balance + amount < 0){
        cout<< "You cannot afford to pay. You must sell property or declare bankruptcy." << endl;
        handleLowBalance(plyrInd, amount, plyrs, nullptr, nullptr); //Handle low balance situation (to be implemented)
    }
    if (plyrs[plyrInd].isBankrupt){
        cout<< "You are bankrupt and cannot pay what you owe." << endl;
    }
    else{
    plyrs[plyrInd].balance += amount; //Add the amount to the player's balance (for salary collection) or deduct the amount from the player's balance (for property purchase)
    }
}
void handleLowBalance(int plyrInd, int amount, Player* plyrs, Board* board, City* cities){
    cout << "YOU ARE IN HANDLE LOW BALANCE FUNCTION"<<endl<<endl;
}
void buyProperty(int plyrInd, Player* plyrs, Board* board, City* cities){
    //declare variables
    int propId; //ID of the property the plyrs wants to buy
    int propertyCost; //Cost of the property the plyrs wants to buy

    //Handle the process of buying a property when a plyrs lands on an unowned property
    propId = board[plyrs[plyrInd].position].propertyID;
    propertyCost = cities[propId].cost;
    if (plyrs[plyrInd].isBankrupt){
        cout<< "You are bankrupt and cannot buy this property." << endl;
    }
    else if (plyrs[plyrInd].balance < propertyCost){
        cout<< "You cannot afford to buy this property." << endl;
    }
    else{
        moneyTransaction(plyrInd, plyrs, -1*propertyCost); //Handle money transaction with the bank for property purchase (to be implemented)
        cities[propId].ownerIndex = plyrInd; //Set the owner index for the city
        plyrs[plyrInd].numProperties++; //Increment the number of properties owned by the player
        if (cities[propId].groupID == 8){
            plyrs[plyrInd].numRailroads++;
            plyrs[plyrInd].railroadsOwned[plyrs[plyrInd].numRailroads - 1] = propId; //Add the property to the player's owned properties array
        }
        else if (cities[propId].groupID == 9){
            plyrs[plyrInd].numUtilities++;
            plyrs[plyrInd].utilitiesOwned[plyrs[plyrInd].numUtilities - 1] = propId; //Add the property to the player's owned properties array
        }
        else{
            plyrs[plyrInd].numCities++;
            plyrs[plyrInd].citiesOwned[plyrs[plyrInd].numCities - 1] = propId; //Add the property to the player's owned properties array
            calculateGroupOwned(propId, plyrInd, plyrs, cities); //Check if the player now owns all properties in the group and update group ownership status (to be implemented)
        }
        cout<< "You bought " << cities[propId].name << " for $" << propertyCost << "." << endl;
    }
}
void calculateGroupOwned(int propId, int plyrInd, Player* plyrs, City* cities){
    int groupID = cities[propId].groupID;
    // Check if the player owns all properties in the group and update group ownership status
    bool ownsAllInGroup = true;
    for (int i=0; i<MAX_CITIES; i++){
        if (cities[i].groupID == groupID){
            if (cities[i].ownerIndex == -1 || cities[i].ownerIndex != plyrInd){
                ownsAllInGroup = false;
                break;
            }
        }
    }
    if (ownsAllInGroup){
        plyrs[plyrInd].groupOwned[groupID] = true; //Player owns all properties in the group
    }
    else{
        plyrs[plyrInd].groupOwned[groupID] = false; //Player does not own all properties in the group
    }
}
void upgradeProperty(int plyrInd, int* nHouses, int* nHotels, Player* plyrs, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to upgrade
    int propId; //ID of the property the plyrs wants to upgrade
    int upgradeCost; //Cost of upgrading the property
    int groupID; //Group ID of the property the plyrs wants to upgrade

    //Handle the process of upgrading a property when a plyrs owns it and has enough money
    cout<< "Your properties: " << endl;
    for(int i=0; i<plyrs[plyrInd].numCities; i++){
        cout<< i <<". " << cities[plyrs[plyrInd].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to upgrade?" << endl;
    cin>> propertyNumber;
    propId = plyrs[plyrInd].citiesOwned[propertyNumber];
    groupID = cities[propId].groupID;
    if (!plyrs[plyrInd].groupOwned[groupID]){
        cout<< "You do not own all properties in this group and cannot upgrade." << endl;
    }
    else{
        if (cities[propId].upgradeLevel >= 5){
            cout << "This property already has a hotel and cannot be upgraded further." << endl;
        }
        else if (cities[propId].upgradeLevel == 4){
            if (*nHotels <= 0){
                cout<< "There are no hotels available to upgrade this property." << endl;
            }
            else{
                if (cities[propId].upgradeLevel > cities[propId].groupMinimumUpgradeLevel){
                    cout<< "You must upgrade the other properties in this group to the same level before upgrading this property." << endl;
                }
                else{
                    moneyTransaction(plyrInd, plyrs, -1*cities[propId].upgradeCost); //Handle money transaction with the bank for property upgrade (to be implemented)
                    cities[propId].upgradeLevel++; //Upgrade the property
                    (*nHotels)--; //Decrement the number of hotels available
                    (*nHouses) += 4; //Return the 4 houses used for the upgrade back to the pool of available houses
                    cout<< "You upgraded " << cities[propId].name << " to a hotel for $" << cities[propId].upgradeCost << "." << endl;
                }
            }
        }
        else{
            if (*nHouses <= 0){
                cout<< "There are no houses available to upgrade this property." << endl;
            }
            else{
                if (cities[propId].upgradeLevel > cities[propId].groupMinimumUpgradeLevel){
                    cout<< "You must upgrade the other properties in this group to the same level before upgrading this property." << endl;
                }
                else{
                    moneyTransaction(plyrInd, plyrs, -1*cities[propId].upgradeCost); //Handle money transaction with the bank for property upgrade (to be implemented)
                    cities[propId].upgradeLevel++; //Upgrade the property
                    (*nHouses)--; //Decrement the number of houses available
                    cout<< "You upgraded " << cities[propId].name << " to a house for $" << cities[propId].upgradeCost << "." << endl;
                }
            }
        }
    }

}
void mortgageProperty(int plyrInd, Player* plyrs, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to mortgage
    int propId; //ID of the property the plyrs wants to mortgage
    int mortgageValue; //Amount of money the player receives from mortgaging the property

    //Handle the process of mortgaging a property when a plyrs owns it and needs money
    cout<< "Your properties: " << endl;
    for(int i=0; i<plyrs[plyrInd].numCities; i++){
        cout<< i <<". " << cities[plyrs[plyrInd].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to mortgage?" << endl;
    cin>> propertyNumber;
    propId = plyrs[plyrInd].citiesOwned[propertyNumber];
    if (cities[propId].isMortgaged){
        cout<< "This property is already mortgaged." << endl;
    }
    else{
        mortgageValue = cities[propId].cost / 2; //Mortgage value is typically half the cost of the property
        moneyTransaction(plyrInd, plyrs, mortgageValue); //Handle money transaction with the bank for mortgaging the property (to be implemented)
        cities[propId].isMortgaged = true; //Mark the city as mortgaged
        cout<< "You mortgaged " << cities[propId].name << " for $" << mortgageValue << "." << endl;
    }
}
void unmortgageProperty(int plyrInd, Player* plyrs, Board* board, City* cities){
    //declare variables
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to unmortgage
    int propId; //ID of the property the plyrs wants to unmortgage
    float unmortgageCost; //Amount of money the player must pay to unmortgage the property

    //Handle the process of unmortgaging a property when a plyrs owns it and has enough money
    cout<< "Your properties: " << endl;
    for(int i=0; i<plyrs[plyrInd].numCities; i++){
        cout<< i <<". " << cities[plyrs[plyrInd].citiesOwned[i]].name << endl;
    }
    cout<< "Which property would you like to unmortgage?" << endl;
    cin>> propertyNumber;
    propId = plyrs[plyrInd].citiesOwned[propertyNumber];
    if (!cities[propId].isMortgaged){
        cout<< "This property is not mortgaged." << endl;
    }
    else{
        unmortgageCost = (cities[propId].cost / 2) * 1.1f; //Unmortgage cost is typically the mortgage value plus 10% interest
        if (plyrs[plyrInd].balance < unmortgageCost){
            cout<< "You cannot afford to unmortgage this property." << endl;
        }
        else{
            moneyTransaction(plyrInd, plyrs, -1*unmortgageCost); //Handle money transaction with the bank for unmortgaging the property (to be implemented)
            cities[propId].isMortgaged = false; //Mark the city as unmortgaged
            cout<< "You unmortgaged " << cities[propId].name << " for $" << unmortgageCost << "." << endl;
        }
    }
}
void sellProperty(int plyrInd, Player* plyrs, Board* board, City* cities){
    //not sure if this function will be necessary since plyrs can just mortgage properties to get money instead of selling them, but I will implement it just in case
    cout << "YOU ARE IN SELL PROPERTY FUNCTION"<<endl<<endl;
}
void tradeProperty(int plyrInd, Player* plyrs, Board* board, City* cities){
    //declare variables
    int tradePartnerIndex; //Index of the player the current player wants to trade with
    char choice; //User choice for trading options
    int input; //General variable for user input in trading options
    int cashOffer = 0; //Amount of cash the player wants to offer in the trade
    int cashRequest = 0; //Amount of cash the player wants to request in return for the offer in the trade
    int* offeredPropertyID = new int[plyrs[plyrInd].numCities]; //ID of the property the player wants to offer in the trade
    int propertyNumber; //Number of the property in the player's owned properties array that the player wants to offer in the trade

    //Handle the process of trading properties between plyrs
    cout << "You chose to trade properties." << endl;
    cout << "Which player would you like to trade with?" << endl;
    cin >> tradePartnerIndex; //Get the index of the player to trade with (to be implemented)
    int* requestedPropertyID = new int[plyrs[tradePartnerIndex].numCities]; //ID of the property the player wants to request in return for the offer in the trade

    cout << "You chose to trade with " << plyrs[tradePartnerIndex].name << "." << endl;

    cout << "Here is your options for trading:" << endl;
    cout << "first: " << "would you like to see the list of your properties? (y/n)" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        listPlayerProperties(plyrInd, plyrs, cities); //List the current player's properties (to be implemented)
    }
    cout << "second: " << "would you like to see the list of " << plyrs[tradePartnerIndex].name << "'s properties? (y/n)" << endl;
    cin >> choice;
    if (choice == 'y' || choice == 'Y'){
        listPlayerProperties(tradePartnerIndex, plyrs, cities); //List the trade partner player's properties (to be implemented)
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
                if (cashOffer > plyrs[plyrInd].balance){
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
                if (propertyNumber < 0 || propertyNumber >= plyrs[plyrInd].numProperties){
                    cout << "Invalid property number." << endl;
                }
                else{
                    offeredPropertyID[offeredCounter] = plyrs[plyrInd].citiesOwned[propertyNumber];
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
                if (cashRequest > plyrs[tradePartnerIndex].balance){
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
                if (propertyNumber < 0 || propertyNumber >= plyrs[tradePartnerIndex].numProperties){
                    cout << "Invalid property number." << endl;
                }
                else{
                    cout << "You requested " << cities[plyrs[tradePartnerIndex].citiesOwned[propertyNumber]].name << " in return for your offer." << endl;
                    requestedPropertyID[requestedCounter] = plyrs[tradePartnerIndex].citiesOwned[propertyNumber];
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
     cout << "Does " << plyrs[tradePartnerIndex].name << " accept this trade? (y/n)" << endl;
     cin >> choice;
     if (choice == 'y' || choice == 'Y'){
        //Handle the process of finalizing the trade by transferring cash and properties between the plyrs based on the offer and request
        cout << plyrs[tradePartnerIndex].name << " accepted the trade." << endl;
        moneyTransaction(plyrInd, tradePartnerIndex, plyrs, cashOffer); //Handle cash transaction from current player to trade partner (to be implemented)
        moneyTransaction(tradePartnerIndex, plyrInd, plyrs, cashRequest); //Handle cash transaction from trade partner to current player (to be implemented)
        for (int i=0; i<offeredCounter; i++){
            cities[offeredPropertyID[i]].ownerIndex = tradePartnerIndex; //Transfer ownership of offered properties to trade partner
            cout << "You transferred " << cities[offeredPropertyID[i]].name << " to " << plyrs[tradePartnerIndex].name << "." << endl;
        }
        for (int i=0; i<requestedCounter; i++){
            cities[requestedPropertyID[i]].ownerIndex = plyrInd; //Transfer ownership of requested properties to current player
            cout << "You received " << cities[requestedPropertyID[i]].name << " from " << plyrs[tradePartnerIndex].name << "." << endl;
        }
    }
    else{
        cout << plyrs[tradePartnerIndex].name << " rejected the trade." << endl;
    }
    deallocateMemory(offeredPropertyID); //Deallocate the dynamically allocated offeredPropertyID array
    deallocateMemory(requestedPropertyID); //Deallocate the dynamically allocated requestedPropertyID array
}
void listPlayerProperties(int plyrInd, Player* plyrs, City* cities){
    int counter = 0;
    cout << "Your properties: " << endl;
    for(int i=0; i<plyrs[plyrInd].numCities; i++){
        cout<< counter <<". ";
        displayPropertyOneLiner(plyrs[plyrInd].citiesOwned[i], cities);
        cout << endl;
        counter++;
    }
    for(int i=0; i<plyrs[plyrInd].numRailroads; i++){
        cout<< counter <<". ";
        displayPropertyOneLiner(plyrs[plyrInd].railroadsOwned[i], cities);
        cout << endl;
        counter++;
    }
    for(int i=0; i<plyrs[plyrInd].numUtilities; i++){
        cout<< counter <<". ";
        displayPropertyOneLiner(plyrs[plyrInd].utilitiesOwned[i], cities);
        cout << endl;
        counter++;
    }   
}
void displayPropertyOneLiner(int propId, City* cities){
    cout << cities[propId].name << " - " << cities[propId].cost << "$ - Rent: " << cities[propId].houseRent[0] << "$ - Upgrade Cost: " << cities[propId].upgradeCost << "$ - Group Id: " << cities[propId].groupID;
}
int declareBankruptcy(int plyrInd, int* nHouses, int* nHotels, Player* plyrs, Board* board, City* cities){
    //declare variables
    int propId; //ID of the property the plyrs wants to sell
    int totalAssetsPrice = 0; //Total value of the player's assets (cash + properties) to determine if they can pay what they owe or if they must declare bankruptcy
    
    //Handle the process of declaring bankruptcy and removing the player from the game when they cannot afford to pay what they owe
    plyrs[plyrInd].isBankrupt = true; //Mark the player as bankrupt
    //Transfer the player's properties back to the bank and mark them as unowned
    for(int i=0; i<plyrs[plyrInd].numCities; i++){
        propId = plyrs[plyrInd].citiesOwned[i];
        cities[propId].ownerIndex = -1;
        if (cities[propId].isMortgaged){
            cities[propId].isMortgaged = false; //Unmortgage the property when transferring it back to the bank
            totalAssetsPrice -= cities[propId].cost / 2 * 1.1; //remove the mortgage value from the total assets price
        }
        if (cities[propId].upgradeLevel > 0){
            if (cities[propId].upgradeLevel == 5){
                (*nHotels)++; //Return the hotel used for the upgrade back to the pool of available hotels
                (*nHouses) += 4; //Return the 4 houses used for the upgrade back to the pool of available houses
                totalAssetsPrice += (cities[propId].upgradeCost * 4) + cities[propId].upgradeCost; //Add the value of the upgrades to the total assets price
            }
            else{
                (*nHouses) += cities[propId].upgradeLevel; //Return the houses used for the upgrade back to the pool of available houses
                totalAssetsPrice += cities[propId].upgradeCost * cities[propId].upgradeLevel; //Add the value of the upgrades to the total assets price
            }
        }
        cities[propId].upgradeLevel = 0; //Reset the upgrade level of the property
        cities[propId].ownerIndex = -1;
        totalAssetsPrice += cities[propId].cost; //Add the property's cost to the total assets price
    }
    for(int i=0; i<plyrs[plyrInd].numRailroads; i++){
        propId = plyrs[plyrInd].railroadsOwned[i];
        cities[propId].ownerIndex = -1;
    }
    for(int i=0; i<plyrs[plyrInd].numUtilities; i++){
        propId = plyrs[plyrInd].utilitiesOwned[i];
        cities[propId].ownerIndex = -1;
    }
    cout<< "You declared bankruptcy and are out of the game." << endl;
    return totalAssetsPrice; //Return the total value of the player's assets to determine if they can pay what they owe or if they must declare bankruptcy
}
void goToJail(int plyrInd, Player* plyrs){
    plyrs[plyrInd].position = 10; //Move the player to the Jail space
    plyrs[plyrInd].inJail = true; //Mark the player as being in jail
    plyrs[plyrInd].jailTurns = 0; //Reset the player's jail turn count
    cout << "You are now in jail." << endl;
}
void jailTurn(int plyrInd, Player* plyrs, Board* board, City* cities){
    //Declare variables
    int choice; //User choice for how to get out of jail
    bool getoutOfJail = false; //Flag to indicate if the player has gotten out of jail
    int* diceR = new int[2]; //Array to store the results of rolling the dice

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
                rollDice(diceR); //Roll the dice
                cout << "You rolled a " << diceR[0] << " and a " << diceR[1] << "." << endl;
                if (diceR[0] == diceR[1]){ //Check if the player rolled doubles
                    cout << "You rolled doubles and got out of jail!" << endl;
                    getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                    plyrs[plyrInd].jailTurns = 0; //Reset the player's jail turn count
                }
                else{
                    if (plyrs[plyrInd].jailTurns == 2){ //If this is the player's third turn in jail, they must pay the fine and get out of jail
                        cout << "This is your third turn in jail. You must pay the fine to get out of jail." << endl;
                        moneyTransaction(plyrInd, plyrs, -50); //Handle money transaction with the bank for paying the fine (to be implemented)
                        getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                        plyrs[plyrInd].jailTurns = 0; //Reset the player's jail turn count
                    }
                    else{
                            cout << "You did not roll doubles." << endl;
                            plyrs[plyrInd].jailTurns++; //Increment the player's jail turn count
                    }
                }
                break;
            case 2:
                //Handle paying the fine to get out of jail (to be implemented)
                cout << "You chose to pay the fine to get out of jail." << endl;
                moneyTransaction(plyrInd, plyrs, -50); //Handle money transaction with the bank for paying the fine
                plyrs[plyrInd].jailTurns = 0; //Reset the player's jail turn count
                getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                break;
            case 3:
                //Handle using a 'Get Out of Jail Free' card to get out of jail (to be implemented)
                cout << "You chose to use a 'Get Out of Jail Free' card." << endl;
                plyrs[plyrInd].jailTurns = 0; //Reset the player's jail turn count
                getoutOfJail = true; //Set the flag to indicate the player has gotten out of jail
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 3." << endl;
                break;
        }
        if (getoutOfJail){
            plyrs[plyrInd].inJail = false; //Mark the player as no longer being in jail
            cout << "You are now out of jail." << endl;
        }
    }while(choice < 1 || choice > 3); //Continue to prompt the player until they make a valid choice
    deallocateMemory(diceR); //Deallocate memory for the dice roll array    
}
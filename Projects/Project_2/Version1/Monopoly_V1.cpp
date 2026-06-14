/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
#include <fstream>    //File I/O Library
using namespace std;

//User libraries
#include "Player.h"

#include "Dice.h"

#include "Board.h"
#include "Square.h"
#include "Property.h"
#include "City.h"
#include "ActionSpace.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
const int MAX_PLAYERS = 4;
const int MAX_BOARD_SPACES = 40; //Total number of spaces on the board

//Function Prototype
int getPlayersData(Player* plyrs, int maxPlayers); //get number of plyrs and their names and initialize their starting data
void getOrderOfPlay(Player* plyrs, int nPlyrs); //determine the order in which plyrs will take their turns

void mainGameLoop(Board& board, Player* plyrs, int nOfPlyrs); //Main game loop where players take turns until the game ends
void gameOver(); //function to handle end of game scenario and display final results
void deallocateMemory(Player* plyrs, Board& board); //Deallocate all dynamically allocated memory for players

void jailTurn(int plyrInd, Player* plyrs, Board& board); //Function to handle the player's turn while they are in jail (to be implemented)
void playersTurn(int plyrInd, Player* plyrs, Board& board); //Function to handle the player's turn when they are not in jail (to be implemented)

int showMenu(int nMenu); //Display a menu based on the provided template index and return the user's choice
void handleMenuChoice(int choice,int nMenu, int plyrInd, Player* plyrs, Board& board); //Handle the action based on the user's menu choice

void movePlayer(int plyrInd, Player* plyrs, Board& board, Dice& dice, bool& endTurn); //Move a player a specified number of steps on the board (to be implemented)

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    Player* plyrs = new Player[MAX_PLAYERS];
    int nPlyrs; //Number of players
    Board board;

    //Initialize Board
    board.initializeBoard(); //Initialize the board with the appropriate spaces and properties
    
    //Start new game and Display welcome message
    cout << "Welcome to Monopoly!" << endl;
    cout << "Starting a new game of Monopoly!" << endl;
    cout << "Press Enter to begin..." << endl;
    cin.get(); //Wait for user to press Enter

    cout << "----------------------------------------" << endl;

    //Get player data and determine order of play
    cout << "First, let's determine the order of play." << endl;
    cout << "Press Enter to begin..." << endl;
    cin.get(); //Wait for user to press Enter
    nPlyrs = getPlayersData(plyrs, MAX_PLAYERS); //get number of plyrs and their names and initialize their starting data
    getOrderOfPlay(plyrs, nPlyrs); //determine the order in which plyrs will take their turns
    cout << "The order of play has been determined!" << endl;
    cout << "----------------------------------------" << endl;

    //Enter main game loop
    mainGameLoop(board, plyrs, nPlyrs); //Main game loop where players take turns until the game ends

    //Game over scenario
    gameOver(); //function to handle end of game scenario and display final results

    //Deallocate all dynamically allocated memory at the end of the game
    deallocateMemory(plyrs, board);

    //Exit the program
    return 0;
};

int getPlayersData(Player* plyrs, int maxPlayers){
    //Declare Variables
    int nPlyrs;
    int tokenChoice;

    //Get number of plyrs and their names, initialize their attributes
    cout << "How many players are playing? (2-4): ";
    cin >> nPlyrs;
    while (nPlyrs < 2 || nPlyrs > maxPlayers) {
        cout << "Invalid number of players. Please enter a number between 2 and " << maxPlayers << ": ";
        cin >> nPlyrs;
    }
    cin.ignore(); // Ignore the newline character left in the buffer

    for (int i = 0; i < nPlyrs; i++) {
        char name[50];
        cout << "Enter the name of player " << (i + 1) << ": ";
        cin.getline(name, 50);
        cout << "Which token would " << name << " like to use? (1-4): ";
        cout << "1. Car" << endl;
        cout << "2. Hat" << endl;
        cout << "3. Dog" << endl;
        cout << "4. Thimble" << endl;
        cin >> tokenChoice;
        cin.ignore(); // Ignore the newline character left in the buffer
        plyrs[i] = Player(name, i, tokenChoice); // Initialize player with name, ID, and token
    }

    return nPlyrs;
}
void getOrderOfPlay(Player* plyrs, int nPlyrs){
    //Declare Variables
    Dice dice;
    int rolls[MAX_PLAYERS]; //Array to store the initial dice rolls of each player for determining order of play

    //Roll dice for each player to determine order of play
    cout << "Determining order of play by rolling dice..." << endl;
    cout << "----------------------------------------" << endl;
    cout << "Press Enter to continue..." << endl;
    cin.get(); //Wait for user to press Enter

    for (int i = 0; i < nPlyrs; i++) {
        cout << plyrs[i].getName() << " is rolling the dice..." << endl;
        cout << "Press Enter to roll the dice..." << endl;
        cin.get(); //Wait for user to press Enter
        dice.Roll();
        cout << "They rolled a " << dice.getDice1() << " and " << dice.getDice2() << "!" << endl;
        rolls[i] = dice.getTotalRoll();
    }

    //Determine order of play based on rolls (highest roll goes first)
    for (int i = 0; i < nPlyrs - 1; i++) {
        for (int j = i + 1; j < nPlyrs; j++) {
            if (rolls[j] > rolls[i]) {
                //Swap rolls
                int tempRoll = rolls[i];
                rolls[i] = rolls[j];
                rolls[j] = tempRoll;
                //Swap players
                Player tempPlayer = plyrs[i];
                plyrs[i] = plyrs[j];
                plyrs[j] = tempPlayer;
            }
        }
    }

    cout << "The order of play has been determined!" << endl;
    for (int i = 0; i < nPlyrs; i++) {
        cout << (i + 1) << ". " << plyrs[i].getName() << endl;
    }
    cout << "----------------------------------------" << endl;
}
void mainGameLoop(Board& board, Player* plyrs, int nOfPlyrs){
    //Declare Variables
    bool gameEnded = false; //Flag to indicate if the game has ended

    //Main game loop where players take turns until the game ends
    while (!gameEnded) {
        for (int i = 0; i < nOfPlyrs; i++) {
            if (!plyrs[i].isBankrupt()) {
                cout << "It's " << plyrs[i].getName() << "'s turn!" << endl;
                cout << "Press Enter to continue..." << endl;
                cin.get(); //Wait for user to press Enter

                //Player takes their turn (to be implemented: rolling dice, moving, buying properties, etc.)
                if (plyrs[i].isInJail()) {
                    //Handle jail turn logic
                    cout << "You are in jail." << endl;
                    jailTurn(i, plyrs, board); //Function to handle the player's turn while they are in jail (to be implemented)
                } else {
                    playersTurn(i, plyrs, board); //Function to handle the player's turn when they are not in jail (to be implemented)
                }
                //Check for end of game condition (e.g., only one player left with money)
                int activePlayers = 0;
                for (int j = 0; j < nOfPlyrs; j++) {
                    if (!plyrs[j].isBankrupt()) {
                        activePlayers++;
                    }
                }
                if (activePlayers <= 1) {
                    gameEnded = true;
                }
            }
        }
    }
}
void playersTurn(int plyrInd, Player* plyrs, Board& board){
    //Declare Variables
    Dice dice;
    int choice;
    bool endTurn = false;
    bool rolledDice = false; //Flag to track if the player has moved during their turn

    //Show player options and handle their choices
    do{
        choice = showMenu(0); //Show main menu and get user 
        if (choice == 0) {
            movePlayer(plyrInd, plyrs, board, dice, endTurn); //Function to handle moving the player based on their dice roll (to be implemented)
            rolledDice = true; //Set rolledDice flag to true after the player has rolled the dice and moved
        } else handleMenuChoice(choice, 0, plyrInd, plyrs, board); //Handle the action based on the user's menu choice

        if (rolledDice && dice.isDouble() && !endTurn) {
            cout << "You rolled a double! You get to roll again." << endl;
            rolledDice = false; //Reset rolledDice flag for the next roll
        }
        else if (rolledDice){
            dice.resetConsecutiveDoubles(); //Reset consecutive doubles counter if the player did not roll a double
            endTurn = true; //End the turn if the player did not roll a double
        }
    }while(!endTurn); //Continue showing the menu until the player chooses to roll the dice (option 0)
    choice = -1; //Reset choice variable for the end turn menu
    do{
        if (!plyrs[plyrInd].isBankrupt() && !plyrs[plyrInd].isInJail()) {
            choice = showMenu(1); //Show end turn menu and get user choice
            if (choice != 0) handleMenuChoice(choice, 1, plyrInd, plyrs, board); //Show end turn menu and handle choices until player chooses to end their turn (option 0)
        }
    }while(!plyrs[plyrInd].isBankrupt() && !plyrs[plyrInd].isInJail() && choice != 0);
    cout << "End of " << plyrs[plyrInd].getName() << "'s turn." << endl;
    cout << "----------------------------------------" << endl;
}
int showMenu(int nMenu){
    //Declare Variables
    int choice;

    //Display menu options based on the menu template index
    cout<<"0. " << (nMenu==0 ? "Roll the dice" : "End turn") << endl;
    cout<<"1. Upgrade property" << endl;
    cout<<"2. Mortgage property" << endl;
    cout<<"3. Unmortgage property" << endl;
    cout<<"4. Trade properties" << endl;
    cout<<"5. Declare bankruptcy" << endl;

    //Get user choice and validate input
    do{
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice < 0 || choice > 5){
            cout<< "Invalid choice. Please enter a number between 0 and 5: ";
        }
    }while(choice < 0 || choice > 5);
    return choice;
}
void handleMenuChoice(int choice,int nMenu, int plyrInd, Player* plyrs, Board& board){ //Handle the action based on the user's menu choice
    bool endTurn = false;

    do{
        switch(choice){
            case 0: //return to main where case 0 is done
                break;
            case 1:
                plyrs[plyrInd].UpgradeProperty(board); //Handle upgrade property action
                break;
            case 2:
                plyrs[plyrInd].mortgageProperty(board); //Handle mortgage property action
                break;
            case 3:
                plyrs[plyrInd].unmortgageProperty(board); //Handle unmortgage property action
                break;
            case 4:
                plyrs[plyrInd].tradeProperty(plyrs, board); //Handle trade properties action
                break;
            case 5:
                plyrs[plyrInd].declareBankruptcy(); //Handle declare bankruptcy action
                break;
            default:
                //Handle invalid choice
                cout << "Error: Invalid choice in handleMenuChoice function." << endl;
                break;
        }
        if(choice != 0){
            choice = showMenu(nMenu);
        }
    }while(choice != 0);
}
void movePlayer(int plyrInd, Player* plyrs, Board& board, Dice& dice, bool& endTurn){ //Function to handle moving the player based on their dice roll (to be implemented)
    //Declare Variables

    //Roll the dice and move the player accordingly (to be implemented)
    cout << "Rolling the dice..." << endl;
    dice.Roll();
    cout << "You rolled a " << dice.getTotalRoll() << "." << endl;
    if (dice.rolledThreeDoubles()) {
        cout << "You rolled three doubles! You must go to jail." << endl;
        plyrs[plyrInd].goToJail(); //Function to send the player to jail, updates position to jail and sets inJail flag to true
        endTurn = true; //End the turn if the player goes to jail
        dice.resetConsecutiveDoubles(); //Reset consecutive doubles counter after going to jail
        return;
    }

    plyrs[plyrInd].move(dice.getTotalRoll()); //Function to move the player a certain number of spaces on the board, updates position accordingly and handles passing Go

    //Handle landing on different types of spaces (properties, chance/community chest, etc.)
    Square* currentSquare = board.getSquare(plyrs[plyrInd].getPosition()); //function to get the Square object at a specific index on the board
    cout << "You landed on " << currentSquare->getName() << "." << endl;
    currentSquare->onLand(&plyrs[plyrInd]); //Function to handle the action for landing on the current square
    if (plyrs[plyrInd].isBankrupt()) {
        cout << "You have gone bankrupt!" << endl;
        endTurn = true; //End the turn if the player goes bankrupt
    }
    else if (plyrs[plyrInd].isInJail()) {
        cout << "You have been sent to jail!" << endl;
        endTurn = true; //End the turn if the player goes to jail
    }
}
void jailTurn(int plyrInd, Player* plyrs, Board& board){ //Function to handle the player's turn while they are in jail (to be implemented)
    //Declare Variables
    int choice;
    Dice dice;
    bool gotOutOfJail = false; //Flag to track if the player got out of jail during this turn

    //Handle the player's options for getting out of jail (rolling doubles, paying fine, using Get Out of Jail Free card)
    cout << "You are in jail." << endl;
    cout << "Currently, you have been in jail for " << plyrs[plyrInd].getJailTurns() << " turns." << endl;
    do{
        cout << "Here are your options:" << endl;
        cout << "1. Try to roll doubles to get out of jail." << endl;
        cout << "2. Pay the fine to get out of jail." << endl;
        cout << "3. Use a Get Out of Jail Free card to get out of jail. (if you have one)" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if(choice < 1 || choice > 3){
            cout << "Invalid choice. Please enter a number between 1 and 3: ";
        }
        else if (choice == 3 && plyrs[plyrInd].getHasGetOutOfJailCard() <= 0) {
            cout << "You do not have a Get Out of Jail Free card. Please choose another option." << endl;
            choice = 0; //Reset choice to trigger the loop again
        }
    }while(choice < 1 || choice > 3);

    cin.ignore(); //Ignore the newline character left in the buffer after reading the choice

    switch(choice){
        case 1:
            cout << "You chose to try to roll doubles to get out of jail." << endl;
            cout << "Press Enter to roll the dice..." << endl;
            cin.get();
            dice.Roll(); //Roll the dice
            cout << "You rolled a " << dice.getDice1() << " and a " << dice.getDice2() << "." << endl;
            if (dice.isDouble()) { //Check if the player rolled doubles
                cout << "You rolled doubles and got out of jail!" << endl;
                plyrs[plyrInd].getOutOfJail(); //Function to get the player out of jail, updates inJail flag to false and resets jailTurns to 0
                gotOutOfJail = true;
            }
            else {
                cout << "You did not roll doubles." << endl;
                plyrs[plyrInd].incrementJailTurns(); //Function to increment the number of turns the player has been in jail by 1
                if (plyrs[plyrInd].getJailTurns() >= 3) { //If this is the player's third turn in jail, they must pay the fine and get out of jail
                    cout << "This is your third turn in jail. You must pay the fine to get out of jail." << endl;
                    plyrs[plyrInd].deductMoney(50); //Function to deduct a certain amount from the player's balance for paying the fine
                    plyrs[plyrInd].getOutOfJail(); //Get the player out of jail after paying the fine
                    gotOutOfJail = true;
                }
            }
            break;
        case 2:
            cout << "You chose to pay the fine to get out of jail." << endl;
            plyrs[plyrInd].deductMoney(50); //function to deduct a certain amount from the player's balance for paying the fine
            plyrs[plyrInd].getOutOfJail(); //Function to get the player out of jail, updates inJail flag to false and resets jailTurns to 0
            gotOutOfJail = true;
            break;
        case 3:
            cout << "You chose to use a Get Out of Jail Free card." << endl;
            plyrs[plyrInd].useGetOutOfJailCard(); //Function to use the Get Out of Jail Free card, updates hasGetOutOfJailCard flag to false and gets the player out of jail
            gotOutOfJail = true;
            cout << "You used a Get Out of Jail Free card and got out of jail!" << endl;
            cout << "You have " << plyrs[plyrInd].getHasGetOutOfJailCard() << " Get Out of Jail Free cards remaining." << endl;
            cout << "Press Enter to roll the dice and move out of jail..." << endl;
            cin.get();
            dice.Roll(); //Roll the dice to move out of jail
            cout << "You rolled a " << dice.getDice1() << " and a " << dice.getDice2() << "." << endl;
            break;
        default:
            //Handle invalid choice (should not reach here due to validation loop)
            cout << "Invalid choice. Please try again." << endl;
            break;
    }
    if (gotOutOfJail) {
        cout << "You are now moving " << dice.getTotalRoll() << " spaces out of jail." << endl;
        plyrs[plyrInd].move(dice.getTotalRoll()); //Function to move the player a certain number of spaces on the board, updates position accordingly and handles passing Go
        Square* currentSquare = board.getSquare(plyrs[plyrInd].getPosition()); //function to get the Square object at a specific index on the board
        cout << "You landed on " << currentSquare->getName() << "." << endl;
        currentSquare->onLand(&plyrs[plyrInd]); //Function to handle the action for landing on the current square
    }
    else {
        cout << "You remain in jail. Good luck next turn!" << endl;
    }
    cout << "----------------------------------------" << endl;
}
void gameOver(){
    //Handle end of game scenario and display final results (to be implemented)
    cout << "Game Over!" << endl;
    cout << "Thank you for playing Monopoly!" << endl;
}
void deallocateMemory(Player* plyrs, Board& board){
    //Deallocate any dynamically allocated memory for players and board (if applicable)
    delete[] plyrs; //Deallocate the array of players
}


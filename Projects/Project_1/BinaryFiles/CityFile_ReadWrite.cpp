/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/
/*
Version 1.1
making and testing the functions for reading and writing the city and board data to external binary files, 
including the initialization function that reads the data from the files to set up the game components at the start of the game.

Steps included:
* manually initializing the city and board data in the code for filling the binary files
* making a readFromFile function for reading the city and board data from the binary files and returning it as City and Board objects
* making a writeToFile function for writing the city and board data to the binary files from City and Board objects
* testing the readFromFile and writeToFile functions by writing the manually initialized data to the files and then reading it back and printing it to the console to verify that it is correct.
* making an initialization function that calls the readFromFile functions to read the city and board data from the files and set up the game components at the start of the game.

Next steps:
Implement those fuunctions to the main game version and make sure to call the initialization function at the start of the game to set up the game components from the files.
make the same functions for reading and writing the chance cards and community chest cards data to and from external binary files, and test them as well.
making the structure for the chance cards and community chest cards data, and filling the binary files with the appropriate data for the cards.
making the logic for handling the effects of the chance cards and community chest cards when they are drawn during the game, including moving players to different spaces, giving or taking money, etc.

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
int const MAX_PLAYERS = 4;     //Maximum number of players
int const MAX_BOARD_SPACES = 40; //Total number of spaces on the board
int const MAX_CITIES = 22+4+2; //22 properties + 4 railroads + 2 utilities
int const MAX_CHANCE_CARDS = 16; //Number of Chance cards
int const MAX_COMMUNITY_CHEST_CARDS = 16; //Number of Community Chest cards
int const BOARD_SIZE = 40;         //Total number of spaces on the board

int const STARTINGBALANCE = 1500;  //Starting balance for each players
int const SALARY = 200;            //Amount collected when passing Go

//Function Prototype
void initializeCityManually(City* cities); //Initialize city data manually in the code (for testing purposes)
void initializeBoardManually(Board* board); //Initialize board data manually in the code (for testing purposes)

void initialization(string* filesNames, City* cities, Board* board, int* chanceCards, int* communityChestCards); //Initialize cities, board, chance cards, and community chest cards from external files

void writeToFile(string fileName, City *cities); //Write data for cities to external files
void writeToFile(string fileName, Board* board); //Write data for board to external files
void writeToFile(string fileName, int* chanceCards, int type); //Write data for chance cards and community chest cards to external files (type 0 for chance cards, type 1 for community chest cards)

City* readCityFromFile(string fileName, int id); //Read data for cities from external files
Board* readBoardFromFile(string fileName, int id); //Read data for board from external files
int* readCardsFromFile(string fileName, int id, int type); //Read data for chance cards and community chest cards from external files (type 0 for chance cards, type 1 for community chest cards)

void deallocateMemory(Player* players, City* cities, Board* board, int* chanceCards, int* communityChestCards); //Deallocate all dynamically allocated memory
void printCityData(City city); //Print the data for a city to the console (for testing purposes)
void printBoardData(Board board); //Print the data for a board space to the console (for testing purposes)
void printCardsData(int* cards, int type); //Print the data for chance cards and community chest cards to the console (for testing purposes, type 0 for chance cards, type 1 for community chest cards)

int main(int argv, char **argc)
{
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    Player* players = new Player[MAX_PLAYERS];
    City* cities = new City[MAX_CITIES];
    Board* board = new Board[BOARD_SIZE];
    int* chanceCards = new int[MAX_CHANCE_CARDS];
    int* communityChestCards = new int[MAX_COMMUNITY_CHEST_CARDS];
    int choice;

    string* filenames = new string[4];
    filenames[0] = "CityData.bin";
    filenames[1] = "BoardData.bin";
    filenames[2] = "ChanceCardsData.bin";
    filenames[3] = "CommunityChestCardsData.bin";

    //int noOfPlayers = MAX_PLAYERS;
    //int housesAvailable = 32;
    //int hotelsAvailable = 12;

    do{
        cout << "Here is the menu for the files:"<<endl;
        cout << "1. Initialize city and board data from file" << endl;
        cout << "2. Initialize city data from the code" << endl;
        cout << "3. Initialize board data from the code" << endl;
        cout << "4. Write city data to file" << endl;
        cout << "5. Write board data to file" << endl;
        cout << "6. Print city data to console" << endl;
        cout << "7. Print board data to console" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter the number corresponding to the action you want to perform: ";
        cin >> choice;
        switch(choice){
            case 1:
                // Initialize city data from file
                initialization(filenames, cities, board, chanceCards, communityChestCards);
                break;
            case 2:
                // Initialize city data from the code
                initializeCityManually(cities);
                break;
            case 3:
                // Initialize board data from the code
                initializeBoardManually(board);
                break;
            case 4:
                // Write city data to file
                writeToFile(filenames[0], cities);
                break;
            case 5:
                // Write board data to file
                writeToFile(filenames[1], board);
                break;
            case 6:
                // Print city data to console
                for (int i = 0; i < MAX_CITIES; i++) {
                    printCityData(cities[i]);
                }
                break;
            case 7:
                // Print board data to console
                for (int i = 0; i < BOARD_SIZE; i++) {
                    printBoardData(board[i]);
                }
                break;
            case 8:
                // Exit
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    }while(choice != 8);

    //Deallocate dynamically allocated memory
    deallocateMemory(players, cities, board, chanceCards, communityChestCards);

    //Close files
    //cityFile.close();

    //Exit the program
    return 0;
};
void printCityData(City city){
    cout << "City No." << city.id << endl;
    cout << "Board Position: " << city.boardPosition << endl;
    cout << "Name: " << city.name << endl;
    cout << "Group ID: " << city.groupID << endl;
    cout << "Cost: " << city.cost << endl;
    cout << "upgradeCost: " << city.upgradeCost << endl;
    cout << "Rent 0: " << city.houseRent[0] << endl;
    cout << "Rent 1: " << city.houseRent[1] << endl;
    cout << "Rent 2: " << city.houseRent[2] << endl;
    cout << "Rent 3: " << city.houseRent[3] << endl;
    cout << "Rent 4: " << city.houseRent[4] << endl;
    cout << "Mortgage Value: " << city.mortgageValue << endl;
    cout << "----------------------------------------" << endl;
}
void printBoardData(Board board){
    cout << "Board Space No." << board.id << endl;
    cout << "Name: " << board.name << endl;
    cout << "Property ID: " << board.propertyID << endl;
    cout << "Type: " << board.type << endl;
    cout << "----------------------------------------" << endl;
}
void deallocateMemory(Player* players, City* cities, Board* board, int* chanceCards, int* communityChestCards){
    delete[] players;
    delete[] cities;
    delete[] board;
    delete[] chanceCards;
    delete[] communityChestCards;
}
void initializeCityManually(City* cities){
    //Initialize cities, board, chance cards, and community chest cards
    cities[0]  = City{0, 1, "Mediterranean Avenue",    0 ,60  ,50 , {2 , 30 , 90  , 160 , 250 }, 30 , -1, 0, 0, false};
    cities[1]  = City{1, 3, "Baltic Avenue",           0 ,60  ,50 , {4 , 60 , 180 , 320 , 450 }, 30 , -1, 0, 0, false};
    cities[2]  = City{2, 6, "Oriental Avenue",         1 ,100 ,50 , {6 , 90 , 270 , 400 , 550 }, 50 , -1, 0, 0, false};
    cities[3]  = City{3, 8, "Vermont Avenue",          1 ,100 ,50 , {6 , 90 , 270 , 400 , 550 }, 50 , -1, 0, 0, false};
    cities[4]  = City{4, 9, "Connecticut Avenue",      1 ,120 ,50 , {8 , 100, 300 , 450 , 600 }, 60 , -1, 0, 0, false};
    cities[5]  = City{5, 11, "St. Charles Place",      2 ,140 ,100, {10, 150, 450 , 625 , 750 }, 70 , -1, 0, 0, false};
    cities[6]  = City{6, 13, "States Avenue",          2 ,140 ,100, {10, 150, 450 , 625 , 750 }, 70 , -1, 0, 0, false};
    cities[7]  = City{7, 14, "Virginia Avenue",        2 ,160 ,100, {12, 180, 500 , 700 , 900 }, 80 , -1, 0, 0, false};
    cities[8]  = City{8, 16, "St. James Place",        3 ,180 ,100, {14, 200, 500 , 750 , 950 }, 90 , -1, 0, 0, false};
    cities[9]  = City{9, 18, "Tennessee Avenue",       3 ,180 ,100, {14, 200, 500 , 750 , 950 }, 90 , -1, 0, 0, false};
    cities[10] = City{10, 19, "New York Avenue",       3 ,200 ,100, {16, 220, 600 , 800 , 1000}, 100, -1, 0, 0, false};
    cities[11] = City{11, 21, "Kentucky Avenue",       4 ,220 ,150, {18, 250, 700 , 875 , 1050}, 110, -1, 0, 0, false};
    cities[12] = City{12, 23, "Indiana Avenue",        4 ,220 ,150, {18, 250, 700 , 875 , 1050}, 110, -1, 0, 0, false};
    cities[13] = City{13, 24, "Illinois Avenue",       4 ,240 ,150, {20, 300, 750 , 925 , 1100}, 120, -1, 0, 0, false};
    cities[14] = City{14, 26, "Atlantic Avenue",       5 ,260 ,150, {22, 330, 800 , 975 , 1150}, 130, -1, 0, 0, false};
    cities[15] = City{15, 27, "Ventnor Avenue",        5 ,260 ,150, {22, 330, 800 , 975 , 1150}, 130, -1, 0, 0, false};
    cities[16] = City{16, 29, "Marvin Gardens",        5 ,280 ,150, {24, 360, 850 , 1025, 1200}, 140, -1, 0, 0, false};
    cities[17] = City{17, 31, "Pacific Avenue",        6 ,300 ,200, {26, 390, 900 , 1100 ,1275}, 150, -1, 0, 0, false};
    cities[18] = City{18, 32, "North Carolina Avenue", 6 ,300 ,200, {26, 390, 900 , 1100 ,1275}, 150, -1, 0, 0, false};
    cities[19] = City{19, 34, "Pennsylvania Avenue",   6 ,320 ,200, {28, 450, 1000, 1200, 1400}, 160, -1, 0, 0, false};
    cities[20] = City{20, 37, "Park Place",            7 ,350 ,200, {35, 500, 1100, 1300, 1500}, 175, -1, 0, 0, false};
    cities[21] = City{21, 39, "Boardwalk",             7 ,400 ,200, {50, 600, 1400, 1700, 2000}, 200, -1, 0, 0, false};
    cities[22] = City{22, 5, "Reading Railroad",       8 ,200 ,-1 , {25, 50 , 100 , 200 , -1  }, 100, -1, 0, 0, false};
    cities[23] = City{23, 15, "Pennsylvania Railroad", 8 ,200 ,-1 , {25, 50 , 100 , 200 , -1  }, 100, -1, 0, 0, false};
    cities[24] = City{24, 25, "B&O Railroad",          8 ,200 ,-1 , {25, 50 , 100 , 200 , -1  }, 100, -1, 0, 0, false};
    cities[25] = City{25, 35, "Short Line",            8 ,200 ,-1 , {25, 50 , 100 , 200 , -1  }, 100, -1, 0, 0, false};
    cities[26] = City{26, 12, "Electric Company",      9 ,150 ,-1 , {1 , 10 , -1  , -1  , -1  }, 75 , -1, 0, 0, false};
    cities[27] = City{27, 28, "Water Works",           9 ,150 ,-1 , {1 , 10 , -1  , -1  , -1  }, 75 , -1, 0, 0, false};

}
void initializeBoardManually(Board* board){
    //Initialize board spaces
    board[0]  = Board{0 , "Go",                        -1,  0, {0, 0, 0, 0}};
    board[1]  = Board{1 , "Mediterranean Avenue",       0,  1, {0, 0, 0, 0}};
    board[2]  = Board{2 , "Community Chest",           -1,  5, {0, 0, 0, 0}};
    board[3]  = Board{3 , "Baltic Avenue",              1,  1, {0, 0, 0, 0}};
    board[4]  = Board{4 , "Income Tax",                -1,  6, {0, 0, 0, 0}};
    board[5]  = Board{5 , "Reading Railroad",          22,  2, {0, 0, 0, 0}};
    board[6]  = Board{6 , "Oriental Avenue",            2,  1, {0, 0, 0, 0}};
    board[7]  = Board{7 , "Chance",                    -1,  4, {0, 0, 0, 0}};
    board[8]  = Board{8 , "Vermont Avenue",             3,  1, {0, 0, 0, 0}};
    board[9]  = Board{9 , "Connecticut Avenue",         4,  1, {0, 0, 0, 0}};
    board[10] = Board{10, "Jail/Just Visiting",        -1,  8, {0, 0, 0, 0}};
    board[11] = Board{11, "St. Charles Place",          5,  1, {0, 0, 0, 0}};
    board[12] = Board{12, "Electric Company",          26,  3, {0, 0, 0, 0}};
    board[13] = Board{13, "States Avenue",              6,  1, {0, 0, 0, 0}};
    board[14] = Board{14, "Virginia Avenue",            7,  1, {0, 0, 0, 0}};
    board[15] = Board{15, "Pennsylvania Railroad",     23,  2, {0, 0, 0, 0}};
    board[16] = Board{16, "St. James Place",            8,  1, {0, 0, 0, 0}};
    board[17] = Board{17, "Community Chest",           -1,  5, {0, 0, 0, 0}};
    board[18] = Board{18, "Tennessee Avenue",           9,  1, {0, 0, 0, 0}};
    board[19] = Board{19, "New York Avenue",           10,  1, {0, 0, 0, 0}};
    board[20] = Board{20, "Free Parking",              -1,  9, {0, 0, 0, 0}};
    board[21] = Board{21, "Kentucky Avenue",           11,  1, {0, 0, 0, 0}};
    board[22] = Board{28, "Chance",                    -1,  4, {0, 0, 0, 0}};   
    board[23] = Board{22, "Indiana Avenue",            12,  1, {0, 0, 0, 0}};
    board[24] = Board{23, "Illinois Avenue",           13,  1, {0, 0, 0, 0}};
    board[25] = Board{24, "B&O Railroad",              24,  2, {0, 0, 0, 0}};
    board[26] = Board{25, "Atlantic Avenue",           14,  1, {0, 0, 0, 0}};
    board[27] = Board{26, "Ventnor Avenue",            15,  1, {0, 0, 0, 0}};
    board[28] = Board{27, "Water Works",               27,  3, {0, 0, 0, 0}};
    board[29] = Board{28, "Marvin Gardens",            16,  1, {0, 0, 0, 0}};
    board[30] = Board{30, "Go To Jail",                -1, 10, {0, 0, 0, 0}};
    board[31] = Board{29, "Pacific Avenue",            17,  1, {0, 0, 0, 0}};
    board[32] = Board{31, "North Carolina Avenue",     18,  1, {0, 0, 0, 0}};
    board[33] = Board{33, "Community Chest",           -1,  5, {0, 0, 0, 0}};
    board[34] = Board{32, "Pennsylvania Avenue",       19,  1, {0, 0, 0, 0}};
    board[35] = Board{34, "Short Line",                25,  2, {0, 0, 0, 0}};
    board[36] = Board{35, "Chance",                    -1,  4, {0, 0, 0, 0}};
    board[37] = Board{36, "Park Place",                20,  1, {0, 0, 0, 0}};
    board[38] = Board{37, "Luxury Tax",                -1,  7, {0, 0, 0, 0}};
    board[39] = Board{39, "Broadwalk",                 21,  1, {0, 0, 0, 0}};
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

void writeToFile(string fileName, City *cities){
    //Declare an output file stream and open the file for writing in binary mode
    fstream outFile;
    outFile.open(fileName, ios::out | ios::binary); //Open the file

    //write city data to file
    for (int i=0; i<MAX_CITIES; i++){
        outFile.write(reinterpret_cast<char*>(&cities[i]), sizeof(City)); //Write each city data to the file
    }

    //Close the file
    outFile.close();
}
void writeToFile(string fileName, Board *board){
    //Declare an output file stream and open the file for writing in binary mode
    fstream outFile;
    outFile.open(fileName, ios::out | ios::binary); //Open the file

    //write board data to file
    for (int i=0; i<MAX_BOARD_SPACES; i++){
        outFile.write(reinterpret_cast<char*>(&board[i]), sizeof(Board)); //Write each board data to the file
    }

    //Close the file
    outFile.close();
}

void initialization(string* fileNames, City* cities, Board* board, int* chanceCards, int* communityChestCards){
    //read city data from file and print to console
    for (int i=0; i<MAX_CITIES; i++){
        City cityFromFile = *readCityFromFile(fileNames[0], i);
        printCityData(cityFromFile); //Print the read city data to the console
        cities[i] = cityFromFile; //Store the read city data in the cities array
    }
    //read board data from file and print to console
    for (int i=0; i<MAX_BOARD_SPACES; i++){
        Board boardFromFile = *readBoardFromFile(fileNames[1], i);
        printBoardData(boardFromFile); //Print the read board data to the console
        board[i] = boardFromFile; //Store the read board data in the board array
    }
}   
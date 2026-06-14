/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <iomanip>    //Format library
#include <fstream>    //File I/O library
using namespace std;

//User libraries
#include "cities.h"
#include "board.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
const int MAX_CITIES = 28;
const int BOARD_SIZE = 40;
const int MAX_PLAYERS = 4;
const int MAX_BOARD_SPACES = 40;

//Function Prototype
void initializeCityManually(City* cities);
void initializeBoardManually(Board* board);
void writeToFile(string fileName, City *cities);
void writeToFile(string fileName, Board* board);

//Execution begins here
int main(int argv, char **argc)
{

    City* cities = new City[MAX_CITIES];
    Board* board = new Board[BOARD_SIZE];
    initializeCityManually(cities);
    initializeBoardManually(board);

    string cityFileName = "CityData.bin";
    string boardFileName = "BoardData.bin";

    writeToFile(cityFileName, cities);
    writeToFile(boardFileName, board);

    delete[] cities;
    delete[] board;



    return 0;
};
void initializeCityManually(City* cities){
    //Initialize cities, board, chance cards, and community chest cards
    cities[0]  = City{0, 1, "Mediterranean Avenue",    0 ,60  ,50 , {2 , 10 , 30 , 90  , 160 , 250 }, 30 , -1, 0, 0, false};
    cities[1]  = City{1, 3, "Baltic Avenue",           0 ,60  ,50 , {4 , 20 , 60 , 180 , 320 , 450 }, 30 , -1, 0, 0, false};
    cities[2]  = City{2, 6, "Oriental Avenue",         1 ,100 ,50 , {6 , 30, 90 , 270 , 400 , 550 }, 50 , -1, 0, 0, false};
    cities[3]  = City{3, 8, "Vermont Avenue",          1 ,100 ,50 , {6 , 30, 90 , 270 , 400 , 550 }, 50 , -1, 0, 0, false};
    cities[4]  = City{4, 9, "Connecticut Avenue",      1 ,120 ,50 , {8 , 40, 100, 300 , 450 , 600 }, 60 , -1, 0, 0, false};
    cities[5]  = City{5, 11, "St. Charles Place",      2 ,140 ,100, {10, 50, 150, 450 , 625 , 750 }, 70 , -1, 0, 0, false};
    cities[6]  = City{6, 13, "States Avenue",          2 ,140 ,100, {10, 50, 150, 450 , 625 , 750 }, 70 , -1, 0, 0, false};
    cities[7]  = City{7, 14, "Virginia Avenue",        2 ,160 ,100, {12, 60, 180, 500 , 700 , 900 }, 80 , -1, 0, 0, false};
    cities[8]  = City{8, 16, "St. James Place",        3 ,180 ,100, {14, 70, 200, 500 , 750 , 950 }, 90 , -1, 0, 0, false};
    cities[9]  = City{9, 18, "Tennessee Avenue",       3 ,180 ,100, {14, 70, 200, 500 , 750 , 950 }, 90 , -1, 0, 0, false};
    cities[10] = City{10, 19, "New York Avenue",       3 ,200 ,100, {16, 80, 220, 600 , 800 , 1000}, 100, -1, 0, 0, false};
    cities[11] = City{11, 21, "Kentucky Avenue",       4 ,220 ,150, {18, 90, 250, 700 , 875 , 1050}, 110, -1, 0, 0, false};
    cities[12] = City{12, 23, "Indiana Avenue",        4 ,220 ,150, {18, 90, 250, 700 , 875 , 1050}, 110, -1, 0, 0, false};
    cities[13] = City{13, 24, "Illinois Avenue",       4 ,240 ,150, {20, 100, 300, 750 , 925 , 1100}, 120, -1, 0, 0, false};
    cities[14] = City{14, 26, "Atlantic Avenue",       5 ,260 ,150, {22, 110, 330, 800 , 975 , 1150}, 130, -1, 0, 0, false};
    cities[15] = City{15, 27, "Ventnor Avenue",        5 ,260 ,150, {22, 110, 330, 800 , 975 , 1150}, 130, -1, 0, 0, false};
    cities[16] = City{16, 29, "Marvin Gardens",        5 ,280 ,150, {24, 120, 360, 850 , 1025, 1200}, 140, -1, 0, 0, false};
    cities[17] = City{17, 31, "Pacific Avenue",        6 ,300 ,200, {26, 130, 390, 900 , 1100 ,1275}, 150, -1, 0, 0, false};
    cities[18] = City{18, 32, "North Carolina Avenue", 6 ,300 ,200, {26, 130, 390, 900 , 1100 ,1275}, 150, -1, 0, 0, false};
    cities[19] = City{19, 34, "Pennsylvania Avenue",   6 ,320 ,200, {28, 150, 450, 1000, 1200, 1400}, 160, -1, 0, 0, false};
    cities[20] = City{20, 37, "Park Place",            7 ,350 ,200, {35, 175, 500, 1100, 1300, 1500}, 175, -1, 0, 0, false};
    cities[21] = City{21, 39, "Boardwalk",             7 ,400 ,200, {50, 200, 600, 1400, 1700, 2000}, 200, -1, 0, 0, false};
    cities[22] = City{22, 5, "Reading Railroad",       8 ,200 ,-1 , {25, 50 , 100 , 200 , -1, -1  }, 100, -1, 0, 0, false};
    cities[23] = City{23, 15, "Pennsylvania Railroad", 8 ,200 ,-1 , {25, 50 , 100 , 200 , -1, -1  }, 100, -1, 0, 0, false};
    cities[24] = City{24, 25, "B&O Railroad",          8 ,200 ,-1 , {25, 50 , 100 , 200 , -1, -1  }, 100, -1, 0, 0, false};
    cities[25] = City{25, 35, "Short Line",            8 ,200 ,-1 , {25, 50 , 100 , 200 , -1, -1  }, 100, -1, 0, 0, false};
    cities[26] = City{26, 12, "Electric Company",      9 ,150 ,-1 , {1 , 10 , -1  , -1  , -1, -1  }, 75 , -1, 0, 0, false};
    cities[27] = City{27, 28, "Water Works",           9 ,150 ,-1 , {1 , 10 , -1  , -1  , -1, -1  }, 75 , -1, 0, 0, false};

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
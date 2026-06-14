/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: Gaddis_9ThE_Ch14_P8 - Date Class
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries
#include "Date.h"
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int month, day, year;
    Date date(1, 1, 2000); // Default date initialization

    //Initialize Variables
    cout << "This program will display a date in three different formats." << endl;
    cout << " Enter the month (1-12) followed by the day (1-31) and year (e.g. 5 22 2026): ";
    cin >> date; // Use overloaded input operator to read date

    //Display the date in different formats
    cout << date; // Use overloaded output operator to display date

    //Exit the program
    return 0;
};
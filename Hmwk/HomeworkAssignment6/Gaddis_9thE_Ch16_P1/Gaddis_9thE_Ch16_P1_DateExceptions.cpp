/*
Author: Philopatair Mallik
Date: 06/07/2026
purpose: Gaddis_9ThE_Ch16_P1_DateExceptions
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

    //Initialize Variables
    cout << "This program will display a date in three different formats." << endl;
    cout << "Enter the month (1-12): ";
    cin >> month;
    cout << "Enter the day (1-31): ";
    cin >> day;
    cout << "Enter the year: ";
    cin >> year;

    //Create Date object
    try {
        Date date(month, day, year);

        //Display the date in different formats
        cout << "Numeric format: ";
        date.printNum();
        cout << "Written format (Day Month Year): ";
        date.printWrtn_DMY();
        cout << "Written format (Month Day, Year): ";
        date.printWrtn_MDY();
    }
    catch (Date::InvalidMonth) {
        cout << "ERROR: Invalid month." << endl;
    }
    catch (Date::InvalidDay) {
        cout << "ERROR: Invalid day." << endl;
    }

    //Exit the program
    return 0;
};
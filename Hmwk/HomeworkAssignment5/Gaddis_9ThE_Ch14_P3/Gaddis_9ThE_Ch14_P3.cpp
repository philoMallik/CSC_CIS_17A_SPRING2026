/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "DayOfYear.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    int day;
    
    //Initialize Variables
    cout << "Enter a day of the year (1-365): ";
    cin >> day;

    //Mapping Process -> Inputs to Outputs
    DayOfYear date(day);

    //Display Inputs/Outputs
    cout << "Day " << day << " would be ";
    date.print();

    //Increment the day
    cout << "Incrementing the day using prefix increment..." << endl;
    ++date; // Using prefix increment
    cout << "The next day is: ";
    date.print();

    //Decrement the day
    cout << "Decrementing the day using prefix decrement..." << endl;
    --date; // Using prefix decrement
    cout << "The previous day is: ";
    date.print();

    //Increment the day using postfix increment
    cout << "Incrementing the day using postfix increment..." << endl;
    date++; // Using postfix increment
    cout << "The next day is: ";
    date.print();

    //Decrement the day using postfix decrement
    cout << "Decrementing the day using postfix decrement..." << endl;
    date--; // Using postfix decrement
    cout << "The previous day is: ";
    date.print();

    //Exit the program
    return 0;
};
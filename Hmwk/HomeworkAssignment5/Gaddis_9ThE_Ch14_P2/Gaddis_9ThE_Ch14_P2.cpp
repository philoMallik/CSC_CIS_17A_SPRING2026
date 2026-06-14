/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: Gaddis_9ThE_Ch14_P2 - DayOfYear Class Implementation 
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

    //Exit the program
    return 0;
};
/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "Numbers.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    int num;

    //Initialize Variables
    cout << "Enter a number between 0 and 9999: ";
    cin >> num;

    //Mapping Process -> Inputs to Outputs
    Numbers number(num);

    //Display Inputs/Outputs
    cout << "The number " << num << " in English is: ";
    number.print();
    cout << endl;

    //Exit the program
    return 0;
};
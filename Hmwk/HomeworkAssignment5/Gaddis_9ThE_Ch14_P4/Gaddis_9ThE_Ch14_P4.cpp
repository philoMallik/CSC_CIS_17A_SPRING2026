/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: Gaddis_9ThE_Ch14_P4.cpp - NumDays class test program
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "NumDays.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    int hours1, hours2;

    //Initialize Variables
    cout << "Enter the number of hours worked for employee 1: ";
    cin >> hours1;
    cout << "Enter the number of hours worked for employee 2: ";
    cin >> hours2;

    //Mapping Process -> Inputs to Outputs
    NumDays emp1(hours1); // Create a NumDays object for employee 1
    NumDays emp2(hours2); // Create a NumDays object for employee 2

    //Output the results
    cout << "Employee 1 worked " << emp1.getHours() << " hours, which is equivalent to " << emp1.getDays() << " days." << endl;
    cout << "Employee 2 worked " << emp2.getHours() << " hours, which is equivalent to " << emp2.getDays() << " days." << endl;

    cout << "Total hours worked by both employees: " << (emp1 + emp2).getHours() << " hours, which is equivalent to " << (emp1 + emp2).getDays() << " days." << endl;
    cout << "Difference in hours worked between employee 1 and employee 2: " << (emp1 - emp2).getHours() << " hours, which is equivalent to " << (emp1 - emp2).getDays() << " days." << endl;

    cout << "Incrementing employee 1's hours by 1..." << endl;
    emp1++; // Increment employee 1's hours by 1
    cout << "Employee 1 now worked " << emp1.getHours() << " hours, which is equivalent to " << emp1.getDays() << " days." << endl;

    cout << "Decrementing employee 2's hours by 1..." << endl;
    emp2--; // Decrement employee 2's hours by 1
    cout << "Employee 2 now worked " << emp2.getHours() << " hours, which is equivalent to " << emp2.getDays() << " days." << endl;

    
    //Exit the program
    return 0;
};
/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: Gaddis_9ThE_Ch13_P2.cpp - Employee class implementation and testing 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <iomanip>    //Format library
using namespace std;

//User libraries
#include "Employee.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Declare & Initialize Variables 
    Employee emp1("Susan Meyers", 47899, "Accounting"   , "Vice President");
    Employee emp2("Mark Jones"  , 39119, "IT"           , "Programmer"    );
    Employee emp3("Joy Rogers"  , 81774, "Manufacturing", "Engineer"      );

    //Display Inputs/Outputs
    cout << "The Employees are: " << endl;
    cout << left << setw(15) << "Name" << setw(12) << "ID Number" << setw(15) << "Department" << setw(15) << "Position" << endl;
    cout << left << setw(15) << emp1.getName() << setw(12) << emp1.getIdNum() << setw(15) << emp1.getDep() << setw(15) << emp1.getPos() << endl;
    cout << left << setw(15) << emp2.getName() << setw(12) << emp2.getIdNum() << setw(15) << emp2.getDep() << setw(15) << emp2.getPos() << endl;
    cout << left << setw(15) << emp3.getName() << setw(12) << emp3.getIdNum() << setw(15) << emp3.getDep() << setw(15) << emp3.getPos() << endl;

    //Exit the program
    return 0;
};
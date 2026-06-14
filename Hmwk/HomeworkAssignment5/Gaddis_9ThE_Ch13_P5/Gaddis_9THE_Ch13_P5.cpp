/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: Gaddis_9ThE_Ch13_P5_RetailItemCLass 
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "RetailItem.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Declare & Initialize Variables
    cout << "This program will create three retail items and display their details." << endl;
    RetailItem item1("Jacket", 12, 59.95f);
    RetailItem item2("Designer Jeans", 40, 34.95f);
    RetailItem item3("Shirt", 20, 24.95f);

    //Mapping Process -> Inputs to Outputs

    //Display Inputs/Outputs
    cout << "Item 1: " << item1.getDescription() << ", Units on Hand: " << item1.getUnitsOnHand() << ", Price: $" << item1.getPrice() << endl;
    cout << "Item 2: " << item2.getDescription() << ", Units on Hand: " << item2.getUnitsOnHand() << ", Price: $" << item2.getPrice() << endl;
    cout << "Item 3: " << item3.getDescription() << ", Units on Hand: " << item3.getUnitsOnHand() << ", Price: $" << item3.getPrice() << endl;

    //Exit the program
    return 0;
};
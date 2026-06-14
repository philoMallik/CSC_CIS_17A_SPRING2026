/*
Author: Philopatair Mallik
Date: 04/20/2026
purpose: Gaddis_9thE_Ch12_P14_InventoryScreenReport.cpp 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <fstream>    //File Stream Library
using namespace std;

//User libraries
#include "Item.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    string fileName = "inventory.dat";

    // title and purpose of the program
    cout << "This program demonstrates how to read and display inventory data from a file." << endl;

    fstream in;
    in.open(fileName, ios::in | ios::binary);
    Item item;
    int quantityTot = 0;
    int wscostTot = 0;
    int rtcostTot = 0;
    
    while (in.read(reinterpret_cast<char*>(&item), sizeof(item))){
        quantityTot += item.Quantity;
        wscostTot += item.WSCost;
        rtcostTot += item.RTCost;
    }

    //Display output to the user
    cout<< "Total quantity on hand: " << quantityTot << endl;
    cout<< "Total wholesale cost: $" << wscostTot << endl;
    cout<< "Total retail cost: $" << rtcostTot << endl;
    
    //Exit the program
    return 0;
};
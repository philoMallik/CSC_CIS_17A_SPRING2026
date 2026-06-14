/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: Gaddis_9ThE_Ch13_P5 - C++ Class Template for Inventory Management 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries
#include "Inventory.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void displayItem(const Inventory &item, int size);
void getItemData(Inventory *item, int size);
void randomItemData(Inventory *item, int size);

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    cout << "Welcome to the Inventory Management System!" << endl;
    cout << "How many items would you like to manage? ";
    int size;
    cin >> size;
    
    // Create an array of Inventory objects to hold the inventory items
    Inventory *inventory = new Inventory[size];

    cout << "Would you like to enter item data manually (Y/N)? (else it would be generated randomly) ";
    char choice;
    cin >> choice;

    switch (choice) {
        case 'Y':
        case 'y':
            cout << "You chose to enter item data manually." << endl;
            // Get item data from the user
            getItemData(inventory, size);
            break;
        case 'N':
        case 'n':
            cout << "You chose to generate item data randomly." << endl;
            // Generate random item data
            randomItemData(inventory, size);
            break;
        default:
            cout << "Invalid choice. Defaulting to random item data generation." << endl;
            choice = 'N';
    }

    // Display the random item
    displayItem(*inventory, size);

    // Clean up dynamically allocated memory
    delete[] inventory;

    //Exit the program
    return 0;
};

void displayItem(const Inventory &item, int size){
    cout << "Inventory Items:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Item " << i + 1 << ":" << endl;
        cout << "  Item Number: " << item.getItmNum() << endl;
        cout << "  Quantity: " << item.getQty() << endl;
        cout << "  Cost: $" << item.getCost() << endl;
        cout << "  Total Cost: $" << item.getTotCost() << endl;
    }
}
void getItemData(Inventory *item, int size){
    //Declare Variables
    int itemNumber;
    int quantity;
    float itemCost;

    for (int i = 0; i < size; i++) {
        cout << "Enter data for Item " << i + 1 << ":" << endl;
        cout << "Item Number: ";
        cin >> itemNumber;
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Cost: $";
        cin >> itemCost;

        // Set the item data using the mutator functions
        item[i].setItmNum(itemNumber);
        item[i].setQty(quantity);
        item[i].setCost(itemCost);
        item[i].setTotCost(); // Calculate total cost
    }
}
void randomItemData(Inventory *item, int size){
    //Declare Variables
    int itemNumber;
    int quantity;
    float itemCost;
    
    for (int i = 0; i < size; i++) {
        itemNumber = rand() % 100 + 1; // Random item number between 1 and 100
        quantity = rand() % 100 + 1;     // Random quantity between 1 and 100
        itemCost = static_cast<float>(rand() % 10000) / 100.0f + 0.01f; // Random cost between $0.01 and $100.00

        // Set the item data using the mutator functions
        item[i].setItmNum(itemNumber);
        item[i].setQty(quantity);
        item[i].setCost(itemCost);
        item[i].setTotCost(); // Calculate total cost
    }
}
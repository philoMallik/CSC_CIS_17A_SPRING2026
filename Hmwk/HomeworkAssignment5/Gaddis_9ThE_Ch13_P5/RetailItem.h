/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: Gaddis_9ThE_Ch13_P5_RetailItemCLass 
*/

#ifndef RETAILITEM_H
#define RETAILITEM_H

#include <iostream>
using namespace std; 

class RetailItem
{
    private:
        string description; // Item description
        int unitsOnHand;   // Units on hand
        float price;       // Item price    
    public:
        // Constructor
        RetailItem(string, int, float); // Constructor
        // Mutators
        void setDescription(string); // Set item description
        void setUnitsOnHand(int);   // Set units on hand
        void setPrice(float);       // Set item price
        // Accessors
        string getDescription(); // Get item description
        int getUnitsOnHand();   // Get units on hand
        float getPrice();       // Get item price
};

#endif // RETAILITEM_H
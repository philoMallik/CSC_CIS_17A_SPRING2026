#ifndef ITEM_H
#define ITEM_H

#include <iostream>
using namespace std;

struct Item{
    char itemDescription[50];
    int Quantity;     // Quantity on hand
    int WSCost;       // Wholesale cost
    int RTCost;       // Retail cost
    int DateAdded[3]; // Assuming DateAdded is an array of 3 integers: day, month, year
};
#endif
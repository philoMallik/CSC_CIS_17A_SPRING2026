
/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: RetailItem Class Implementation File 
*/

    #include "RetailItem.h"
    #include <iostream>
    using namespace std;

    // Constructor
    RetailItem::RetailItem(string description, int unitsOnHand, float price){
        this->description = description;
        this->unitsOnHand = unitsOnHand;
        this->price = price;
    }
    // Mutators
    void RetailItem::setDescription(string description) {
        this->description = description;
    }
    void RetailItem::setUnitsOnHand(int unitsOnHand) {
        this->unitsOnHand = unitsOnHand;
    }
    void RetailItem::setPrice(float price) {
        this->price = price;
    }
    // Accessors
    string RetailItem::getDescription() {
        return description;
    }
    int RetailItem::getUnitsOnHand() {
        return unitsOnHand;
    }
    float RetailItem::getPrice() {
        return price;
    }
    /*
    Author: Philopatair Mallik
    Date: 05/20/2026
    purpose: C++ Class Template for Inventory Management 
    */

    #include <iostream>
    using namespace std;
    
    
    #include "Inventory.h"
    
    // Default constructor
    Inventory::Inventory(){
        itmNum = 0;
        qty = 0;
        cost = 0.0;
        totCost = 0.0;
    }

    // Constructor #2
    Inventory::Inventory(int itemNumber, int quantity, float itemCost){
        if (itemNumber < 0) {
            cout << "Error: Item number cannot be negative. Setting to 0." << endl;
            itemNumber = 0;
        }
        else itmNum = itemNumber;

        if (quantity < 0) {
            cout << "Error: Quantity cannot be negative. Setting to 0." << endl;
            quantity = 0;
        }
        else qty = quantity;

        if (itemCost < 0) {
            cout << "Error: Cost cannot be negative. Setting to 0." << endl;
            itemCost = 0.0;
        }
        else cost = itemCost;

        setTotCost(); // Calculate total cost
    }

    // Mutator functions
    void Inventory::setItmNum(int itemNumber){
        itmNum = itemNumber;
    }
    void Inventory::setQty(int quantity){
        qty = quantity;
    }
    void Inventory::setCost(float itemCost){
        cost = itemCost;
    }
    void Inventory::setTotCost(){
        totCost = qty * cost;
    }
    // Accessor functions
    int Inventory::getItmNum() const{
        return itmNum;
    }
    int Inventory::getQty() const{
        return qty;
    }
    float Inventory::getCost() const{
        return cost;
    }
    float Inventory::getTotCost() const{
        return totCost;
    }
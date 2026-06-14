/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: C++ Class Template for Inventory Management 
*/

#ifndef INVENTORY_H
#define INVENTORY_H

class Inventory
{
    private:
        int itmNum;     // Item number
        int qty;        // Quantity of the item
        float cost;     // Cost of the item
        float totCost;  // Total cost of the item (quantity * cost)
    public:
        // Default constructor
        Inventory();

        // Constructor #2
        Inventory(int itemNumber, int quantity, float itemCost);

        // Mutator functions
        void setItmNum(int itemNumber);
        void setQty(int quantity);
        void setCost(float itemCost);
        void setTotCost();              // Calculate total cost
        // Accessor functions
        int getItmNum() const;
        int getQty() const;
        float getCost() const;
        float getTotCost() const;
};

#endif // INVENTORY_H
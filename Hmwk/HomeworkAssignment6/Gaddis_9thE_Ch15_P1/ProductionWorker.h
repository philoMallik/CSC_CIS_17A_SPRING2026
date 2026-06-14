/*
Author: Philopatair Mallik
Date:   06/03/2026
purpose:ProductionWorker Class Specification
*/

#ifndef PRODUCTIONWORKER_H
#define PRODUCTIONWORKER_H

#include "Employee.h"

class ProductionWorker: public Employee
{
    private:
        int shift;      //1 for day shift, 2 for night shift
        float payRate;  //hourly pay rate
    public:
        // Constructor
        ProductionWorker(string name, int num, int hDate, int shift, float payRate);

        // Accessor functions
        int getShift() const;
        float getPayRate() const;

        // Mutator functions
        void setShift(int shift);
        void setPayRate(float payRate);
};

#endif // PRODUCTIONWORKER_H
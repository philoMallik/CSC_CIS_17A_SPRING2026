/*
Author: Philopatair Mallik
Date:   06/03/2026
purpose:Employee Class Definition 
*/

#include <iostream>
using namespace std;

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

class Employee{
    private:
        string name;
        int num;
        int hDate;      // Hire date in the format MMDDYYYY

    public:
        // Constructor
        Employee(string name, int num, int hDate);

        // Accessor functions
        string getName() const;
        int getNum() const;
        int getHDate() const;

        // Mutator functions
        void setName(string name);
        void setNum(int num);
        void setHDate(int hDate);
};

#endif // EMPLOYEE_H
/*
File: Employee.h
Author: Philopatair Mallik
Date: 05/22/2026
purpose: C++ Class Template 
*/

#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
using namespace std;

class Employee
{
    private:
        string name;
        int idNum;
        string Dep;
        string pos;
    public:
        // Constructor
        Employee(string name, int idNum, string Dep, string pos);
        Employee(string name, int idNum);
        Employee();

        //Accessors
        string getName() const;
        int getIdNum() const;
        string getDep() const;
        string getPos() const;

        //Mutators
        void setName(string name);
        void setIdNum(int idNum);
        void setDep(string Dep);
        void setPos(string pos);
};

#endif // EMPLOYEE_H
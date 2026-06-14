/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:Employee Class Implementation
*/

//User Libraries
#include "Employee.h"

Employee::Employee(string name, int num, int hDate){
    this->name = name;
    this->num = num;
    this->hDate = hDate;
}

string Employee::getName() const{
    return name;
}

int Employee::getNum() const{
    return num;
}

int Employee::getHDate() const{
    return hDate;
}

void Employee::setName(string name){
    this->name = name;
}

void Employee::setNum(int num){
    this->num = num;
}

void Employee::setHDate(int hDate){
    this->hDate = hDate;
}

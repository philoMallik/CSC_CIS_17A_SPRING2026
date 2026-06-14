/*
File: Employee.cpp
Author: Philopatair Mallik
Date: 05/22/2026
purpose: Employee class implementation 
*/

#include "Employee.h"

// Constructor
Employee::Employee(string name, int idNum, string Dep, string pos){
    this->name = name;
    this->idNum = idNum;
    this->Dep = Dep;
    this->pos = pos;
}

Employee::Employee(string name, int idNum){
    this->name = name;
    this->idNum = idNum;
    this->Dep = "";
    this->pos = "";
}

Employee::Employee(){
    this->name = "";
    this->idNum = 0;
    this->Dep = "";
    this->pos = "";
}

// Accessors
string Employee::getName() const{
    return name;
}

int Employee::getIdNum() const{
    return idNum;
}

string Employee::getDep() const{
    return Dep;
}

string Employee::getPos() const{
    return pos;
}

// Mutators
void Employee::setName(string name){
    this->name = name;
}

void Employee::setIdNum(int idNum){
    this->idNum = idNum;
}

void Employee::setDep(string Dep){
    this->Dep = Dep;
}

void Employee::setPos(string pos){
    this->pos = pos;
}

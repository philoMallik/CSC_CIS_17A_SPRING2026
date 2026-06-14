/*
Filename:  Card.cpp
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   Class Implementation
*/

//System libraries
#include  <iostream>
#include <cstring>
using namespace std;

//User libraries
#include "Card.h"


Card::Card() {
    description[0] = '\0';
    actionType = -1;
    value = 0;
}


//Constructor to initialize the card with a description, action type, and value
Card::Card(const char* des, int actionType, int value) {
    strncpy(this->description, des, 100);
    this->description[99] = '\0';
    this->actionType = actionType;
    this->value = value;
}

//Destructor
Card::~Card() {
}

const char* Card::getDescription() const {
    return description;
}
int Card::getActionType() const {
    return actionType;
}
int Card::getValue() const {
    return value;
}

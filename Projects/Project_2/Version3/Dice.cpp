/*
Filename:  Dice.cpp
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class implementation file
*/

//System libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

//User libraries
#include "Dice.h"

// ============ Constructors ============

Dice::Dice() {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    die1 = 1;
    die2 = 1;
    consecutiveDoubles = 0;
}

Dice::~Dice() {
}

// ============ Member Functions ============

void Dice::Roll() {
    die1 = (rand() % 6) + 1;
    die2 = (rand() % 6) + 1;

    if (isDouble()) {
        consecutiveDoubles++;
    } else {
        consecutiveDoubles = 0;
    }
}

int Dice::getDie1() const {
    return die1;
}

int Dice::getDie2() const {
    return die2;
}

int Dice::getDice1() const {
    return die1;
}

int Dice::getDice2() const {
    return die2;
}

int Dice::getConsecutiveDoubles() const {
    return consecutiveDoubles;
}

int Dice::getTotalRoll() const {
    return die1 + die2;
}

bool Dice::isDouble() const {
    return die1 == die2;
}

bool Dice::rolledThreeDoubles() const {
    return consecutiveDoubles >= 3;
}

void Dice::resetConsecutiveDoubles() {
    consecutiveDoubles = 0;
}
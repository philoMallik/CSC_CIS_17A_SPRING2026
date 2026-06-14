/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:Essay Class Implementation
*/

//System Libraries
#include <iostream>
using namespace std;

//User Libraries
#include "Essay.h"

// Constructor
Essay::Essay() : grammar(0), spelling(0), corrLen(0), content(0) {
	setScore(0.0);
}

Essay::Essay(int grammar, int spelling, int length, int content)
	: grammar(grammar), spelling(spelling), corrLen(length), content(content) {
	setScore(grammar + spelling + length + content);
    determineGrade();
}

// Accessor functions
int Essay::getGrammar() const {
	return grammar;
}

int Essay::getSpelling() const {
	return spelling;
}

int Essay::getLength() const {
	return corrLen;
}

int Essay::getContent() const {
	return content;
}

// Mutator functions
void Essay::setGrammar(int grammar) {
	this->grammar = grammar;
	setScore(this->grammar + spelling + corrLen + content);
}

void Essay::setSpelling(int spelling) {
	this->spelling = spelling;
	setScore(grammar + this->spelling + corrLen + content);
}

void Essay::setLength(int length) {
	corrLen = length;
	setScore(grammar + spelling + corrLen + content);
}

void Essay::setContent(int content) {
	this->content = content;
	setScore(grammar + spelling + corrLen + this->content);
}

// Display function
void Essay::display() const {
    cout << "Essay Scores:" << endl;
    cout << "Grammar: " << grammar << "/30" << endl;
    cout << "Spelling: " << spelling << "/20" << endl;
    cout << "Correct Length: " << corrLen << "/20" << endl;
    cout << "Content: " << content << "/30" << endl;
    cout << "Total Score: " << getScore() << "/100" << endl;
    cout << "Letter Grade: " << getLetterGrade() << endl;
}
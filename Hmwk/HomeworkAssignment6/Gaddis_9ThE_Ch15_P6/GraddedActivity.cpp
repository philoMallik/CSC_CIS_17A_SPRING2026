/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:GradedActivity Class Implementation
*/

//User Libraries
#include "GraddedActivity.h"

// Constructor
GradedActivity::GradedActivity(){
    score = 0.0;
    letter = ' ';
}

void GradedActivity::determineGrade(){
    if (score >= 90)        letter = 'A';
    else if (score >= 80)   letter = 'B';
    else if (score >= 70)   letter = 'C';
    else if (score >= 60)   letter = 'D';
    else                    letter = 'F';
}

void GradedActivity::setScore(double score){
    this->score = score;
    determineGrade();
}
double GradedActivity::getScore() const{
    return score;
}
char GradedActivity::getLetterGrade() const{
    return letter;
}
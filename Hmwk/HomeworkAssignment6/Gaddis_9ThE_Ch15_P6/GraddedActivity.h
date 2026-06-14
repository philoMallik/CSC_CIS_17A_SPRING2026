/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:GradedActivity Class Specification - Class copied from the textbook Gaddis_9ThE_Ch15.sec4_GradedActivity.h
*/

#ifndef GRADEDACTIVITY_H
#define GRADEDACTIVITY_H

class GradedActivity;

class GradedActivity{
    protected:
        char letter;            // to hold the letter grade
        double score;           // to hold the numeric score
        void determineGrade();  // determine the letter grade

    public:
        // Constructor
        GradedActivity();

        // Accessor functions
        double getScore() const;
        char getLetterGrade() const;

        // Mutator function
        void setScore(double score);
};

#endif // GRADEDACTIVITY_H
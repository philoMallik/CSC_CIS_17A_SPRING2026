/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:Essay Class Specification
*/

#ifndef ESSAY_H
#define ESSAY_H
#include "GraddedActivity.h"


class Essay : public GradedActivity {
    private:
        int grammar;    // Grammar score (0-30)
        int spelling;   // Spelling score (0-20)
        int corrLen;    // Correct length score (0-20)
        int content;    // Content score (0-30)

    public:
        // Constructor
        Essay();
        Essay(int grammar, int spelling, int length, int content);

        // Accessor functions
        int getGrammar() const;
        int getSpelling() const;
        int getLength() const;
        int getContent() const;

        // Mutator functions
        void setGrammar(int grammar);
        void setSpelling(int spelling);
        void setLength(int length);
        void setContent(int content);

        //display function
        void display() const;
};


#endif // ESSAY_H
/*
Filename:  Prob1Random.h
Author:    Philopatair Mallik
Date:      06/09/2026
Purpose:   Prob1Random class Specification
*/

#ifndef PROB1RANDOM_H
#define PROB1RANDOM_H

//System libraries
#include  <iostream>
using namespace std;

class Prob1Random;  //Forward declaration

class Prob1Random{
  private:
    //Private variables defined here
    char *set;      //the set of numbers to draw random number from
    char nset;      //the number of variables in the sequence
    int *freq;      //Frequency of all the random numbers returned
    int numRand;    //The total number of times the random number
                    //function is called
    public:
        Prob1Random(const char,const char *);//Constructor
        ~Prob1Random(void);         //Destructor
        char randFromSet(void);     //Returns a random number from the set
        int *getFreq(void) const;   //Returns the frequency histogram
        char *getSet(void) const;   //Returns the set used
        int getNumRand(void) const; //Gets the numer of times randFromSet
                                    //has been called

};

#endif  // PROB1RANDOM_H
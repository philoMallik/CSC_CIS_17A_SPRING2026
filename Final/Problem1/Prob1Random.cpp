/* 
 * File:    Prob1Random.cpp
 * Author:  Philopatair Mallik
 * Date:    06/09/2026
 * Purpose: class implementation file
 */

//System libraries
#include <iostream>
using namespace std;

//User libraries
#include "Prob1Random.h"

    // Constructors
    Prob1Random::Prob1Random(const char n,const char *s){
        nset=n;
        set=new char[n];
        for(int i=0;i<n;i++){
            set[i]=s[i];
        }
        freq=new int[n];
        for(int i=0;i<n;i++){
            freq[i]=0;
        }
        numRand=0;
    }
    
    //Destructor
    Prob1Random::~Prob1Random(void){
        delete [] set;
        delete [] freq;
    }

    //Accessors
    int* Prob1Random::getFreq(void) const{
        return freq;
    }
    char* Prob1Random::getSet(void) const{
        return set;
    }
    int Prob1Random::getNumRand(void) const{
        return numRand;
    }

    //Mutators


    //Operator overloads

    //Member functions
    char Prob1Random::randFromSet(void){
        numRand++;
        int index=rand()%nset;
        freq[index]++;
        return set[index];
    }
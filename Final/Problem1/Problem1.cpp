/*
File:   Problem1.cpp
Author: Philopatair Mallik
Date:   06/09/2026
purpose: Final Exam : Problem 1 :  Random Sequence) Create a class that returns a random number
from the following set, 19,34,57,79,126. Loop 100,000 times with this procedure and print
the frequency of each of the 5 numbers obtained. The following is the specification for
the class.
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
using namespace std;

//User libraries
#include "Prob1Random.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));

    //Driver program to return a random sequence
    char n=5;
    char rndseq[]={19,34,57,79,126};
    int ntimes=100000;
    Prob1Random a(n,rndseq);
    for(int i=1;i<=ntimes;i++){
    a.randFromSet();
    }
    int *x=a.getFreq();
    char *y=a.getSet();
    for(int i=0;i<n;i++){
    cout<<setw(3)<<int(y[i])<<" occurred "<<x[i]<<" times"<<endl;
    }
    cout<<endl<<"The total number of random numbers is "<<a.getNumRand()<<endl;
    //Exit the program
    return 0;
};
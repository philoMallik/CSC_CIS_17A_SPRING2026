/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries
#include "GraddedActivity.h"
#include "Essay.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void randGenScores(int &grammar, int &spelling, int &length, int &content);


//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int grammar, spelling, length, content;

    //create an Essay object Array
    Essay essays[5];

    //Initialize Variables
    for(int i = 0; i < 5; i++){
        randGenScores(grammar, spelling, length, content);
        essays[i] = Essay(grammar, spelling, length, content);
    }

    //Display the results
    for(int i = 0; i < 5; i++){
        cout << "Essay " << (i + 1) << ":" << endl;
        essays[i].display();
        cout << "-----------------------------" << endl;
    }

    //Exit the program
    return 0;
};
void randGenScores(int &grammar, int &spelling, int &length, int &content){
    grammar = rand() % 31;   // 0-30
    spelling = rand() % 21;  // 0-20
    length = rand() % 21;    // 0-20
    content = rand() % 31;   // 0-30
}
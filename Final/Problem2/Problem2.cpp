/*
File:   Problem2.cpp
Author: Philopatair Mallik
Date:   06/09/2026
purpose: Problem 2 (All Kinds of Sorting) Sort a single column array and/or sort a 2
         dimensional array of characters given any column. Here is what I used as my template
         specification.
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <fstream>    //File I/O library
using namespace std;

//User libraries
#include "Prob2Sort.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Driver Program to test the sorting problem
    cout<<"The start of Problem 2, the sorting problem"<<endl;
    Prob2Sort<char> rc;
    bool ascending=true;

    //Getting the array from the file
    ifstream infile;
    infile.open("Problem2.txt",ios::in);
    char *ch2=new char[10*16];
    char *ch2p=ch2;
    while(infile.get(*ch2)){
        cout<<*ch2;ch2++;
    }
    infile.close();
    cout<<endl;

    //sorting the array
    cout<<"Sorting on which column"<<endl;
    int column;
    cin>>column;
    char *zc=rc.sortArray(ch2p,10,16,column,ascending);
    for(int i=0;i<10;i++){
        for(int j=0;j<16;j++){
        cout<<zc[i*16+j];
        }
    }
    delete []zc;
    cout<<endl;

    //Exit the program
    return 0;
};

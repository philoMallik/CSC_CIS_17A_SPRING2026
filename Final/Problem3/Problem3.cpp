/*
File:   Problem3.cpp
Author: Philopatair Mallik
Date:   06/09/2026
purpose:  Problem 3 (Spreadsheet Stuff)
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "Prob3Table.h"
#include "Prob3TableInherited.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    cout<<"Entering problem number 3"<<endl;
    int rows=5;
    int cols=6;
    Prob3TableInherited<int> tab("Problem3.txt",rows,cols);
    const int *naugT=tab.getTable();

    //Display array without sums
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<naugT[i*cols+j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    //Display array with sums
    const int *augT=tab.getAugTable();
    for(int i=0;i<=rows;i++){
        for(int j=0;j<=cols;j++){
            cout<<augT[i*(cols+1)+j]<<" ";
        }
        cout<<endl;
    }

    //Exit the program
    return 0;
};
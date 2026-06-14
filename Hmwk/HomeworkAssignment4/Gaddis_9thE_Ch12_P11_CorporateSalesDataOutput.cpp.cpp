/*
Author: Philopatair Mallik
Date: 04/20/2026
purpose: Gaddis_9thE_Ch12_P11_CorporateSalesDataOutput.cpp
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <fstream>    //File Stream Library
using namespace std;

//User libraries
#include "CompanyDivision.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void structToFile ( const string, CompanyDivision*, int);

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    CompanyDivision *divisions = new CompanyDivision[4];
    string fileName = "companySales.dat";

    //get the data for the structure from the user
    cout<< "This program demonstrates how to use structures to store and display corporate sales data." << endl;
    cout << "Input the name of the division, the quarter number, and the sales for that quarter." << endl;
    for (int i = 0; i < 4; i++){
        cout<< "Division " << i+1 << ": " << endl;
        cout<< "Input the name of the division: ";
        cin.getline(divisions[i].Name, 50);
        for (int j = 0; j < 4; j++){
            cout<< "Input the sales for quarter " << j+1 << ": ";
            do{
                cin>>divisions[i].qrtrsls[j];
                if (divisions[i].qrtrsls[j] < 0){
                    cout<< "Sales cannot be negative. Please enter a valid sales amount: ";
                }
            } while (divisions[i].qrtrsls[j] < 0);
        }
        cin.ignore();
    }

    //write the structure to file
    structToFile(fileName, divisions, 4);

    //Exit the program
    delete[] divisions;
    return 0;
};

void structToFile ( const string fileName, CompanyDivision *divisions, int size){
    fstream out;
    out.open(fileName, ios::out);
    for (int i = 0; i < size; i++){
        out<< "Division " << i+1 << ": " << endl;
        out<< "Name: " << divisions[i].Name << endl;
        for (int j = 0; j < 4; j++){
            out<< "Quarter " << j+1 << ": $" << divisions[i].qrtrsls[j] << endl;
        }
        out<< "------------------------------" << endl;
    }
    out.close();
}
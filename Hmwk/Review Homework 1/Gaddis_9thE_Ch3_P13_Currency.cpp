/*
Author: Philopatair Mallik
Date: 03/12/2026
purpose: Currency
    a program that convert the currency from dollars to either Japanese yen or euros
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
const float YEN_PER_DOLLAR = 98.93;
const float EUROS_PER_DOLLAR = 0.74;
//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    float DollAmt;
    int choice;
    float output;
    //Initialize Variables
    cout<<"Currency conversion program."<<endl
        <<"Input the Amount to be converted in Dollars"<<endl;
    cin>>DollAmt;
    cout<<"Which currency you want it to be converted to?"<<endl
        <<"Press '1' for Japanese yen"<<endl
        <<"Press '2' for euros"<<endl;
    cin>>choice;
    while(choice<1||choice>2){
        cout<<"Wrong input!"<<endl;
        cout<<"Which currency you want it to be converted to?"<<endl
            <<"Press '1' for Japanese yen"<<endl
            <<"Press '2' for euros"<<endl;
    }
    //Mapping Process -> Inputs to Outputs
    switch (choice){
        case 1: output=DollAmt*YEN_PER_DOLLAR;
        break;
        case 2: output=DollAmt*EUROS_PER_DOLLAR;
        break;
    }
    //Display Inputs/Outputs
    cout<<"the amount entered in ";
    if (choice==1)cout<<"Japanese yen";
    else cout<<"euros";
    cout<<" is "<<fixed<<setprecision(2)<<output;
    //Exit the program
    return 0;
};
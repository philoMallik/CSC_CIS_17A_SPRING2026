/*
Author: Philopatair Mallik
Date: 03/12/2026
purpose: Days in a Month
    A program that calculates how many days in a given month and a year
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int month,year,days;
    //Initialize Variables
    //cout<<"This Program determine how many days in the month givenm in given year."<<endl;
    cout<<"Enter a month (1-12): ";
    cin>>month;
    cout<<"Enter a year: ";
    cin>>year;
    //Mapping Process -> Inputs to Outputs
    switch(month){
        case  1:
        case  3:
        case  5:
        case  7:
        case  8:
        case 10:
        case 12: days=31;
                 break;
        case  4:
        case  6:
        case  9:
        case 11: days=30;
                 break;
        case  2: if(year%100==0){
                    if(year%400==0) days=29;
                    else            days=28;
                 }
                 else{
                    if(year%4==0) days=29;
                    else          days=28;
                 }
    }
    //Display Inputs/Outputs
    cout<<days<<" days"<<endl;
    //Exit the program
    return 0;
};
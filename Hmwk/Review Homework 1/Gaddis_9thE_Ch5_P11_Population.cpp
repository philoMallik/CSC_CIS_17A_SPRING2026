/*
Author: Philopatair Mallik
Date: 03/12/2026
purpose: Population
    a program that calculate the population of organisms that increases averagely per day
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
const int PERCENT =100;
//Function Prototype

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int days;
    float size,increase;
    //Initialize Variables
    cout<<"Enter the starting number of organisms: ";
    cin>>size;
    while(size<2){
        cout<<"starting number can't be less than 2."<<endl;
        cout<<"Enter the starting number of organisms: ";
        cin>>size;
    }
    cout<<"Enter the average daily population increase (as a percentage): ";
    cin>>increase;
    while(increase<0){
        cout<<"average daily population increase can't be less than 0."<<endl;
        cout<<"Enter the average daily population increase: ";
        cin>>increase;
    }
    cout<<"Enter the number of days they will multiply: ";
    cin>>days;
    while(days<1){
        cout<<"number of days they will multiply can't be less than 0."<<endl;
        cout<<"Enter the number of days they will multiply: ";
        cin>>days;
    }
    //Mapping Process -> Inputs to Outputs
    increase/=PERCENT;
    for(int i=0;i<days;i++){
        size+=(increase*size);
        cout<<"The size of the population in day "<<i+1<<" = "<<fixed<<setprecision(0)<<size<<endl;;
    }
    //Display Inputs/Outputs

    //Exit the program
    return 0;
};
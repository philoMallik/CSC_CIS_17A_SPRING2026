/*
Author: Philopatair Mallik
Date: 03/12/2026
purpose: Sum of Two fractions
a program that calculate the sum of two fractions
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
    int num1,num2,den1,den2,num3,den3;
    //Initialize Variables
    cout<<"This is a program that calculates the sum of two fractions."<<endl;
    cout<<"Input the numerator and denominator of first number seperated by space then press enter."<<endl;
    cin>>num1>>den1;
    while(den1==0){
        cout<<"Denominator can't be equal to zero!"<<endl;
        cout<<"Input the denominator for the first number"<<endl;
        cin>>den1;
    }
    cout<<"Input the numerator and denominator of second number seperated by space then press enter."<<endl;
    cin>>num2>>den2;
    while(den2==0){
        cout<<"Denominator can't be equal to zero!"<<endl;
        cout<<"Input the denominator for the second number"<<endl;
        cin>>den2;
    }
    //Mapping Process -> Inputs to Outputs
    num3=(num1*den2)+(num2*den1);
    den3=den1*den2;
    //Display Inputs/Outputs
    cout<<"The sum of the two fractions is "<<num3<<"/"<<den3<<endl;
    //Exit the program
    return 0;
};
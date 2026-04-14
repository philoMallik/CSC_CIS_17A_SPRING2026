/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <iomanip>    //Format Library
using namespace std;

//User libraries
struct CompanyDivision{
    float q1sales;
    float q2sales;
    float q3sales;
    float q4sales;
};
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void fillDivDat(CompanyDivision &div); //Fill the data for a company division
void calcTotSal(CompanyDivision div); //Calculate the total annual sales for a company division

//Execution begins here
int main(int argv, char **argc){
    //Declare Variables
    CompanyDivision North, South, East, West; //Company divisions to hold quarterly data for each division

    cout<<"North"<<endl;
    fillDivDat(North); //Fill the data for the North division
    calcTotSal(North); //Calculate the total annual sales for the North division
    cout<<endl;

    cout<<"West"<<endl;
    fillDivDat(West); //Fill the data for the West division 
    calcTotSal(West); //Calculate the total annual sales for the West division
    cout<<endl;

    cout<<"East"<<endl;
    fillDivDat(East); //Fill the data for the East division
    calcTotSal(East); //Calculate the total annual sales for the East division
    cout<<endl;

    cout<<"South"<<endl;
    fillDivDat(South); //Fill the data for the South division
    calcTotSal(South); //Calculate the total annual sales for the South division

    //Exit the program
    return 0;
};
void fillDivDat(CompanyDivision &div){ //Fill the data for a company division
    cout<<"Enter first-quarter sales:"<<endl;
    cin>>div.q1sales;
    cout<<"Enter second-quarter sales:"<<endl;
    cin>>div.q2sales;
    cout<<"Enter third-quarter sales:"<<endl;
    cin>>div.q3sales;
    cout<<"Enter fourth-quarter sales:"<<endl;
    cin>>div.q4sales;
}
void calcTotSal(CompanyDivision div){ //Calculate the total annual sales for a company division
    float totSls = div.q1sales + div.q2sales + div.q3sales + div.q4sales;
    cout<<"Total Annual sales:$"<<fixed<<setprecision(2)<<totSls<<endl;
    float avgSls = totSls / 4;
    cout<<"Average Quarterly Sales:$"<<fixed<<setprecision(2)<<avgSls;
}
/*
Author: Philopatair Mallik
Date: 03/13/2026
purpose: Temerature
    A program that create a weather report for a 10 days period
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>
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
    int days=10;
    int hiTemp[days],lowTemp[days],humidity[days];
    int totHum=0,avgHum,diurnal,maxTemp,minTemp;
    //Initialize Variables
    for(int i=0;i<days;i++){
        cout<<"Enter highest temperature, lowest temperature and humidity for day "<<i+1<<" (Seperated by a space): "<<endl;
        cin>>hiTemp[i]>>lowTemp[i]>>humidity[i];
        totHum+=humidity[i];
    }
    //Mapping Process -> Inputs to Outputs
    avgHum=totHum/days;
    maxTemp=hiTemp[0];
    minTemp=lowTemp[0];
    for(int i=0;i<days;i++){
        maxTemp=hiTemp[i]>maxTemp?hiTemp[i]:maxTemp;
        minTemp=lowTemp[i]<minTemp?lowTemp[i]:minTemp;
    }
    //Display Inputs/Outputs
    cout<<setw(5)<<"Day"<<setw(15)<<"Highest Temp."<<setw(15)<<"Lowest Temp."<<setw(15)<<"Diurnal Var."<<setw(15)<<"Humidity"<<endl;
    for(int i=0;i<days;i++){
        cout<<left<<setw(5)<<i
            <<left<<setw(15)<<hiTemp[i]
            <<left<<setw(15)<<lowTemp[i]
            <<left<<setw(15)<<hiTemp[i]-lowTemp[i]
            <<left<<setw(15)<<humidity[i]
            <<left<<setw(15)<<(humidity[i]>avgHum?"Above Average":humidity[i]<avgHum?"BelowAverage":"(Average)")
            <<endl;
    }
    cout<<endl;
    cout<<"Maximum Temperature = "<<maxTemp<<endl;
    cout<<"Minimum Temperature = "<<minTemp<<endl;
    cout<<"Overall Variation   = "<<maxTemp-minTemp;

    //Exit the program
    return 0;
};
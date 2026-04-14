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
struct Month{
    float highTemp,
         lowTemp;
    float totRain;
};
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void getWeatherData(Month &); //Get the weather data for a month
void calcAverages(Month*); //Calculate the average monthly rainfall, highest and lowest temperatures for a month and Average monthly temperature

//Execution begins here
int main(int argv, char **argc){
    //Declare Variables
    Month *months = new Month[6]; //Array of 6 months to hold weather data for each month
    //Initialize Variables
    for(int i = 0; i < 6; i++){
        getWeatherData(months[i]); //Get the weather data for each month
    }

    //Mapping Process -> Inputs to Outputs
    calcAverages(months);

    //Deallocate dynamically allocated memory
    delete[] months;

    //Exit the program
    return 0;
};
void getWeatherData(Month &month){ //Get the weather data for a month
    cout<<"Enter the total rainfall for the month:"<<endl;
    cin>>month.totRain;
    cout<<"Enter the high temp:"<<endl;
    cin>>month.highTemp;
    cout<<"Enter the low temp:"<<endl;
    cin>>month.lowTemp;
}
void calcAverages(Month* months){ //Calculate the average monthly rainfall, highest and lowest temperatures for a month and Average monthly temperature
    float totRain = 0,
          avgRain = 0,
          avgTemp = 0;
    float totTemp = 0,
          highTemp = months[0].highTemp,
          lowTemp = months[0].lowTemp;
    for(int i = 0; i < 6; i++){
        totRain += months[i].totRain;
        totTemp += months[i].highTemp + months[i].lowTemp;
        if(months[i].highTemp > highTemp){
            highTemp = months[i].highTemp;
        }
        if(months[i].lowTemp < lowTemp){
            lowTemp = months[i].lowTemp;
        }
    }
    avgRain = totRain / 6.0f;
    cout<<"Average monthly rainfall:"<<avgRain<<endl;
    cout<<"High Temp:"<<highTemp<<endl;
    cout<<"Low Temp:"<<lowTemp<<endl;
    avgTemp = (totTemp) / 12.0f;
    cout<<"Average Temp:"<<avgTemp;
}
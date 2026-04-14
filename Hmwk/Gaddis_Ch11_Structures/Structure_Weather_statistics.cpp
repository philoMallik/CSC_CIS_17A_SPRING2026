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
struct MonthlyStat
{
    char name[9];
    int totRain;
    int highTemp; //Degrees Fahrenheit
    int lowTemp;  //Degrees Fahrenheit
    int AvgTemp;  //Degrees Fahrenheit
};


//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void getWeatherData(MonthlyStat*); //Get the weather data for a month
void displayAvgRain(MonthlyStat*); //Display the average rainfall for the year
void displayLowTemp(MonthlyStat*); //Display the lowest temperature for the year
void displayHighTemp(MonthlyStat*); //Display the highest temperature for the year
void displayAvgTemp(MonthlyStat*); //Display the average temperature for the year

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    MonthlyStat month[12];

    //Initialize Variables
    getWeatherData(month); //Get the weather data for each month

    //Mapping Process & Display Inputs/Outputs
    displayAvgRain(month); //Display the average rainfall for the year
    displayLowTemp(month); //Display the lowest temperature for the year
    displayHighTemp(month); //Display the highest temperature for the year  
    displayAvgTemp(month); //Display the average temperature for the year

    //Exit the program
    return 0;
};
void getWeatherData(MonthlyStat* month){ //Get the weather data for a month
   for(int i = 0; i < 12; i++){
        cin>>month[i].name>>month[i].totRain>>month[i].lowTemp>>month[i].highTemp;
        month[i].AvgTemp = (month[i].highTemp + month[i].lowTemp) / 2;
        cin.ignore();
    }
}
void displayAvgRain(MonthlyStat* month){ //Display the average rainfall for the year
    int totRain = 0;
    float avgRain = 0;
    for(int i = 0; i < 12; i++){
        totRain += month[i].totRain;
    }
    avgRain = totRain / 12.0f;
    cout<<"Average Rainfall "<<fixed<<setprecision(1)<<avgRain<<" inches/month"<<endl;
}
void displayLowTemp(MonthlyStat* month){ //Display the lowest temperature for the year
    int index = 0;
    for(int i = 1; i < 12; i++){
        if(month[i].lowTemp < month[index].lowTemp){
            index = i;
        }
    }
    cout<<"Lowest  Temperature "
         <<left<<setw(8)<<month[index].name
         <<right<<setw(3)<<month[index].lowTemp<<" Degrees Fahrenheit"<<endl;
}
void displayHighTemp(MonthlyStat* month){ //Display the highest temperature for the year
    int index = 0;
    for(int i = 1; i < 12; i++){
        if(month[i].highTemp > month[index].highTemp){
            index = i;
        }
    }
    cout<<"Highest Temperature "
         <<left<<setw(8)<<month[index].name
         <<right<<setw(3)<<month[index].highTemp<<" Degrees Fahrenheit"<<endl;
}
void displayAvgTemp(MonthlyStat* month){ //Display the average temperature for the year
    int totTemp = 0;
    int avgTemp = 0;
    for(int i = 0; i < 12; i++){
        totTemp = totTemp + month[i].lowTemp + month[i].highTemp;
    }
    avgTemp = totTemp / 24;
    if (totTemp%24>12)avgTemp++;
    cout<<"Average Temperature for the year "<<static_cast<int>(avgTemp)<<" Degrees Fahrenheit"<<endl;
}
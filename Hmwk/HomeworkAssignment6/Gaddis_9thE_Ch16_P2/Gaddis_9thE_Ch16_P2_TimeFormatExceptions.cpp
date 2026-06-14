/*
Author: Philopatair Mallik
Date: 06/07/2026
purpose: Gaddis_9ThE_Ch16_P2 TimeFormat
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;
//User libraries
#include "Time.h"
#include "MillTime.h"
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void generateTime(int &milHr, int &milSec);
void inputTime(MillTime &time);

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int milHr, milSec;
    generateTime(milHr, milSec);
    
    MillTime time(milHr, milSec);
    cout << "Randomly generated time:\n";
    cout << "Military Time: ";
    time.dsplymil();
    cout << "Standard Time: ";
    time.dsplyStd();

    cout << "\nNow, enter a time in military format (HHMM) and seconds (SS):\n";
    inputTime(time);
    cout << "You entered:\n";
    cout << "Military Time: ";
    time.dsplymil();
    cout << "Standard Time: ";
    time.dsplyStd();

    //Exit the program
    return 0;
};
void generateTime(int &milHr, int &milSec){
    milHr = rand() % 2400; // Generate a random military hour between 0000 and 2359
    milSec = rand() % 60;   // Generate a random military second between 0 and 59
}
void inputTime(MillTime &time){
    int milHr, milSec;
    cout << "Enter military time (HHMM): ";
    cin >> milHr;
    cout << "Enter military seconds (SS): ";
    cin >> milSec;
    try{
        time.setTime(milHr, milSec);
    } 
    catch (const MillTime::BadHr){
        cout << "ERROR: Invalid military time. \n";
        time.setTime(0, 0); // Set to default time if input is invalid
    }
    catch (const MillTime::BadSec){
        cout << "ERROR: Invalid military seconds. \n";
        time.setTime(0, 0); // Set to default time if input is invalid
    }
}
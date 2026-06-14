/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose: Gaddis_9thE_Ch16_P5 Total Template Function 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Templates
template <class T>
T total(int count) {
    T val;
    T total = 0;
    for (int i = 0; i < count; i++) {
        cout << "Enter value " << (i + 1) << ": ";
        cin >> val;
        total += val;
    }
    return total;
}

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int count;

    //Test with integers
    cout << "How many integers do you want to sum? ";
    cin >> count;
    int totalInt = total<int>(count);
    cout << "Total of integers: " << totalInt << endl;

    //Test with floats
    cout << "How many floats do you want to sum? ";
    cin >> count;
    float totalFloat = total<float>(count);
    cout << "Total of floats: " << totalFloat << endl;

    //Test with doubles
    cout << "How many doubles do you want to sum? ";
    cin >> count;
    double totalDouble = total<double>(count);
    cout << "Total of doubles: " << totalDouble << endl;

    //Exit the program
    return 0;
};
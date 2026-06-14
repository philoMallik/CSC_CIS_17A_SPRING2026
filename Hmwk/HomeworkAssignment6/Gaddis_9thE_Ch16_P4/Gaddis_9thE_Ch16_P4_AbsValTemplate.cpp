/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose: Gaddis_9thE_Ch16_P4 AbsVal Template Function 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void genRandarg(int &);
void genRandarg(float &);
void genRandarg(double &);
void genRandarg(char &);
void genRandarg(string &);

//Templates
template <class T>
T AbsVal(T arg) {
    return (arg < 0) ? -arg : arg;
}

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int     intArg;
    float   floatArg;
    double  doubleArg;
    char    charArg;
    string  stringArg;

    //generate random arguments
    genRandarg(intArg);
    genRandarg(floatArg);
    genRandarg(doubleArg);
    genRandarg(charArg);
    genRandarg(stringArg);

    //Display the random arguments and their absolute values
    cout << "Random Integer: " << intArg << " | Absolute Value: " << AbsVal(intArg) << endl;
    cout << "Random Float: " << floatArg << " | Absolute Value: " << AbsVal(floatArg) << endl;
    cout << "Random Double: " << doubleArg << " | Absolute Value: " << AbsVal(doubleArg) << endl;
    cout << "Random Char: '" << charArg << "' | Absolute Value: '" << AbsVal(charArg) << "'" << endl;
    //cout << "Random String: \"" << stringArg << "\" | Absolute Value: \"" << AbsVal(stringArg) << "\"" << endl;

    //Exit the program
    return 0;
};

void genRandarg(int &arg) {
    arg = rand() % 201 - 100; // Random integer between -100 and 100
}
void genRandarg(float &arg) {
    arg = static_cast<float>(rand()) / RAND_MAX * 200 - 100; // Random float between -100 and 100
}

void genRandarg(double &arg) {
    arg = static_cast<double>(rand()) / RAND_MAX * 200 - 100; // Random double between -100 and 100
}

void genRandarg(char &arg) {
    arg = static_cast<char>(rand() % 95 + 32);                  // Random printable ASCII character
}

void genRandarg(string &arg) {
    int length = rand() % 10 + 1; // Random string length between 1 and 10
    arg.clear();
    for (int i = 0; i < length; i++) {
        arg += static_cast<char>(rand() % 26 + 97); // Random lowercase letter
    }
}
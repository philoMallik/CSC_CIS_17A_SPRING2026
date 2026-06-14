/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose: Gaddis_9thE_Ch16_P3 Min/Max Template Functions
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void gen2randNums(int &, int &);
void gen2randNums(float &, float &);
void gen2randNums(double &, double &);
void gen2randChars(char &, char &);
void gen2randStrings(string &, string &);

//Templates
template <class T>
T Min(T a, T b) {
    return (a < b) ? a : b;
}

template <class T>
T Max(T a, T b) {
    return (a > b) ? a : b;
}

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int int1, int2;
    float float1, float2;
    double double1, double2;
    char char1, char2;
    string string1, string2;
    
    //Initialize Variables
    gen2randNums(int1, int2);
    gen2randNums(float1, float2);
    gen2randNums(double1, double2);
    gen2randChars(char1, char2);
    gen2randStrings(string1, string2);

    //Display the random numbers & their minimum and maximum
    cout << "Random Integers: " << int1 << " and " << int2 << endl;
    cout << "Minimum Integer: " << Min(int1, int2) << endl;
    cout << "Maximum Integer: " << Max(int1, int2) << endl;

    cout << "Random Floats: " << float1 << " and " << float2 << endl;
    cout << "Minimum Float: " << Min(float1, float2) << endl;
    cout << "Maximum Float: " << Max(float1, float2) << endl;

    cout << "Random Doubles: " << double1 << " and " << double2 << endl;
    cout << "Minimum Double: " << Min(double1, double2) << endl;
    cout << "Maximum Double: " << Max(double1, double2) << endl;

    cout << "Random Characters: '" << char1 << "' and '" << char2 << "'" << endl;
    cout << "Minimum Character: '" << Min(char1, char2) << "'" << endl;
    cout << "Maximum Character: '" << Max(char1, char2) << "'" << endl;

    cout << "Random Strings: \"" << string1 << "\" and \"" << string2 << "\"" << endl;
    cout << "Minimum String: \"" << Min(string1, string2) << "\"" << endl;
    cout << "Maximum String: \"" << Max(string1, string2) << "\"" << endl;


    //Exit the program
    return 0;
};
void gen2randNums(int &a, int &b) {
    a = rand() % 100 + 1; // Random integer between 1 and 100
    b = rand() % 100 + 1; // Random integer between 1 and 100
}
void gen2randNums(float &a, float &b) {
    a = static_cast<float>(rand()) / RAND_MAX * 100.0f; // Random float between 0 and 100
    b = static_cast<float>(rand()) / RAND_MAX * 100.0f; // Random float between 0 and 100
}
void gen2randNums(double &a, double &b) {
    a = static_cast<double>(rand()) / RAND_MAX * 100.0; // Random double between 0 and 100
    b = static_cast<double>(rand()) / RAND_MAX * 100.0; // Random double between 0 and 100
}
void gen2randChars(char &a, char &b) {
    a = static_cast<char>(rand() % 26 + 'a'); // Random lowercase letter
    b = static_cast<char>(rand() % 26 + 'a'); // Random lowercase letter
}
void gen2randStrings(string &a, string &b) {
    int length = rand() % 10 + 1; // Length of the random strings between 1 and 10
    a = "";
    b = "";
    for (int i = 0; i < length; i++) {
        a += static_cast<char>(rand() % 26 + 'a');
        b += static_cast<char>(rand() % 26 + 'a');
    }
}

/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
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
    float n1,n2,n3;
    string bin1,bin2,bin3;
    string oct1,oct2,oct3;
    string hex1,hex2,hex3;
    string NASABin1,NASABin2,NASABin3;
    string NASAHex1,NASAHex2,NASAHex3;
    string  IEEEBin1,IEEEBin2,IEEEBin3;
    string IEEEHex1,IEEEHex2,IEEEHex3;
    float n1_1Bshift, n2_1Bshift, n3_1Bshift;
    float n1_2Bshift, n2_2Bshift, n3_2Bshift;
    float n1_3Bshift, n2_3Bshift, n3_3Bshift;


    //Initialize Variables
    n1 = 5.75;
    unsigned char n1HexChar = 0x5C;
    unsigned char n1OctChar = 056;
    unsigned char n1BinChar = 0b10111000;
    unsigned int n1_1bBShift = 32 * n1;
    unsigned char n1_1bBShiftBin = 0b10111000;
    cout << "n1: " << n1 << endl;
    cout << "n1HexChar: " << num1 << endl;
    num1 >>= 32;
    cout << "num1 >> 32: " << num1 << endl;

    n1HexChar >>= 16;
    cout << "n1HexChar >> 16: " << (float)n1HexChar << endl;

    //Exit the program
    return 0;
};
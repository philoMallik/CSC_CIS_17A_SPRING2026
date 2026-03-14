/*
Author: Philopatair Mallik
Date: 01/26/2026
purpose: C++ Menu Template 
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
void problem1();
void problem2();
void problem3();
void problem4();
void problem5();
void problem6();
void problem7();
void problem8();
void problem9();
void problem10();
//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    unsigned short choose;
    unsigned short problemCount;
    //Initialize Variables
    problemCount = 10;
    do
    {
        cout << "This is a Menu program" << endl;
        cout << "Type 1  for problem X1" << endl;
        cout << "Type 2  for problem x2" << endl;
        cout << "Type 3  for problem x3" << endl;
        cout << "Type 4  for problem x4" << endl;
        cout << "Type 5  for problem x5" << endl;
        cout << "Type 6  for problem x6" << endl;
        cout << "Type 7  for problem x7" << endl;
        cout << "Type 8  for problem x8" << endl;
        cout << "Type 9  for problem x9" << endl;
        cout << "Type 10 for problem x10" << endl;
        cin >> choose;

        //Mapping Process -> Inputs to Outputs
        switch (choose)
        {
            case  1:
            {
                problem1();
                break;
            }
            case  2:
            {
                problem2();
                break;
            }
            case  3:
            {
                problem3();
                break;
            }
            case  4:
            {
                problem4();
                break;
            }
            case  5:
            {
                problem5();
                break;
            }
            case  6:
            {
                problem6();
                break;
            }
            case  7:
            {
                problem7();
                break;
            }
            case  8:
            {
                problem8();
                break;
            }
            case  9:
            {
                problem9();
                break;
            }
            case  10:
            {
                problem10();
                break;
            }
            default: cout << "You have choosen to exit" << endl;
        }

    } while (choose >= 1 && choose <= problemCount);
    


    //Display Inputs/Outputs

    //Exit the program
    return 0;
};
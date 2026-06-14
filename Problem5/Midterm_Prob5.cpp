/*
Author: Philopatair Mallik
Date: 04/22/2026
purpose: Midterm Problem 5 - 
5. (10 points) Exploration of datatypes!
    a) Using a byte variable, what is the largest n for the function n! that can be
    calculated. A factorial is simply
    n! = 1 * 2 * 3 * 4 ... * (n-2) * (n-1) * n
    For instance, 1! = 1, 2! = 2, 3! = 6, 4! = 24, 5! = 120 etc....
    Signed as well as unsigned.
    b) What would be the largest n for n! using short, int, long, long long, float, double,
    etc... Use all the primitive data types that you are familiar with signed as well as
    unsigned.
Note: I want you to investigate this and the program you turn in should just print ”cout”
the final results. You don’t know how to capture errors yet so run each till it overflows
then back off by 1. Don’t need the program that tests for this.
*/

//system libraries
#include <iostream>   //Input/Output library
#include <fstream>    //File I/O library
#include <iomanip>    //Format library`
#include <cmath>      //Math library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void signedcharFactorial();
void unsignedcharFactorial();

void signedShortFactorial();
void unsignedShortFactorial();

void signedIntFactorial();
void unsignedIntFactorial();

void signedLongFactorial();
void unsignedLongFactorial();

void signedLongLongFactorial();
void unsignedLongLongFactorial();


void floatFactorial();
void doubleFactorial();

//Execution begins here
int main(int argv, char **argc)
{
    //Calculate factorials for different data types
    signedcharFactorial();
    unsignedcharFactorial();
    signedShortFactorial();
    unsignedShortFactorial();
    signedIntFactorial();
    unsignedIntFactorial();
    signedLongFactorial();
    unsignedLongFactorial();
    signedLongLongFactorial();
    unsignedLongLongFactorial();
    floatFactorial();
    doubleFactorial();
    //Exit the program
    return 0;
};
void signedcharFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    signed char result = 1;
    signed char tempResult = 1;
    int num = 1;
    fstream out;
    out.open("signedCharFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "signed char" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void signedShortFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    short result = 1;
    short tempResult = 1;
    int num = 1;
    fstream out;
    out.open("signedShortFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "signed short" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void signedIntFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    int result = 1;
    int tempResult = 1;
    int num = 1;
    fstream out;
    out.open("signedIntFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--;
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "signed int" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void signedLongFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    signed long result = 1;
    signed long tempResult = 1;
    int num = 1;
    fstream out;
    out.open("signedLongFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "signed long" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void signedLongLongFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    signed long long result = 1;
    signed long long tempResult = 1;
    int num = 1;
    string filename = "signedLongLongFactorials.dat";
    fstream out;
    out.open(filename, ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "signed long long" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void unsignedcharFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    unsigned char result = 1;
    unsigned char tempResult = 1;
    int num = 1;
    fstream out;
    out.open("unsignedCharFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "unsigned char" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void unsignedShortFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    unsigned short result = 1;
    unsigned short tempResult = 1;
    int num = 1;
    fstream out;
    out.open("unsignedShortFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "unsigned short" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void unsignedIntFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    unsigned int result = 1;
    unsigned int tempResult = 1;
    int num = 1;
    fstream out;
    out.open("unsignedIntFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "unsigned int" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void unsignedLongFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    unsigned long result = 1;
    unsigned long tempResult = 1;
    int num = 1;
    fstream out;
    out.open("unsignedLongFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "unsigned long" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void unsignedLongLongFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    unsigned long long result = 1;
    unsigned long long tempResult = 1;
    int num = 1;
    fstream out;
    out.open("unsignedLongLongFactorials.dat", ios::out | ios::app);
    while (tempResult > 0){
        tempResult = result * num;
        if (tempResult > 0){
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "unsigned long long" << " is for number " << setw(5) << num << " with value: " << result << endl;
}
void floatFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    float result = 1;
    float tempResult = 1;
    bool overflow = false;
    int num = 1;
    fstream out;
    out.open("floatFactorials.dat", ios::out | ios::app);
    out << left << setw(15) << num << result << endl;
    num = 2;
    while (!overflow){
        tempResult = result * num;
        if (tempResult > pow(10, 39)){ // Using a threshold to detect overflow for float
            overflow = true;
        }
        else {
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "float" << " is for number " << setw(5) << num << " with value: " << fixed << result << endl;
}
void doubleFactorial(){
    //Calculate factorials until overflow occurs, then back off by 1
    double result = 1;
    double tempResult = 1;
    bool overflow = false;
    int num = 1;
    fstream out;
    out.open("doubleFactorials.dat", ios::out | ios::app);
    out << left << setw(15) << num << result << endl;
    num = 2;
    while (!overflow){
        tempResult = result * num;
        if (tempResult > pow(10, 308)){ // Using a threshold to detect overflow for double
            overflow = true;
        }
        else {
            result = tempResult;
            out << left << setw(15) << num << result << endl;
            num++;
        }
    }
    num--; // Back off by 1
    cout << left << setw(21) << "Highest factorial in " << setw(18) << "double" << " is for number " << setw(5) << num << " with value: " << fixed << result << endl;
}
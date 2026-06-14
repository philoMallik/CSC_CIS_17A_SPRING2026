/*
Author: Philopatair Mallik
Date: 04/20/2026
purpose: Gaddis_9thE_Ch12_P8_ArrayFileFunctions.cpp 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <fstream>    //File Stream Library 
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void arrayToFile ( const string, int*, int);
void fileToArray ( const string, int*, int);

void fillArray (int*, int);
void prntArray (int*, int, int);

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    string fileName = "array.dat";
    int size = 100;
    int perLine = 10;
    int* arr = new int[size];

    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //fill the array with random 2 digit numbers
    fillArray(arr, size);

    //Display the array before writing to file
    cout << "This program demonstrates how to write an array to a file and read an array from a file." << endl;
    cout << "The array before writing to file: " << endl;
    prntArray(arr, size, perLine);

    //write the array to file
    arrayToFile(fileName, arr, size);

    //clear the array
    for (int i = 0; i < size; i++){
        arr[i] = 0;
    }

    //read the array from file
    fileToArray(fileName, arr, size);

    //Display the array after reading from file
    cout << "The array after reading from file: " << endl;
    prntArray(arr, size, perLine);

    //deallocate memory
    delete[] arr;

    //Exit the program
    return 0;
};

void arrayToFile ( const string fileName, int* arr, int size)
{
    fstream out;
    out.open(fileName, ios::out | ios::binary);
    for (int i = 0; i < size; i++){
        out.write(reinterpret_cast<char*>(&arr[i]), sizeof(arr[i]));
    }
    out.close();
}

void fileToArray ( const string fileName, int* arr, int size)
{
    fstream in;
    in.open(fileName, ios::in | ios::binary);
    for (int i = 0; i < size; i++){
        in.read(reinterpret_cast<char*>(&arr[i]), sizeof(arr[i]));
    }
    in.close();
}

void fillArray (int* arr, int size)
{
    for (int i = 0; i < size; i++){
        arr[i] = rand() % 90 + 10;
    }
}

void prntArray (int* arr, int size, int perLine)
{
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
        if ((i + 1) % perLine == 0){
            cout << endl;
        }
    }
}
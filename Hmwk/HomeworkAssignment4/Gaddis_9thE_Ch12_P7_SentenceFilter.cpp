/*
Author: Philopatair Mallik
Date: 04/20/2026
purpose: Gaddis_9thE_Ch12_P7_SentenceFilter.cpp
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

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    string inFile, outFile;
    fstream in, out;
    char ch;
    bool newSentence = true;

    //User Input
    cout<< "Enter the name of the first file to read from: ";
    cin >> inFile;
    cout<< "Enter the name of the second file to write to: ";
    cin >> outFile;

    //opening files
    in.open(inFile, ios::in);
    out.open(outFile, ios::out);

    //reading data from the first file
    //editing the data and writing to the second file
    while (in.get(ch))
    {
        if (ch == '.'){
            newSentence = true;
            out.put(ch);
        }
        else if (newSentence){
            if (ch <91 && ch > 64){
                out.put(ch);
                newSentence = false;
            }
            else if (ch <123 && ch > 96){
                out.put(ch - 32);
                newSentence = false;
            }
            else{
                out.put(ch);
            }      
        }
        else{
            if (ch <91 && ch > 64){
                out.put(ch + 32);
            }
            else if (ch <123 && ch > 96){
                out.put(ch);
            }
            else{
                out.put(ch);
            }
        }
    }

    //closing files
    in.close();
    out.close();

    //Exit the program
    return 0;
};
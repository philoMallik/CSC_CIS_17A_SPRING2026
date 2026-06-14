/*
    Author: Philopatair Mallik
    Date: 05/20/2026
    purpose: C++ Class Template for Numbers 
    */

    #include <iostream>
    using namespace std;
    
    
    #include "Numbers.h"
    
    // Default constructor
    Numbers::Numbers(int num){
        if (num < 0 || num > 9999) {
            cout << "Error: Number must be between 0 and 9999. Setting to 0." << endl;
            num = 0;
        }
        else number = num;
    }

    // Function to print the number in words
    void Numbers::print(){
        int n1 = number % 10;           //units digit 
        int n2 = (number / 10) % 10;    //tens digit
        int n3 = (number / 100) % 10;   //hundreds digit
        int n4 = (number / 1000) % 10;  //thousands digit

        string EnglishNum;

        switch (n4){
            case 0: break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9: EnglishNum += lessThan20[n4];
                    EnglishNum += " " + thousand;
                    break;
            default: break;
        }
        switch (n3){
            case 0: break;
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9: EnglishNum += lessThan20[n3];
                    EnglishNum += " " + hundred;
                    break;
            default: break;
        }
        switch (n2){
            case 0: break;
            case 1: if (n1 != 0) EnglishNum += lessThan20[n1 + 10];
                    else EnglishNum += lessThan20[n1];
                    break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
            case 8:
            case 9: EnglishNum += tens[n2];
                    if (n1 != 0) EnglishNum += " " + lessThan20[n1];
                    break;
            default: break;
        }
        if (number == 0) EnglishNum = lessThan20[0]; // Handle the case for zero
        cout << EnglishNum << endl;
    }
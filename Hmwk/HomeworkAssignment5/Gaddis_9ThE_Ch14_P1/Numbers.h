/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: C++ Class Template for Numbers 
*/

#ifndef NUMBERS_H
#define NUMBERS_H

#include <iostream>
using namespace std;

class Numbers
{
    private:
        int number;
        static string lessThan20[20];
        static string tens[10];
        static string hundred;
        static string thousand;
    public:
        Numbers(int num);
        void print();
        
};

string Numbers::lessThan20[20] = {"zero", "one", "two", "three", "four",
                                "five", "six", "seven", "eight", "nine",
                                "ten", "eleven", "twelve", "thirteen", "fourteen",
                                "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
string Numbers::tens[10] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};
string Numbers::hundred  = "hundred";
string Numbers::thousand = "thousand";

#endif // NUMBERS_H
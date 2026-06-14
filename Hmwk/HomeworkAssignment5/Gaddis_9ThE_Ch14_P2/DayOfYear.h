/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: C++ Class Template for DayOfYear 
*/

#ifndef DAYOFYEAR_H
#define DAYOFYEAR_H

#include <iostream>
using namespace std;


class DayOfYear
{
    private:
        int day;   // Day of the year (1-365)
        static string months[12]; // Array to hold month names
    public:
        DayOfYear(int d); // Constructor to initialize the day of the year
        void print(); // Function to print the day of the year in month/day format
};

string DayOfYear::months[12] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};


#endif // DAYOFYEAR_H
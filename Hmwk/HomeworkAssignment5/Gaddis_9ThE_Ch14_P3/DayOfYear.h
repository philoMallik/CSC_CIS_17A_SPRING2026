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
        int dayOfYr;   // Day of the year (1-365)
        int day; // Day of the month corresponding to the day of the month (1-31)
        int month; // Month corresponding to the day of the year (1-12)
        static string months[12]; // Array to hold month names
    public:
        DayOfYear(int d); // Constructor to initialize the day of the year
        void print(); // Function to print the day of the year in month/day format
        DayOfYear operator++(); // Prefix increment operator to move to the next day
        DayOfYear operator++(int); // Postfix increment operator to move to the next day
        DayOfYear operator--(); // Prefix decrement operator to move to the previous day
        DayOfYear operator--(int); // Postfix decrement operator to move to the previous day
};

string DayOfYear::months[12] = {"January", "February", "March", "April", "May", "June",
                                "July", "August", "September", "October", "November", "December"};


#endif // DAYOFYEAR_H
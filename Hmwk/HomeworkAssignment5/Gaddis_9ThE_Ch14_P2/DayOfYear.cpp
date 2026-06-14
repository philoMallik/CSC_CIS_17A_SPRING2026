/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: C++ Class Template for DayOfYear 
*/

#include <iostream>
using namespace std;

#include "DayOfYear.h"

DayOfYear::DayOfYear(int d) {
    if (d < 1 || d > 365) {
        cout << "Error: Day must be between 1 and 365. Setting to 1." << endl;
        day = 1;
    } else {
        day = d;
    }
}

void DayOfYear::print() {
    int monthIndex = 0;
    int dayOfMonth = day;

    // Array to hold the number of days in each month
    int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Determine the month and day of the month
    while (monthIndex < 12 && dayOfMonth > daysInMonths[monthIndex]) {
        dayOfMonth -= daysInMonths[monthIndex];
        monthIndex++;
    }

    // Print the result in month/day format
    cout << months[monthIndex] << " " << dayOfMonth << endl;
}
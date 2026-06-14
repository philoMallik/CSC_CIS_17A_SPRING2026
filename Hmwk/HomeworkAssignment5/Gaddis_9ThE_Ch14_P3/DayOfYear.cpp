/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: C++ Class Template for DayOfYear 
*/

#include <iostream>
using namespace std;

#include "DayOfYear.h"

DayOfYear::DayOfYear(int dayOfYr) {
    if (dayOfYr < 1 || dayOfYr > 365) {
        cout << "Error: Day must be between 1 and 365. Exiting program" << endl;
        this->dayOfYr = 1;
    } else {
        this->dayOfYr = dayOfYr;
    }
    this->day = 0; // Initialize day to 0
    this->month = 0; // Initialize month to 0
        // Array to hold the number of days in each month
    int daysInMonths[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Determine the month and day of the month
    while (this->month < 12 && this->day > daysInMonths[this->month]) {
        this->day -= daysInMonths[this->month];
        this->month++;
    }
    this->month = this->month + 1; // Adjust month to be 1-based index
}

void DayOfYear::print() {
    // Print the result in month/day format
    cout << months[this->month - 1] << " " << this->day << endl;
}

DayOfYear DayOfYear::operator++() {
    this->dayOfYr++;
    if (this->dayOfYr > 365) {
        this->dayOfYr = 1; // Wrap around to the first day of the year
    }
    return *this;
}

DayOfYear DayOfYear::operator++(int) {
    DayOfYear temp(dayOfYr); // Store the current state
    dayOfYr++; // Use the prefix increment to move to the next day
    if (dayOfYr > 365) {
        dayOfYr = 1; // Wrap around to the first day of the year
    }
    return temp; // Return the original state
}
/* 
 * File:    Date.cpp
 * Author:  Philopatair Mallik
 * Date:    05/20/2026
 * Purpose: Date class implementation file
 */

#include "Date.h"
#include <iostream>
#include <cstdlib>
using namespace std;

Date::Date(int m, int d, int y){
    if (m < 1 || m > 12) {
        cout << "Invalid month. Setting to 1." << endl;
        m = 1;
    }
    else month = m;
    if (d < 1 || d > 31) {
        cout << "Invalid day. Setting to 1." << endl;
        d = 1;
    }
    else day = d;
    year = y;
}

void Date::printNum() const {
    cout << month << "/" << day << "/" << year << endl;
}

void Date::printWrtn_DMY() const {
    
    cout << day << " " << months[month - 1] << " " << year << endl;
}

void Date::printWrtn_MDY() const {
    static const char* months[] = {"January", "February", "March", "April", "May", "June",
                                   "July", "August", "September", "October", "November", "December"};
    cout << months[month - 1] << " " << day << ", " << year << endl;
}

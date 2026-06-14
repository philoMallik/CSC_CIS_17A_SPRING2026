/* 
 * File:    Date.cpp
 * Author:  Philopatair Mallik
 * Date:    05/22/2026
 * Purpose: Date class implementation file
 */

#include "Date.h"
#include <iostream>
#include <cstdlib>
using namespace std;

    // Constructor
    Date::Date(int m, int d, int y){
        if (m < 1 || m > 12) {
            cout << "Invalid month. Setting to 1." << endl;
            m = 1;
        }
        else month = m;
        if (d < 1 || d > daysInMonth[m - 1]) {
            cout << "Invalid day. Setting to 1." << endl;
            d = 1;
        }
        else day = d;
        year = y;
    }

    // Member functions - print the date in different formats
    void Date::printNum() const {
        cout << month << "/" << day << "/" << year << endl;
    }

    void Date::printWrtn_DMY() const {
        cout << day << " " << months[month - 1] << " " << year << endl;
    }

    void Date::printWrtn_MDY() const {
        cout << months[month - 1] << " " << day << ", " << year << endl;
    }

    Date Date::operator++() {
        day++;
        if (day > daysInMonth[month - 1]) {
            day = 1;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
        }
        return *this;
    }
    Date Date::operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }
    Date Date::operator--() {
        day--;
        if (day < 1) {
            month--;
            if (month < 1) {
                month = 12;
                year--;
            }
            day = daysInMonth[month - 1];
        }
        return *this;
    }
    Date Date::operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    Date Date::operator-(const Date& other) {
        Date result = *this;
        for (int i = 0; i < other.day; i++) {
            --result;
        }
        return result;
    }

    ostream &operator<<(ostream& strm, const Date& date) {
        strm << Date::months[date.month - 1] << " " << date.day << ", " << date.year;
        return strm;
    }
    istream &operator>>(istream& strm, Date& date) {
        strm >> date.month >> date.day >> date.year;
        if (date.month < 1 || date.month > 12) {
            cout << "Invalid month. Setting to 1." << endl;
            date.month = 1;
        }
        if (date.day < 1 || date.day > Date::daysInMonth[date.month - 1]) {
            cout << "Invalid day. Setting to 1." << endl;
            date.day = 1;
        }
        return strm;
    }
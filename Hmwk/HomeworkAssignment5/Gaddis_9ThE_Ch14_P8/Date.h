/* 
 * File:    Date.h
 * Author:  Philopatair Mallik
 * Date:    05/22/2026
 * Purpose: Date class header file
 */

#ifndef DATE_H
#define DATE_H

#include <iostream>
using namespace std;

class Date; // Forward declaration

// Friend function prototypes
ostream& operator<<(ostream& strm, const Date& date);
istream& operator>>(istream& strm, Date& date);

class Date
{  
    private:
        int month;
        int day;
        int year;
        static const string months[12]; // Array of month names
        static const int daysInMonth[12]; // Array of days in each month
    public:
        Date(int m, int d, int y);
        void printNum() const;
        void printWrtn_DMY() const;
        void printWrtn_MDY() const;

        //operator overloads
        Date operator++();    // Prefix increment
        Date operator++(int); // Postfix increment
        Date operator--();    // Prefix decrement
        Date operator--(int); // Postfix decrement
        Date operator-(const Date& other); // Subtract days
        friend ostream& operator<<(ostream& strm, const Date& date); // Output stream overload
        friend istream& operator>>(istream& strm, Date& date); // Input stream overload

};

const int Date::daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string Date::months[12] = {"January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"};

#endif // DATE_H
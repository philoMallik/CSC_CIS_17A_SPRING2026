/* 
 * File:    Date.h
 * Author:  Philopatair Mallik
 * Date:    06/07/2026
 * Purpose: Date class Specification file
 */
#ifndef DATE_H
#define DATE_H

class Date
{  
    private:
        int month;
        int day;
        int year;
    public:
        // Exception handling for invalid month and day values
        class InvalidMonth{};
        class InvalidDay{};

        // Constructor
        Date(int m, int d, int y);

        // Member functions - print the date in different formats
        void printNum() const;
        void printWrtn_DMY() const;
        void printWrtn_MDY() const;
};

#endif // DATE_H
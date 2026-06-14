/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: NumDays class header file
*/

#ifndef NUMDAYS_H
#define NUMDAYS_H

class NumDays
{
    private:
        int hours; // Number of hours worked
        float days; // Number of days worked (calculated as hours / 8)
    public:
        // Constructor
        NumDays(int hours); // Constructor to initialize hours and calculate days

        // Accessor functions
        int getHours() const; // Function to return hours
        float getDays() const; // Function to return days

        // Mutator functions
        void setHours(int hours); // Function to set hours and update days

        //overloaded operators
        NumDays operator+(const NumDays& other) const; // Overload + operator to add two NumDays objects
        NumDays operator-(const NumDays& other) const; // Overload - operator to subtract two NumDays objects
        NumDays operator++(); // Overload prefix ++ operator to increment hours by 1
        NumDays operator++(int); // Overload postfix ++ operator to increment hours by 1
        NumDays operator--(); // Overload prefix -- operator to decrement hours by 1
        NumDays operator--(int); // Overload postfix -- operator to decrement hours by 1
};

#endif // NUMDAYS_H
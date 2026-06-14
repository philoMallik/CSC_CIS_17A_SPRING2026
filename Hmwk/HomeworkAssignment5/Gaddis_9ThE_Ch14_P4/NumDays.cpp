/*
Author: Philopatair Mallik
Date: 05/22/2026
purpose: NumDays class implementation file
*/


#include "NumDays.h"

// Constructor to initialize hours and calculate days
NumDays::NumDays(int hours){
    this->hours = hours;
    this->days = static_cast<float>(hours) / 8.0f; // Calculate days based on hours
}

// Accessor functions
int NumDays::getHours() const {
    return hours;
}

float NumDays::getDays() const {
    return days;
}

// Mutator functions
void NumDays::setHours(int hours) {
    this->hours = hours;
    this->days = static_cast<float>(hours) / 8.0f; // Update days based on new hours
}

// Overload operators
NumDays NumDays::operator+(const NumDays& other) const {
    return NumDays(this->hours + other.hours); // Create a new NumDays object with the sum of hours
}
NumDays NumDays::operator-(const NumDays& other) const {
    return NumDays(this->hours - other.hours); // Create a new NumDays object with the difference of hours
}
NumDays NumDays::operator++() {
    this->hours++; // Increment hours by 1
    this->days = static_cast<float>(this->hours) / 8.0f; // Update days based on new hours
    return *this; // Return the updated object
}   
NumDays NumDays::operator++(int) {
    NumDays temp = *this; // Create a temporary object to hold the current state
    this->hours++; // Increment hours by 1
    this->days = static_cast<float>(this->hours) / 8.0f; // Update days based on new hours
    return temp; // Return the original state before incrementing
}
NumDays NumDays::operator--() {
    this->hours--; // Decrement hours by 1
    this->days = static_cast<float>(this->hours) / 8.0f; // Update days based on new hours
    return *this; // Return the updated object
}
NumDays NumDays::operator--(int) {
    NumDays temp = *this; // Create a temporary object to hold the current state
    this->hours--; // Decrement hours by 1
    this->days = static_cast<float>(this->hours) / 8.0f; // Update days based on new hours
    return temp; // Return the original state before decrementing
}
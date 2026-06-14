/*
Filename:  Prob5Employee.h
Author:    Philopatair Mallik
Date:      06/09/2026
Purpose:   class Specification
*/

#ifndef PROB5EMPLOYEE_H
#define PROB5EMPLOYEE_H

//System libraries
#include  <iostream>
using namespace std;

class Prob5Employee;  //Forward declaration

class Prob5Employee{
  private:
    //Private variables defined here
    char MyName[20];    
    char JobTitle[20];  
    float HourlyRate;   
    int HoursWorked;    
    float GrossPay;     
    float NetPay;

    //member functions
    double Tax(float); //Utility Procedure

  public:
    //constructors
    Prob5Employee(const char[],const char[],float);

    //Accessors
    float getNetPay(float);
    float getGrossPay(float,int);
    
    //Mutators
    int setHoursWorked(int);
    float setHourlyRate(float);

    //Operator overloads

    //Member functions
    float CalculatePay(float,int);
    void toString();

};

#endif  // PROB5EMPLOYEE_H
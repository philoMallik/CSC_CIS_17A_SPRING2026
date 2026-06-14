/* 
 * File:    Prob5Employee.cpp
 * Author:  Philopatair Mallik
 * Date:    06/09/2026
 * Purpose: class implementation file
 */

//System libraries
#include <iostream>
#include <cstring>
using namespace std;

//User libraries
#include "Prob5Employee.h"

    // Constructors
    Prob5Employee::Prob5Employee(const char name[],const char jobTitle[],float hourlyRate){
        strcpy(MyName, name);
        strcpy(JobTitle, jobTitle);
        HourlyRate = setHourlyRate(hourlyRate);
        HoursWorked = 0;
        GrossPay = 0.0;
        NetPay = 0.0;
    }

    //Accessors
    float Prob5Employee::getGrossPay(float hourlyRate,int hoursWorked){
        if (hoursWorked <= 40){
            GrossPay = hourlyRate * hoursWorked;
        }
        else if(hoursWorked < 50){
            GrossPay = (hourlyRate * 40) + ((hourlyRate * 1.5) * (hoursWorked - 40));
        }
        else{
            GrossPay = (hourlyRate * 40) + ((hourlyRate * 1.5) * 10) + ((hourlyRate * 2) * (hoursWorked - 50));
        }
        return GrossPay;
    }
    float Prob5Employee::getNetPay(float hourlyRate){
        NetPay = GrossPay - Tax(GrossPay);
        return NetPay;
    }

    //Mutators
    int Prob5Employee::setHoursWorked(int hours){
        if (hours < 0 || hours >84){
            cout << "Unacceptable Hours Worked" << endl;
            HoursWorked = 0;
        }
        else{
            HoursWorked = hours;
        }
        return HoursWorked;
    }
    float Prob5Employee::setHourlyRate(float rate){
        if (rate < 0 || rate > 200){
            cout << "Unacceptable Hourly Rate" << endl;
            HourlyRate = 0;
        }
        else{
            HourlyRate = rate;
        }
        return HourlyRate;
    }

    //Operator overloads

    //Member functions
    double Prob5Employee::Tax(float grossPay){
        double totTax = 0.1 * grossPay;
        if (grossPay > 500 ) totTax += 0.1 * (grossPay - 500 );
        if (grossPay > 1000) totTax += 0.1 * (grossPay - 1000);
        return totTax;
    }

    void Prob5Employee::toString(){
        cout << "Name = " << MyName << " Job Title = " << JobTitle << endl;
        cout << " Hourly Rate = " << HourlyRate << " Hours Worked = " << HoursWorked << " Gross Pay = " << GrossPay << " Net Pay = " << NetPay << endl;
    }

    float Prob5Employee::CalculatePay(float x,int y){
        return getNetPay(getGrossPay(setHourlyRate(x),setHoursWorked(y)));
    }

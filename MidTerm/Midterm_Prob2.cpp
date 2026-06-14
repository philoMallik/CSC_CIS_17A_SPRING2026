/*
Author: Philopatair Mallik
Date: 04/22/2026
purpose: Midterm Problem 2 - 
2. (15 points) Develop an application using an array of structures created dynamically that
will determine the gross pay for any number of employees input. i.e. ask up front how
many employees you are inputting. The company pays ”straight-time” for the first 40
hours worked, double time for all hours worked in excess of 40 hours but less than 50
hours, and triple time for any hours worked over 50 hours.
The program should be able to loop and input the employee’s name, hours worked, and
the rate of pay. Once this has been done then output this information including the
gross pay in the form of a paycheck. The process starts all over again until you input
an invalid rate of pay or hours worked. This means a negative rate of pay or negative
number of hours worked is not acceptable.
Print it out like an actual paycheck with English language representing the check amount.
Printout like a company Paycheck with format:
• Company
• Address
• Name: Amount: numerical
• Amount: English of numerical value
• Signature Line:
Hint: Utilize the Roman Numeral Conversion Program to help with producing the check.
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries
struct Employee
{
    char name[50];
    float hoursWorked;
    float rateOfPay;
    float grossPay;
};
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void prntPaycheck(Employee*, int, char[], char[]);
void displayinEng(float amount);

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    const int MAX_STRAIGHT_HOURS = 40;
    const int MAX_DOUBLE_HOURS = 50;
    int numEmployees;
    char companyName[] = "XYZ Corporation";
    char companyAddress[] = "123 Main Street";

    //Initialize Variables
    cout << "This program calculates the gross pay for employees based on hours worked and rate of pay." << endl;
    cout << "Enter the number of employees: ";
    cin >> numEmployees;

    //Dynamically create an array of Employee structures
    Employee *employees = new Employee[numEmployees];

    //Input employee data
    int i = 0;
    do{   
        cout << "Enter name for employee " << (i + 1) << ": ";
        cin.ignore(); // Clear the input buffer
        cin.getline(employees[i].name, 50);
        cout << "Enter hours worked for " << employees[i].name << ": ";
        cin >> employees[i].hoursWorked;
        cout << "Enter rate of pay for " << employees[i].name << ": ";
        cin >> employees[i].rateOfPay;

        //Calculate gross pay
        if (employees[i].hoursWorked <= MAX_STRAIGHT_HOURS)
        {
            employees[i].grossPay = employees[i].hoursWorked * employees[i].rateOfPay;
        }
        else if (employees[i].hoursWorked <= MAX_DOUBLE_HOURS)
        {
            employees[i].grossPay=(MAX_STRAIGHT_HOURS*employees[i].rateOfPay)+
                                    ((employees[i].hoursWorked-MAX_STRAIGHT_HOURS)*2*employees[i].rateOfPay);
        }
        else
        {
            employees[i].grossPay=(MAX_STRAIGHT_HOURS*employees[i].rateOfPay)+
                                    ((MAX_DOUBLE_HOURS-MAX_STRAIGHT_HOURS)*2*employees[i].rateOfPay)+
                                    ((employees[i].hoursWorked-MAX_DOUBLE_HOURS)*3*employees[i].rateOfPay);
        }

        //Output paycheck information
        prntPaycheck(employees, i, companyName, companyAddress);

        //Increment employee index
        i++;

    }while(employees->rateOfPay >= 0 && employees->hoursWorked >= 0 && i<numEmployees);

    //Deallocate memory for employees
    delete[] employees;

    //Exit the program
    return 0;
};
void prntPaycheck(Employee *employee, int index, char companyName[], char companyAddress[])
{
    cout << "Company: " << companyName << endl;
    cout << "Address: " << companyAddress << endl;
    cout << "Name: " << employee[index].name << " Amount: $" << employee[index].grossPay << endl;
    cout << "Amount in English: ";displayinEng(employee[index].grossPay);
    cout << endl;
    cout << "Signature Line: ______________________" << endl;
}

void displayinEng(float amount)
{   
    int dollars = static_cast<int>(amount),
        cents   = static_cast<int>((amount - dollars) * 100);
    int n1      = dollars%10,           // units
        n10     = (dollars/10)%10,     // tens
        n100    = (dollars/100)%10,    // hundreds
        n1000   = (dollars/1000)%10,   // thousands
        n10000  = (dollars/10000)%10;  // ten-thousands
    switch (n10000)
    {
        case 0: break;
        case 1: cout << "Ten Thousand "; 
                break;
        case 2: cout << "Twenty Thousand "; 
                break;
        case 3: cout << "Thirty Thousand "; 
                break;
        case 4: cout << "Forty Thousand "; 
                break;
        case 5: cout << "Fifty Thousand "; 
                break;
        case 6: cout << "Sixty Thousand "; 
                break;
        case 7: cout << "Seventy Thousand "; 
                break;
        case 8: cout << "Eighty Thousand "; 
                break;
        case 9: cout << "Ninety Thousand "; 
                break;
        default : cout << "Error in n10000 switch statement" << endl;
    }
    switch (n1000)
    {
        case 0: break;
        case 1: if(n10000 > 0) cout << ", ";
                cout << "One Thousand "; 
                break;
        case 2: if(n10000 > 0) cout << ", ";
                cout << "Two Thousand "; 
                break;
        case 3: if(n10000 > 0) cout << ", ";
                cout << "Three Thousand "; 
                break;
        case 4: if(n10000 > 0) cout << ", ";
                cout << "Four Thousand "; 
                break;
        case 5: if(n10000 > 0) cout << ", ";
                cout << "Five Thousand "; 
                break;
        case 6: if(n10000 > 0) cout << ", ";
                cout << "Six Thousand "; 
                break;
        case 7: if(n10000 > 0) cout << ", ";
                cout << "Seven Thousand "; 
                break;
        case 8: if(n10000 > 0) cout << ", ";
                cout << "Eight Thousand "; 
                break;
        case 9: if(n10000 > 0) cout << ", ";
                cout << "Nine Thousand "; 
                break;
        default : cout << "Error in n1000 switch statement" << endl;
    }
    switch (n100)
    {
        case 0: break;
        case 1: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "One Hundred "; 
                break;
        case 2: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Two Hundred "; 
                break;
        case 3: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Three Hundred "; 
                break;
        case 4: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Four Hundred "; 
                break;
        case 5: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Five Hundred "; 
                break;
        case 6: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Six Hundred "; 
                break;
        case 7: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Seven Hundred "; 
                break;
        case 8: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Eight Hundred "; 
                break;
        case 9: if(n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Nine Hundred "; 
                break;
        default : cout << "Error in n100 switch statement" << endl;
    }
    switch (n10)
    {
        case 0: break;
        case 1: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Ten"; 
                break;
        case 2: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Twenty "; 
                break;
        case 3: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Thirty "; 
                break;
        case 4: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Forty "; 
                break;
        case 5: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Fifty "; 
                break;
        case 6: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Sixty "; 
                break;
        case 7: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Seventy "; 
                break;
        case 8: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Eighty "; 
                break;
        case 9: if(n100 > 0 || n1000 > 0 || n10000 > 0) cout << ", ";
                cout << "Ninety "; 
                break;
        default : cout << "Error in n10 switch statement" << endl;
    }
    cout << "and " << cents << "/100 Dollars" << endl;
}

/*
Author: Philopatair Mallik
Date:   06/07/2026
purpose:Gaddis 9th Edition Chapter 15 Problem 1 
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
#include "Employee.h"
#include "ProductionWorker.h"
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void displayEmployee(const Employee &emp);
void displayProductionWorker(const ProductionWorker &worker);
Employee getEmployeeInfo();
ProductionWorker getProductionWorkerInfo();
//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    Employee emp("John Doe", 10001, 10152020);
    ProductionWorker worker("Jane Smith", 10002, 01012020, 1, 17.50);
    
    //Display Employee and Production Worker information
    cout << "Employee Information:" << endl;
    displayEmployee(emp);
    cout << "Production Worker Information:" << endl;
    displayProductionWorker(worker);

    //Get new employee and production worker information from user
    cout << "\nEnter new employee information:" << endl;
    Employee newEmp = getEmployeeInfo();
    cout << "\nEnter new production worker information:" << endl;
    ProductionWorker newWorker = getProductionWorkerInfo();

    //Display Inputs/Outputs
    cout << "\nNew Employee Information:" << endl;
    displayEmployee(newEmp);
    cout << endl;
    cout << "New Production Worker Information:" << endl;
    displayProductionWorker(newWorker);

    //Exit the program
    return 0;
};
void displayEmployee(const Employee &emp)
{
    cout << "Employee Name: " << emp.getName() << endl;
    cout << "Employee Number: " << emp.getNum() << endl;
    cout << "Hire Date: " << emp.getHDate() << endl;
}
void displayProductionWorker(const ProductionWorker &worker)
{
    displayEmployee(worker); // Display base class information
    cout << "Shift: " << (worker.getShift() == 1 ? "Day" : "Night") << endl;
    cout << "Hourly Pay Rate: $" << worker.getPayRate() << endl;
}
Employee getEmployeeInfo()
{
    string name;
    int num, hDate;

    cout << "Enter employee name: ";
    getline(cin, name);
    cout << "Enter employee number: ";
    cin >> num;
    cout << "Enter hire date (MMDDYYYY): ";
    cin >> hDate;

    return Employee(name, num, hDate);
}
ProductionWorker getProductionWorkerInfo()
{
    string name;
    int num, hDate, shift;
    float payRate;

    cin.ignore(); // Ignore the newline character left in the input buffer
    cout << "Enter employee name: ";
    getline(cin, name);
    cout << "Enter employee number: ";
    cin >> num;
    cout << "Enter hire date (MMDDYYYY): ";
    cin >> hDate;
    cout << "Enter shift (1 for Day, 2 for Night): ";
    cin >> shift;
    cout << "Enter hourly pay rate: ";
    cin >> payRate;

    return ProductionWorker(name, num, hDate, shift, payRate);
}
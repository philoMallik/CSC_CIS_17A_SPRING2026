/*
Author: Philopatair Mallik
Date: 04/22/2026
purpose: Midterm Problem 1 - 
1. (15 points) Develop an application using a structure for a customer that will determine if
he/she has exceeded his/her checking account balance. For each customer, the following
facts are available and the structure should include in the following order:
    a. Account number (Five digits only, i.e. test for this)
    b. Name
    c. Address
    d. Balance at the beginning of the month
    e. Record all checks written by this customer this month Loop until customer is
    through entering checks. Use dynamic array.
    f. Record all deposits credited to this customer’s account this month. Loop until
customer is through entering deposits. Use dynamic array.
Dynamically create the structure.
The program should input each of these facts from input dialogs, store in a structure,
calculate the new balance, display the new balance and debit the account $20 if over-
drawn. Also, if overdrawn, tell the customer the additional $20 fee has been accessed
and what the balance would be with this fee included. Make sure to output the contents
of the structure.
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
struct Customer
{
    int accountNumber;    //Five digits only
    char name[50];
    char address[100];
    float initBal;        //Balance at the beginning of the month
    float *checks;       //Record all checks written by this customer this month
    int numChecks;       //Number of checks written
    float *deposits;     //Record all deposits credited to this customer’s account this month
    int numDeposits;     //Number of deposits credited
};
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void prntCustData(Customer*, float);

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    Customer *customer = new Customer;

    //Initialize Variables
    cout << "This a program to keep track of a customer's checking account balance." << endl;
    cout << "Please enter the following information about the customer:" << endl;
    cout << "Account Number (Five digits only): ";
    cin >> customer->accountNumber;
    cout << "Name: ";
    cin.ignore(); // Clear the input buffer
    cin.getline(customer->name, 50);
    cout << "Address: ";
    cin.getline(customer->address, 100);
    cout << "Balance at the beginning of the month: ";
    cin >> customer->initBal;
    
    //Input checks
    int numChecks;
    cout << "Enter the number of checks written this month: ";
    cin >> numChecks;
    customer->checks = new float[numChecks];
    customer->numChecks = 0;
    for (int i = 0; i < numChecks; i++)
    {
        cout << "Enter amount for check " << (i + 1) << ": ";
        cin >> customer->checks[i];
        customer->numChecks++;
    }

    //Input deposits
    int numDeposits;
    cout << "Enter the number of deposits credited this month: ";
    cin >> numDeposits;
    customer->deposits = new float[numDeposits];
    customer->numDeposits = 0;
    for (int i = 0; i < numDeposits; i++)
    {
        cout << "Enter amount for deposit " << (i + 1) << ": ";
        cin >> customer->deposits[i];
        customer->numDeposits++;
    }

    //Mapping Process -> Inputs to Outputs
    float newBalance = customer->initBal;
    for (int i = 0; i < customer->numChecks; i++)
    {
        newBalance -= customer->checks[i];
    }
    for (int i = 0; i < customer->numDeposits; i++)
    {
        newBalance += customer->deposits[i];
    }
    if (newBalance < 0)
    {
        newBalance -= 20; // Overdraft fee
        cout << "Account overdrawn. An additional $20 fee has been assessed." << endl;
        cout << "New balance with fee included: $" << newBalance << endl;
    }

    //Output the new balance and customer data
    prntCustData(customer, newBalance);

    //Exit the program
    return 0;
};
void prntCustData(Customer *customer, float newBalance)
{
    cout << "Customer Information:" << endl;
    cout << "Account Number: " << customer->accountNumber << endl;
    cout << "Name: " << customer->name << endl;
    cout << "Address: " << customer->address << endl;
    cout << "Initial Balance: $" << customer->initBal << endl;
    cout << "Checks Written: ";
    for (int i = 0; i < customer->numChecks; i++)
    {
        cout << i+1 << ". $" << customer->checks[i] << endl;
    }
    cout << "Deposits Credited: ";
    for (int i = 0; i < customer->numDeposits; i++)
    {
        cout << i+1 << ". $" << customer->deposits[i] << endl;
    }
    cout << "New Balance: $" << newBalance << endl;
}
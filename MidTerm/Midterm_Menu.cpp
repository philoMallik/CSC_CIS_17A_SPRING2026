/*
Author: Philopatair Mallik
Date:   04/24/2026
purpose: CSC 17A Midterm Menu 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
#include <fstream>    //File I/O Library
using namespace std;

//User libraries
#include "Customer.h"
#include "Employee.h"
#include "Array.h"
#include "Stats.h"
#include "Prime.h"
#include "Primes.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void problem1();
void prntCustData(Customer*, float);

void problem2();
void prntPaycheck(Employee*, int, char[], char[]);
void displayinEng(float amount);

void problem3();
Array *fillAry(int,int);        //Fill an array and put into a structure
void prntAry(const Array *,int);//Print the array 
int *copy(const int *,int);     //Copy the array
void mrkSort(int *,int);        //Sort an array
void prtStat(const Stats *);    //Print the structure
void rcvrMem(Array *);          //Recover memory from the Array Structure
void rcvrMem(Stats *);          //Recover memory from Statistics Structure
Stats *stat(const Array *);     //Find & store mean, median, & modes in structure

void problem4();
int encrypt(int, int, int, int);
int decrypt(int, int, int, int);
void swap(int &a, int &b);

void problem5();
double factorial(int);

void problem6();

void problem7();
Primes *factor(int);            //Factor the number into it’s Primes
void prtPrms(const Primes *);   //Print the prime factors
bool isPrime(int);              //Determine if the number is Prime
int power(int,int &);           //What power is this factor and remove from n
int nPrimes(int);               //How many Primes
void cleanUp(Primes *);         //Clean it all up

int main(int argv, char **argc){
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    unsigned short choose;
    unsigned short problemCount;
    //Initialize Variables
    problemCount = 7;

    //Display the Menu and loop until the user chooses to exit
    do{
        cout << "This is a Menu program" << endl;
        cout << "Type 1  for problem X1" << endl;
        cout << "Type 2  for problem x2" << endl;
        cout << "Type 3  for problem x3" << endl;
        cout << "Type 4  for problem x4" << endl;
        cout << "Type 5  for problem x5" << endl;
        cout << "Type 6  for problem x6" << endl;
        cout << "Type 7  for problem x7" << endl;
        cout << "Type any other number to exit" << endl;
        cin >> choose;

        switch (choose){
            case  1:problem1();
                    break;
            case  2:problem2();
                    break;
            case  3:problem3();
                    break;
            case  4:problem4();
                    break;
            case  5:problem5();
                    break;
            case  6:problem6();
                    break;
            case  7:problem7();
                    break;
            default:cout << "You have choosen to exit" << endl;
        }
    }while (choose >= 1 && choose <= problemCount);

    //Exit the program
    return 0;
};
void problem1(){
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
}
void prntCustData(Customer *customer, float newBalance){
    cout << "Customer Information:" << endl;
    cout << "Account Number:      " << customer->accountNumber << endl;
    cout << "Name:                " << customer->name << endl;
    cout << "Address:             " << customer->address << endl;
    cout << "Initial Balance:      $" << customer->initBal << endl;
    cout << "Checks Written:      " << endl;
    for (int i = 0; i < customer->numChecks; i++){
        cout << "\t" << i+1 << ". $" << customer->checks[i] << endl;
    }
    cout << "Deposits Credited:" << endl;
    for (int i = 0; i < customer->numDeposits; i++){
        cout << "\t" << i+1 << ". $" << customer->deposits[i] << endl;
    }
    cout << "New Balance:           $" << newBalance << endl;
}
void problem2(){
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
}
void prntPaycheck(Employee *employee, int index, char companyName[], char companyAddress[]){
    cout << "Company: " << companyName << endl;
    cout << "Address: " << companyAddress << endl;
    cout << "Name: " << employee[index].name << " Amount: $" << employee[index].grossPay << endl;
    cout << "Amount in English: ";
    displayinEng(employee[index].grossPay);
    cout << "Signature Line: ______________________" << endl;
}
void displayinEng(float amount){   
    int dollars = static_cast<int>(amount),
        cents   = static_cast<int>((amount - dollars) * 100);
    int n1      = dollars%10,           // units
        n10     = (dollars/10)%10,     // tens
        n100    = (dollars/100)%10,    // hundreds
        n1000   = (dollars/1000)%10,   // thousands
        n10000  = (dollars/10000)%10;  // ten-thousands
    switch (n10000){
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
    switch (n1000){
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
    switch (n100){
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
    switch (n10){
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
    switch (n1){
        case 0: break;
        case 1: cout << "One "; 
                break;
        case 2: cout << "Two "; 
                break;
        case 3: cout << "Three "; 
                break;
        case 4: cout << "Four "; 
                break;
        case 5: cout << "Five "; 
                break;
        case 6: cout << "Six "; 
                break;
        case 7: cout << "Seven "; 
                break;
        case 8: cout << "Eight "; 
                break;
        case 9: cout << "Nine "; 
                break;
        default : cout << "Error in n1 switch statement" << endl;
    }
    cout << "and " << cents << "/100 Dollars" << endl;
}
void problem3(){
    //Declare variables
    int arySize;//Array Size
    int modNum; //Number to control the modes (digits 0 to 9 allowed)
    Array *array;
    
    //Input the size and mod number
    cout<<"This program develops an array to be analyzed"<<endl;
    cout<<"Array size from mod number to 100"<<endl;
    cout<<"Mod number from 2 to 10"<<endl;
    cout<<"Input the Array Size and the mod number to be used."<<endl;
    cin>>arySize>>modNum;
    cout<<endl<<endl;
    
    //Fill the array
    array=fillAry(arySize,modNum);
    
    //Print the initial array
    cout<<"Original Array before sorting"<<endl;
    prntAry(array,10);
    
    //Sort the array
    mrkSort(array->data,array->size);
    cout<<"Sorted Array to be utilize for the stat function"<<endl;
    prntAry(array,10);
    
    //Calculate some of the statistics
    Stats *stats=stat(array);
    
    //Print the statistics
    prtStat(stats);
    
    //Recover allocated memory
    rcvrMem(array);
    rcvrMem(stats);
}
int *copy(const int *a,int n){
    //Declare and allocate an array
    //that is a c
    int *b=new int[n];
    //Fill
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    //Return the copy
    return b;
}
void mrkSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(array[j]<array[i]){
                int temp=array[i];
                array[i]=array[j];
                array[j]=temp;
            }
        }
    }
}
void rcvrMem(Stats *stats){
    rcvrMem(stats->mode);
    delete stats;
}
void rcvrMem(Array *array){
    delete []array->data;
    delete array;
}
void prntAry(const Array *array,int perLine){
    //Output the array
    for(int i=0;i<array->size;i++){
        cout<<array->data[i]<<" ";
        if(i%perLine==(perLine-1))cout<<endl;
    }
    cout<<endl;
}
Array *fillAry(int n, int modNum){
    //Allocate memory
    Array *array=new Array;
    array->size=n;
    array->data=new int[array->size];
    
    //Fill the array with mod numbers
    for(int i=0;i<n;i++){
        array->data[i]=i%modNum;
    }
    
    //Exit function
    return array;
}
void prtStat(const Stats *ary){
    cout<<endl;
    cout<<"The average of the array = "<<ary->avg<<endl;
    cout<<"The median of the array  = "<<ary->median<<endl;
    cout<<"The number of modes      = "<<
            ary->mode->size<<endl;
    cout<<"The max Frequency        = "<<
            ary->modFreq<<endl;
    if(ary->mode->size==0){
        cout<<"The mode set             = {null}"<<endl;
        return;
    }
    cout<<"The mode set             = {";
    for(int i=0;i<ary->mode->size-1;i++){
        cout<<ary->mode->data[i]<<",";
    }
    cout<<ary->mode->data[ary->mode->size-1]<<"}"<<endl;
}
Stats *stat(const Array *array){
    //Non-working stub to be completed by the student
    cout<<endl<<"Stat function to be completed by the student"<<endl;

    //Declare and allocate a Stats structure
    Stats *stats=new Stats;
    stats->mode=new Array;
    int sum,
        count,
        currentFreq,
        maxFreq,
        nModes,
        modeIndex;

    //Calculate the mean
    sum = 0;
    count = 0;
    for(int i=0;i<array->size;i++){
        sum+=array->data[i];
        count++;
    }
    stats->avg=(sum*1.0f)/count;

    //Calculate the median
    if(array->size%2==0){
        stats->median=(array->data[array->size/2]+array->data[array->size/2-1])/2.0f;
    }else{
        stats->median=array->data[array->size/2];
    }

    //Calculate the mode
        //1. Calculate max frequency
        currentFreq = 1;
        maxFreq = 1;
        for(int i=1;i<=array->size;i++){
            if(i< array->size && array->data[i]==array->data[i-1]){
                currentFreq++;
            }else{
                if(currentFreq>maxFreq){
                    maxFreq=currentFreq;
                }
                currentFreq=1;
            }
        }
        stats->modFreq=maxFreq;

        //2. Count how many modes there are
        nModes = 0;
        currentFreq = 1;
        for(int i=1;i<=array->size;i++){
            if(i< array->size && array->data[i]==array->data[i-1]){
                currentFreq++;
            }else{
                if(currentFreq==maxFreq){
                    nModes++;
                }
                currentFreq=1;
            }
        }

        //3. allocate the mode array
        stats->mode->size=nModes;
        stats->mode->data=new int[nModes];

        //4. Find the modes and fill the mode array
        currentFreq = 1;
        modeIndex = 0;
        for(int i=1;i<=array->size;i++){
            if(i< array->size && array->data[i]==array->data[i-1]){
                currentFreq++;
            }else{
                if(currentFreq==maxFreq){
                    stats->mode->data[modeIndex++] = array->data[i-1];
                }
                currentFreq=1;
            }
        }

    return stats;
}
void problem4(){
    //Declare Variables
    int num;
    int n4, n3, n2, n1;
    int choice = 0;
    int encryptedNum, decryptedNum;

    //Initialize Variables
    cout << "This program encrypts and decrypts four-digit integers using digits 0-7." << endl;
    do{
        cout << "Enter 1 to encrypt a number, 2 to decrypt a number or 3 to exit: ";
        cin >> choice;
        switch(choice){
            case 1: cout << "Enter a four-digit integer (digits 0-7 only): ";
                    cin >> num;

                    //Extract digits from the number
                    n4 = num%10,     
                    n3 = (num/10)%10,
                    n2 = (num/100)%10,    
                    n1 = (num/1000)%10;

                    //Check for invalid digits
                    if (n1 > 7 || n2 > 7 || n3 > 7 || n4 > 7) {
                        cout << "Error: All digits must be between 0 and 7." << endl;
                        break;
                    }
                    else {
                        //Encrypt the number
                        encryptedNum = encrypt(n1, n2, n3, n4);
                        cout << "Encrypted number: " << encryptedNum << endl;
                    }
                    break;
            case 2: cout << "Enter a four-digit encrypted integer (digits 0-7 only): ";
                    cin >> num;

                    //Extract digits from the number
                    n4 = num%10,     
                    n3 = (num/10)%10,
                    n2 = (num/100)%10,    
                    n1 = (num/1000)%10;

                    //Check for invalid digits
                    if (n1 > 7 || n2 > 7 || n3 > 7 || n4 > 7) {
                            cout << "Error: All digits must be between 0 and 7." << endl;
                            break;
                    }
                    else {
                        //Decrypt the number
                        decryptedNum = decrypt(n1, n2, n3, n4);
                        cout << "Decrypted number: " << decryptedNum << endl;
                    }
                    break;
            case 3: cout << "Exiting the program." << endl;
                    break;
            default: cout << "Invalid choice. Please enter 1 to encrypt, 2 to decrypt, or 3 to exit." << endl;

        }
    }while(choice != 3);
}
int encrypt(int n1, int n2, int n3, int n4){   
    //Declare variables for digits
    int encryptedNum;

    //Encryption logic here
    //step1: Replace each digit by (the sum of that digit plus 3 modulus 8)
    n1 = (n1 + 3) % 8;
    n2 = (n2 + 3) % 8;
    n3 = (n3 + 3) % 8;
    n4 = (n4 + 3) % 8;

    //step2: Swap the first digit with the third, and swap the second digit with the fourth
    swap(n1, n3);
    swap(n2, n4);

    //Combine the digits back into a single integer
    encryptedNum = n1 * 1000 + n2 * 100 + n3 * 10 + n4;

    //Return the encrypted number
    return encryptedNum;
}
int decrypt(int n1, int n2, int n3, int n4){
    //Declare variables for digits
    int decryptedNum;
    int decryption[8][2] = {{0,3},{1,4},{2,5},{3,6},{4,7},{5,0},{6,1},{7,2}};

    //Decryption logic here
    //step1: Swap the first digit with the third, and swap the second digit with the fourth
    swap(n1, n3);
    swap(n2, n4);

    //step2: Remap each letter back to the original digit by reversing the encryption process
    for (int i = 0; i < 8; i++) {  
        if (n1 == decryption[i][1]) n1 = decryption[i][0];
        if (n2 == decryption[i][1]) n2 = decryption[i][0];
        if (n3 == decryption[i][1]) n3 = decryption[i][0];
        if (n4 == decryption[i][1]) n4 = decryption[i][0];
    }

    //Combine the digits back into a single integer
    decryptedNum = n1 * 1000 + n2 * 100 + n3 * 10 + n4;

    //Return the decrypted number
    return decryptedNum;
}
void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
void problem5(){
    int signedCharMax = 5,
        unsignedCharMax = 9,
        signedShortMax = 7,
        unsignedShortMax = 17,
        signedIntMax = 16,
        unsignedIntMax = 33,
        signedLongMax = 20,
        unsignedLongMax = 65,
        signedLongLongMax = 20,
        unsignedLongLongMax = 65,
        floatMax = 34,
        doubleMax = 170;

    cout << "Here is the result for the most factorial can be done by each variable type:" << endl;
    cout << "Highest factorial in  signed char        is for number " << setw(3) << signedCharMax       << endl;
    cout << "Highest factorial in  unsigned char      is for number " << setw(3) << unsignedCharMax    << endl;
    cout << "Highest factorial in  signed short       is for number " << setw(3) << signedShortMax      << endl;
    cout << "Highest factorial in  unsigned short     is for number " << setw(3) << unsignedShortMax    << endl;
    cout << "Highest factorial in  signed int         is for number " << setw(3) << signedIntMax        << endl;
    cout << "Highest factorial in  unsigned int       is for number " << setw(3) << unsignedIntMax      << endl;
    cout << "Highest factorial in  signed long        is for number " << setw(3) << signedLongMax       << endl;
    cout << "Highest factorial in  unsigned long      is for number " << setw(3) << unsignedLongMax     << endl;
    cout << "Highest factorial in  signed long long   is for number " << setw(3) << signedLongLongMax   << endl;
    cout << "Highest factorial in  unsigned long long is for number " << setw(3) << unsignedLongLongMax << endl;
    cout << "Highest factorial in  float              is for number " << setw(3) << floatMax            << endl;
    cout << "Highest factorial in  double             is for number " << setw(3) << doubleMax           << endl;
}
double factorial(int n){
    if (n == 0 || n == 1) return 1;
    double result = 1;
    for (int i = 2; i <= n; i++){
        result *= i;
    }
    return result;
}
void problem6(){
    cout << left;
    cout << "Conversion to NASA 4 byte format" << endl;
    cout << "a.    49.1875 Base 10 = " << setw(32) << "31.3"                             << " Base 16" << endl;
    cout << "                      = " << setw(32) << "61.14"                            << " Base 8" << endl;
    cout << "                      = " << setw(32) << "110001.0011"                      << " Base 2" << endl;
    cout << "                      = " << setw(32) << "01100010011000000000000000000110" << " Base 2 (NASA 4 byte format)" << endl;
    cout << "                      = " << setw(32) << "62600006"                         << " Base 16 (NASA 4 byte format)" << endl;
    cout << "   3.07421875 Base 10 = " << setw(32) << "3.13"                             << " Base 16" << endl;
    cout << "                      = " << setw(32) << "3.46"                             << " Base 8" << endl;
    cout << "                      = " << setw(32) << "11.00010011"                      << " Base 2" << endl;
    cout << "                      = " << setw(32) << "01100010011000000000000000000010" << " Base 2 (NASA 4 byte format)" << endl;
    cout << "                      = " << setw(32) << "62600002"                         << " Base 16 (NASA 4 byte format)" << endl;
    cout << "          0.2 Base 10 = " << setw(40) << "0.\033[4m3\033[0m"                << " Base 16" << endl;
    cout << "                      = " << setw(40) << "0.\033[4m1463\033[0m"             << " Base 8" << endl;
    cout << "                      = " << setw(40) << "0.\033[4m0011\033[0m"             << " Base 2" << endl;
    cout << "                      = " << setw(32) << "01100110011001100110011011111110" << " Base 2 (NASA 4 byte format)" << endl;
    cout << "                      = " << setw(32) << "666666FE"                         << " Base 16 (NASA 4 byte format)" << endl;
    cout << "b.   -49.1875 Base 10 = " << setw(40) << "\033[4m9\033[0m50.8125"           << " Base 10 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4mF\033[0mCE.D"              << " Base 16 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4m7\033[0m16.64"             << " Base 8 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4m1\033[0m001110.1101"       << " Base 2" << endl;
    cout << "                      = " << setw(32) << "10011101101000000000000000000110" << " Base 2 (NASA 4 byte format)" << endl;
    cout << "                      = " << setw(32) << "90A00006"                         << " Base 16 (NASA 4 byte format)" << endl;
    cout << "  -3.07421875 Base 10 = " << setw(40) << "\033[4m9\033[0m6.92578125"        << " Base 10 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4mF\033[0mC.ED"              << " Base 16 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4m7\033[0m4.32"              << " Base 8 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4m1\033[0m00.11101101"       << " Base 2" << endl;
    cout << "                      = " << setw(32) << "10011101101000000000000000000010" << " Base 2 (NASA 4 byte format)" << endl;
    cout << "                      = " << setw(32) << "9DA00002"                         << " Base 16 (NASA 4 byte format)" << endl;
    cout << "         -0.2 Base 10 = " << setw(40) << "\033[4m9\033[0m.8"                << " Base 10 negative format" << endl;
    cout << "                      = " << setw(48) << "\033[4mF\033[0m.\033[4mD\033[0m"  << " Base 16 negative format" << endl;
    cout << "                      = " << setw(40) << "\033[4m7\033[0m.6315"             << " Base 8 negative format" << endl;
    cout << "                      = " << setw(48) << "\033[4m1\033[0m.\033[4m1101\033[0m"<< " Base 2" << endl;
    cout << "                      = " << setw(32) << "11101110111011101110111000000000" << " Base 2 (NASA 4 byte format)" << endl;
    cout << "                      = " << setw(32) << "EEEEEE00"                         << " Base 16 (NASA 4 byte format)" << endl;
    cout << "c.           69999902 = 01101001100110011001100100000010" << endl;
    cout << "                      = 3.3    in base 10" << endl;
    cout << "             69999903 = 01101001100110011001100100000011" << endl;
    cout << "                      = 6.0375 in base 10" << endl;
    cout << "             966667FF = 10010110011001100110011111111111" << endl;
    cout << "                      = -0.1041667 *10^-35 in base 10" << endl;
}
void problem7(){
    //Declare Variables
    int num;

    //Initialize Variables
    cout << "This program factors an input integer into its prime numbers." << endl;
    cout << "Enter an integer between 2 and 65000: ";
    cin >> num;

    //Factor the number into its primes
    Primes *primeFactors = factor(num);

    //Print the prime factors
    prtPrms(primeFactors);

    //Clean up
    cleanUp(primeFactors);
}
Primes *factor(int num){
    //Declare variables
    int index = 0;
    int temp = num;

    Primes *primeFactors = new Primes;
    primeFactors->n = num;
    primeFactors->nPrimes = nPrimes(num);
    primeFactors->pStrAry = new Prime[primeFactors->nPrimes];

    //Factor the number into its primes
    for (int i = 2; i <= num; i++){
        if (isPrime(i)){
            if (temp % i == 0){
                primeFactors->pStrAry[index].prime = i;
                primeFactors->pStrAry[index].power = power(i, temp);
                index++;
            }
        }
    }

    //Return the prime factors
    return primeFactors;
}
void prtPrms(const Primes *primeFactors){
    cout << primeFactors->n << " = ";
    for (int i = 0; i < primeFactors->nPrimes; i++) {
        cout << primeFactors->pStrAry[i].prime << "^" << (int)primeFactors->pStrAry[i].power;
        if (i < primeFactors->nPrimes - 1) cout << " * ";
    }
    cout << endl;
}
bool isPrime(int num){
    //Check if the number is less than 2
    if (num < 2) return false;

    //Check for factors from 2 to the square root of num
    for (int i = 2; i*i <= num; i++){
        if (num % i == 0) return false;
    }
    return true;
}
int power(int factor, int &num){
    //Declare variables
    int count = 0;

    //Count how many times the factor divides the number
    while(num % factor == 0){
        num /= factor;
        count++;
    }
    return count;
}
int nPrimes(int num){
    int count = 0;
    for (int i = 2; i <= num; i++){
        if (isPrime(i)){
            if (num % i == 0){
                count++;
                while (num % i == 0){
                    num /= i;
                }
            }
        }
    }
    return count;
}
void cleanUp(Primes *primeFactors){
    delete[] primeFactors->pStrAry;
    delete primeFactors;
}
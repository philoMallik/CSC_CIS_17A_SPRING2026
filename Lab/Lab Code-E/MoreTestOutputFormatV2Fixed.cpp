/* 
 * File:
 * Author: Philopatair Mallik
 * Date: 1/15/2026
 * Purpose: Outputing  numbers in specific format using iomanip
 * Version:
 */

//System Libraries - Post Here
#include <iostream>
//Library for our functions utilized in this question.
#include <iomanip>
using namespace std;

//User Libraries - Post Here

//Global Constants - Post Here
//Only Universal Physics/Math/Conversions found here
//No Global Variables
//Higher Dimension arrays requiring definition prior to prototype only.

//Function Prototypes - Post Here

//Execution Begins Here
int main(int argc, char** argv) {
    //Set random number seed here when needed
    
    //Declare variables or constants here
    //7 characters or less
    int num1 , num2, num3, num4;
    //Initialize or input data here
    cin >> num1;
    cin >> num2;
    cin >> num3;
    cin >> num4;
    //Display initial conditions, headings here
    
    //Process inputs  - map to outputs here
    
    //Format and display outputs here
    cout << setw(9) << num1 
         << setw(10) << fixed << setprecision(1) << showpoint << static_cast<float>(num1) 
         << setw(10) << fixed << setprecision(2) << showpoint << static_cast<float>(num1) << endl;
    cout << setw(9) << num2
         << setw(10) << fixed << setprecision(1) << showpoint << static_cast<float>(num2) 
         << setw(10) << fixed << setprecision(2) << showpoint << static_cast<float>(num2) << endl;
    cout << setw(9) << num3 
         << setw(10) << fixed << setprecision(1) << showpoint << static_cast<float>(num3) 
         << setw(10) << fixed << setprecision(2) << showpoint << static_cast<float>(num3) << endl;
    cout << setw(9) << num4 
         << setw(10) << fixed << setprecision(1) << showpoint << static_cast<float>(num4) 
         << setw(10) << fixed << setprecision(2) << showpoint << static_cast<float>(num4);
    //Clean up allocated memory here
    
    //Exit stage left
    return 0;
}
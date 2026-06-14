/*
Author: Philopatair Mallik
Date: 01/26/2026
purpose: C++ Menu Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //Format Library
using namespace std;

//User libraries
#include "Prob1Random.h"
#include "Prob2Sort.h"
#include "Prob3Table.h"
#include "Prob3TableInherited.h"
#include "Prob4SavingAccount.h"
#include "Prob5Employee.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void problem1();
void problem2();
void problem3();
void problem4();
void problem5();
void problem6();
//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    unsigned short choose;
    unsigned short problemCount;
    //Initialize Variables
    problemCount = 6;
    do
    {
        cout << "This is a Menu program" << endl;
        cout << "Type 1  for problem X1" << endl;
        cout << "Type 2  for problem x2" << endl;
        cout << "Type 3  for problem x3" << endl;
        cout << "Type 4  for problem x4" << endl;
        cout << "Type 5  for problem x5" << endl;
        cout << "Type 6  for problem x6" << endl;
        cout << "Type anything else to exit" << endl;
        cin >> choose;

        //Mapping Process -> Inputs to Outputs
        switch (choose)
        {
            case  1:
            {
                problem1();
                break;
            }
            case  2:
            {
                problem2();
                break;
            }
            case  3:
            {
                problem3();
                break;
            }
            case  4:
            {
                problem4();
                break;
            }
            case  5:
            {
                problem5();
                break;
            }
            case  6:
            {
                problem6();
                break;
            }
            default: cout << "You have choosen to exit" << endl;
        }

    } while (choose >= 1 && choose <= problemCount);
    


    //Display Inputs/Outputs

    //Exit the program
    return 0;
};
void problem1(){
    cout << endl;
    //Driver program to return a random sequence
    char n=5;
    char rndseq[]={19,34,57,79,126};
    int ntimes=100000;
    Prob1Random a(n,rndseq);
    for(int i=1;i<=ntimes;i++){
    a.randFromSet();
    }
    int *x=a.getFreq();
    char *y=a.getSet();
    for(int i=0;i<n;i++){
    cout<<setw(3)<<int(y[i])<<" occurred "<<x[i]<<" times"<<endl;
    }
    cout<<endl<<"The total number of random numbers is "<<a.getNumRand()<<endl;
    cout << endl;

}
void problem2(){
    cout << endl;
    cout<<"The start of Problem 2, the sorting problem"<<endl;
    Prob2Sort<char> rc;
    bool ascending=true;

    //Getting the array from the file
    ifstream infile;
    infile.open("Problem2.txt",ios::in);
    char *ch2=new char[10*16];
    char *ch2p=ch2;
    while(infile.get(*ch2)){
        cout<<*ch2;ch2++;
    }
    infile.close();
    cout<<endl;

    //sorting the array
    cout<<"Sorting on which column"<<endl;
    int column;
    cin>>column;
    char *zc=rc.sortArray(ch2p,10,16,column,ascending);
    for(int i=0;i<10;i++){
        for(int j=0;j<16;j++){
        cout<<zc[i*16+j];
        }
    }
    delete []zc;
    cout<<endl;
}
void problem3(){
    cout << endl;
    cout<<"Entering problem number 3"<<endl;
    int rows=5;
    int cols=6;
    Prob3TableInherited<int> tab("Problem3.txt",rows,cols);
    const int *naugT=tab.getTable();

    //Display array without sums
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            cout<<naugT[i*cols+j]<<" ";
        }
        cout<<endl;
    }
    cout<<endl;

    //Display array with sums
    const int *augT=tab.getAugTable();
    for(int i=0;i<=rows;i++){
        for(int j=0;j<=cols;j++){
            cout<<augT[i*(cols+1)+j]<<" ";
        }
        cout<<endl;
    }
}
void problem4(){
    cout << endl;
    Prob4SavingAccount mine(-300);
    for(int i=1;i<=10;i++){
        mine.Transaction((float)(rand()%500)*(rand()%3-1)); 
    }
    mine.toString();
    cout<<"Balance after 7 years given 10% interest = "
        <<mine.Total((float)(0.10),7)<<endl;
    cout<<"Balance after 7 years given 10% interest = "
        <<mine.TotalRecursive((float)(0.10),7)
        <<" Recursive Calculation "<<endl;
    cout << endl;
}
void problem5(){
    cout << endl;
    Prob5Employee Mark("Mark","Boss",215.50);
    Mark.setHoursWorked(-3);
    Mark.toString();
    Mark.CalculatePay(Mark.setHourlyRate(20.0),Mark.setHoursWorked(25));
    Mark.toString();
    Mark.CalculatePay(Mark.setHourlyRate(40.0),Mark.setHoursWorked(25));
    Mark.toString();
    Mark.CalculatePay(Mark.setHourlyRate(60.0),Mark.setHoursWorked(25));
    Mark.toString();
    Prob5Employee Mary("Mary","VP",50.0);
    Mary.toString();
    Mary.CalculatePay(Mary.setHourlyRate(50.0),Mary.setHoursWorked(40));
    Mary.toString();
    Mary.CalculatePay(Mary.setHourlyRate(50.0),Mary.setHoursWorked(50));
    Mary.toString();
    Mary.CalculatePay(Mary.setHourlyRate(50.0),Mary.setHoursWorked(60));
    Mary.toString();
    cout << endl;
}
void problem6(){
    cout << endl;
    float n1,n2,n3;
    string bin1,bin2,bin3;
    string oct1,oct2,oct3;
    string hex1,hex2,hex3;
    string NASABin1,NASABin2,NASABin3;
    string NASAHex1,NASAHex2,NASAHex3;
    string  IEEEBin1,IEEEBin2,IEEEBin3;
    string IEEEHex1,IEEEHex2,IEEEHex3;
    float n1_1Bshift, n2_1Bshift, n3_1Bshift;
    float n1_2Bshift, n2_2Bshift, n3_2Bshift;
    float n1_3Bshift, n2_3Bshift, n3_3Bshift;


    //Initialize Variables
    n1 = 5.75;
    bin1 = "0101.11";
    oct1 = "5.6";
    hex1 = "5.C";
    NASABin1 = "01011100000000000000000000000011";
    NASAHex1 = "5C000003";
    IEEEBin1 = "01000000101110011001100110011010";
    IEEEHex1 = "40B33333";
    n1_1Bshift = 0.5*n1;
    n1_2Bshift = 0.25*n1;
    n1_3Bshift = 0.125*n1;



    n2 = 0.9;
    bin2 = "0.1110011001100110011001100110011";
    oct2 = "0.7\033[1m1463\033[0m";
    hex2 = "0.E6666666";
    NASABin2 = "00111111011001100110011001100110";
    NASAHex2 = "3F\033[1m6\033[0m";
    IEEEBin2 = "00111111011001100110011001100110";
    IEEEHex2 = "3F\033[1m6\033[0m";
    n2_1Bshift = 0.5*n2;
    n2_2Bshift = 0.25*n2;
    n2_3Bshift = 0.125*n2;

    n3 = 99.7;
    bin3 = "01100011.10110011001100110011001100110011";
    oct3 = "143.5\033[1m4631\033[0m";
    hex3 = "63.B\033[1m3\033[0m";
    NASABin3 = "01100011101100110011001100000111";
    NASAHex3 = "63B33307";
    IEEEBin3 = "01000010110001110110011001100110";
    IEEEHex3 = "42C76666";
    n3_1Bshift = 0.5*n3;
    n3_2Bshift = 0.25*n3;
    n3_3Bshift = 0.125*n3;

    //Mapping Process -> Inputs to Outputs


    //Display Inputs/Outputs
    cout << "1. " << setw(5) << n1 << endl;
    cout << "   " << "binary: " << bin1 << endl;
    cout << "   " << "octal: " << oct1 << endl;
    cout << "   " << "hexadecimal: " << hex1 << endl;
    cout << "   " << "NASA binary: " << NASABin1 << endl;
    cout << "   " << "NASA hexadecimal: " << NASAHex1 << endl;
    cout << "   " << "IEEE binary: " << IEEEBin1 << endl;
    cout << "   " << "IEEE hexadecimal: " << IEEEHex1 << endl;
    cout << "   " << "1 bit shift: " << setw(5) << n1_1Bshift << endl;
    cout << "   " << "2 bit shift: " << setw(5) << n1_2Bshift << endl;
    cout << "   " << "3 bit shift: " << setw(5) << n1_3Bshift << endl;

    cout << "2. " << setw(5) << n2 << endl;
    cout << "   " << "binary: " << bin2 << endl;
    cout << "   " << "octal: " << oct2 << endl;
    cout << "   " << "hexadecimal: " << hex2 << endl;
    cout << "   " << "NASA binary: " << NASABin2 << endl;
    cout << "   " << "NASA hexadecimal: " << NASAHex2 << endl;
    cout << "   " << "IEEE binary: " << IEEEBin2 << endl;
    cout << "   " << "IEEE hexadecimal: " << IEEEHex2 << endl;
    cout << "   " << "1 bit shift: " << setw(5) << n2_1Bshift << endl;
    cout << "   " << "2 bit shift: " << setw(5) << n2_2Bshift << endl;
    cout << "   " << "3 bit shift: " << setw(5) << n2_3Bshift << endl;

    cout << "3. " << setw(5) << n3 << endl;
    cout << "   " << "binary: " << bin3 << endl;
    cout << "   " << "octal: " << oct3 << endl;
    cout << "   " << "hexadecimal: " << hex3 << endl;
    cout << "   " << "NASA binary: " << NASABin3 << endl;
    cout << "   " << "NASA hexadecimal: " << NASAHex3 << endl;
    cout << "   " << "IEEE binary: " << IEEEBin3 << endl;
    cout << "   " << "IEEE hexadecimal: " << IEEEHex3 << endl;
    cout << "   " << "1 bit shift: " << setw(5) << n3_1Bshift << endl;
    cout << "   " << "2 bit shift: " << setw(5) << n3_2Bshift << endl;
    cout << "   " << "3 bit shift: " << setw(5) << n3_3Bshift << endl;
}

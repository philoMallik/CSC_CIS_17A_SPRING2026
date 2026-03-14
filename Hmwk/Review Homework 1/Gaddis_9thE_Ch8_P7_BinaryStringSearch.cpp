/*
Author: Philopatair Mallik
Date: 03/13/2026
purpose: Binary string search
    a program that search an array of strings using binary search and selection sort
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
int binarySrch(string [],int,string);
void selSrt(string [],int [],int);
//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    const int NUM_NAMES = 20;
    string names[NUM_NAMES] = {"Collins, Bill", "Smith, Bart", "Allen, Jim",
                               "Griffin, Jim", "Stamey, Marty", "Rose, Geri",
                               "Taylor, Terri", "Johnson, Jill",
                               "Allison, Jeff", "Looney, Joe", "Wolfe, Bill",
                               "James, Jean", "Weaver, Jim", "Pore, Bob",
                               "Rutherford, Greg", "Javens, Renee",
                               "Harrison, Rose", "Setzer, Cathy",
                               "Pike, Gordon", "Holland, Beth" };
    string name;
    int index, indArr[NUM_NAMES];
    //Initialize Variables
    cout<<"Enter a name to search for (Last, First): ";
    getline(cin,name);
    for(int i=0;i<NUM_NAMES;i++){
        indArr[i]=i+1;
    }
    //Mapping Process -> Inputs to Outputs
    selSrt(names,indArr,NUM_NAMES);
    index=binarySrch(names,NUM_NAMES,name);
    
    //Display Inputs/Outputs
    if(index<0) cout<<"The name was not found."<<endl;
    else cout<<"The name was found at index "<<indArr[index]<<"."<<endl;

    //Exit the program
    return 0;
};
void selSrt(string arry[],int ind[],int size){
    int minIndx;
    string minVal,temp;
    int tempInd;
    for(int i=0;i<(size-1);i++){
        minIndx=i;
        minVal=arry[i];
        for(int j=i+1;j<size;j++){
            if(arry[j]<minVal){
                minVal=arry[j];
                minIndx=j;
            }
        }
        temp=arry[minIndx];
        tempInd=ind[minIndx];
        arry[minIndx]=arry[i];
        ind[minIndx]=ind[i];
        arry[i]=temp;
        ind[i]=tempInd;
    }
}
int binarySrch(string arry[],int size,string name){
    int strtInd=0,
        endInd=size-1,
        midInd,
        indx;
    while(strtInd<=endInd){
        midInd=(strtInd+endInd)/2;
        if(name==arry[midInd]){
            indx=midInd;
            return indx;
        }
        else if (name<arry[midInd]) endInd=midInd-1;
        else strtInd=midInd+1;
    }
    return -1;
}
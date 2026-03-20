/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
int *getData(int &);//Read the array
int *augment(const int *,int);//Augment and copy the original array
void prntAry(const int *,int);//Print the array

//Execution begins here
int main(int argv, char **argc)
{
    //Declare variables and fill
    int *arr,arrSize;

    //Input the number of unique numbers
    //and size of the array
    arr=getData(arrSize);
    
    //Print the the initial array
    prntAry(arr,arrSize);
    cout<<endl;

    //Calculate the augmented array
    int* augArr = new int[arrSize];
    augArr=augment(arr,arrSize);

    //print the augmented array
    prntAry(augArr,arrSize+1);

    //Delete allocated memory
    delete []arr;
    delete []augArr;

    //Exit stage right
    return 0;
};
int *getData(int &arrSize){
    cin>>arrSize;
    int *arr = new int[arrSize];
    for(int i=0;i<arrSize;i++){
        cin>>arr[i];
    }
    return arr;
}
void prntAry(const int *arr,int arrSize){
    cout<<arr[0];
    for(int i=1;i<arrSize;i++){
        cout<<" "<<arr[i];
    }
}
int *augment(const int *arr,int arrSize){
    int *augArr = new int[arrSize+1];
    augArr[0]=0;
    for(int i=1;i<arrSize+1;i++){
        augArr[i]=arr[i-1];
    }
    return augArr;
}

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
int *getData(int &);             //Return the array size and the array from the inputs
int *sumAry(const int *,int);    //Return the array with successive sums
void prntAry(const int *,int);   //Print the array

//Execution begins here
int main(int argv, char **argc)
{
    //Declare variables and fill
    int *arr,
        arrSize;
    
    //Input the number of unique numbers
    //and size of the array
    arr=getData(arrSize);
    
    //Print the the initial array
    prntAry(arr,arrSize);
    cout<<endl;
    
    //calculate the sum array
    int* sumArr = new int[arrSize];
    sumArr=sumAry(arr,arrSize);

    //print the sum array
    prntAry(sumArr,arrSize);

    //Delete allocated memory
    delete []arr;
    delete []sumArr;

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
int *sumAry(const int *arr,int arrSize){
    int *sumArr=new int[arrSize];
    for(int i=0;i<arrSize;i++){
        sumArr[i]=arr[i];
        for(int j=0;j<i;j++){
            sumArr[i]+=arr[j];
        }
    }
    return sumArr;
}
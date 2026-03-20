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
int *getData(int &);           //Fill the array
int *sort(const int *,int);     //Sort smallest to largest
int *reverse(const int *,int); //Sort in reverse order
void prntDat(const int *,int); //Print the array
void swap(int *,int *);     //Swap

//Execution begins here
int main(int argv, char **argc)
{
    //Declare variables and fill
    int *arr,
        arrSize;
    
    //Input the number of unique numbers
    //and size of the array
    arr=getData(arrSize);
    
    //sort the array
    int* srtArr = new int[arrSize];
    srtArr=sort(arr,arrSize);

    //Print the sorted array
    prntDat(srtArr,arrSize);
    cout<<endl;
    
    //reverse the array
    int* rvrsArr = new int[arrSize];
    rvrsArr=reverse(srtArr,arrSize);

    //print the reversed array
    prntDat(rvrsArr,arrSize);

    //Delete allocated memory
    delete []arr;
    delete []srtArr;
    delete []rvrsArr;
    
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
void prntDat(const int *arr,int arrSize){
    cout<<arr[0];
    for(int i=1;i<arrSize;i++){
        cout<<" "<<arr[i];
    }
}
int *reverse(const int *arr,int arrSize){
    int* rvrsArr= new int[arrSize];
    for(int i=0;i<arrSize;i++){
        rvrsArr[i]=arr[arrSize-1-i];
    }
    return rvrsArr;
}
int *sort(const int *arr,int arrSize){
    int* srtArr= new int[arrSize];
    for(int i=0;i<arrSize;i++){
        srtArr[i]=arr[i];
    }
    for(int i=0;i<arrSize-1;i++){
        for(int j=i+1;j<arrSize;j++){
            if(*(srtArr+i)>*(srtArr+j))
                swap(srtArr+i,srtArr+j);
        }
    }
    return srtArr;
}
void swap(int *a,int *b){
    //Swap in place
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}
/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <iomanip>    //output format library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
int *getData(int &);         //Return the array size and the array
void prntDat(int *,int);    //Print the integer array
float *median(int *,int);  //Fill the median Array with the Float array size, the median, and the integer array data
void prntMed(float *);     //Print the median Array
void swap(int *,int *);     //Swap
void minPos(int *,int,int); //Find min Position
void mrkSort(int *,int);    //Mark Sort

//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    int *arr,
        arrSize;
    //Initialize Variables
    arr=getData(arrSize);

    //Mapping Process -> Inputs to Outputs
    //Allocate the median array and fill it
     float *medArr=median(arr,arrSize);

    //Display Inputs/Outputs
    prntDat(arr,arrSize);
    prntMed(medArr);

    //Delete allocated memory
    delete []arr;
    delete []medArr;

    //Exit the program
    return 0;
};
int *getData(int &arrSize){
    cin>>arrSize;
    int arr[arrSize];
    for(int i=0;i<arrSize;i++){
        cin>>arr[i];
    }
    return arr;
}
void prntDat(int *arr,int arrSize){
    cout<<arr[0];
    for(int i=1;i<arrSize;i++){
        cout<<" "<<arr[i];
    }
    cout<<endl;
}
float *median(int *arr,int arrSize){
    float med;
    int index;
    mrkSort(arr,arrSize);
    if(arrSize%2==0){
        index=arrSize/2;
        med=(arr[index]+arr[index+1])/2;
    }
    else{
        index=(arrSize+1)/2;
        med=arr[index];
    }

    float* medArr=new float[arrSize+2];
    medArr[0]=arrSize;
    medArr[1]=med;
    for(int i=0;i<arrSize;i++){
        medArr[i+2]=arr[i];
    }
    return medArr;
}
void prntMed(float *medArr){
    cout<<medArr[0];
    for(int i=1;i<medArr[0];i++){
        cout<<" "<<fixed<<setprecision(2)<<medArr[i];
    }
}
void mrkSort(int *array,int n){
    for(int i=0;i<n-1;i++){
        minPos(array,n,i);
    }
}
void minPos(int *array,int n,int pos){
    for(int i=pos+1;i<n;i++){
        if(*(array+pos)>*(array+i))
            swap(array+pos,array+i);
    }
}
void swap(int *a,int *b){
    //Swap in place
    *a=*a^*b;
    *b=*a^*b;
    *a=*a^*b;
}
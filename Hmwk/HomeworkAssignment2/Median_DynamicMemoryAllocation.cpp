/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
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
    //Declare variables and fill
    int *arr,
        arrSize;
    
    //Input the number of unique numbers
    //and size of the array
    arr=getData(arrSize);
    
    //Calculate the mode array
    float *medArr=median(arr,arrSize);
    
    //Print the initial array
    prntDat(arr,arrSize);
    
    //Print the modal information of the array
    prntMed(medArr);
    
    //Delete allocated memory
    delete []arr;
    delete []medArr;
    
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
    int* srtArr = new int[arrSize];
    for(int i=0;i<arrSize;i++){
        srtArr[i]=arr[i];
    }
    mrkSort(srtArr,arrSize);
    if(arrSize%2==0){
        index=arrSize/2;
        med=(srtArr[index-1]+srtArr[index])/2.0f;
    }
    else{
        index=(arrSize+1)/2;
        med=srtArr[index-1];
    }
    arrSize+=2;
    float* medArr=new float[arrSize];
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
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
int **getData(int &,int &);//Get the Matrix Data
void printDat(const int * const *,int,int);//Print the Matrix
int **augment(const int * const *,int,int);//Augment the original array
void destroy(int **,int);//Destroy the Matrix, i.e., reallocate memory

//Execution begins here
int main(int argv, char **argc)
{    
    //Declare variables and fill
    int **arr,rows,cols;

    //Input the number of unique numbers
    //and size of the array
    arr=getData(rows,cols);
    
    //Print the the initial array
    printDat(arr,rows,cols);
    cout<<endl;

    //Calculate the augmented array
    int **augArr=augment(arr,rows,cols);

    //print the augmented array
    printDat(augArr,rows+1,cols+1);

    //Delete allocated memory
    destroy(arr,rows);
    destroy(augArr,rows+1);

    //Exit stage right
    return 0;
};
int **getData(int &rows,int &cols){
    cin>>rows>>cols;
    int **arr = new int*[rows];
    for(int i=0;i<rows;i++){
        arr[i] = new int[cols];
        for(int j=0;j<cols;j++){
            cin>>arr[i][j];
        }
    }
    return arr;
}
void printDat(const int* const *arr,int rows,int cols){
    for(int i=0;i<rows;i++){
        cout<<arr[i][0];
        for(int j=1;j<cols;j++){
            cout<<" "<<arr[i][j];
        }
        if (i<rows-1) cout<<endl;
    }
}
int **augment(const int * const *arr,int rows,int cols){
    rows++;
    cols++;
    int **augArr = new int*[rows];
    for(int i=0;i<rows;i++){
        augArr[i] = new int[cols];
        for(int j=0;j<cols;j++){
            if(i==0||j==0)augArr[i][j]=0;
            else augArr[i][j]=arr[i-1][j-1];
        }
    }
    return augArr;
}
void destroy(int **arr,int rows){
    for(int i=0;i<rows;i++){
        delete []arr[i];
    }
    delete []arr;
}
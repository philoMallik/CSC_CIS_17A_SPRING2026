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
int **getData(int &,int &);               //Return the 2-D array and its size.
void prntDat(const int* const *,int,int); //Print the 2-D Array
void destroy(int **,int,int);             //Deallocate memory
int sum(const int * const *, int,int);    //Return the Sum

//Execution begins here
int main(int argv, char **argc)
{
    //Declare variables and fill
    int **arr,
        rows,cols;
    
    //Input the number of unique numbers
    //and size of the array
    arr=getData(rows,cols);
    
    //Print the the initial array
    prntDat(arr,rows,cols);
    
    //calculate and print the sum
    cout<< sum(arr,rows,cols);

    //Delete allocated memory
    destroy(arr,rows,cols);

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
void prntDat(const int* const *arr,int rows,int cols){
    for(int i=0;i<rows;i++){
        cout<<arr[i][0];
        for(int j=1;j<cols;j++){
            cout<<" "<<arr[i][j];
        }
        cout<<endl;
    }
}
int sum(const int * const * arr, int rows,int cols){
    int sum=0;
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            sum+=arr[i][j];
        }
    }
    return sum;
}
void destroy(int **arr,int rows,int cols){
    for(int i=0;i<rows;i++){
        delete []arr[i];
    }
    delete []arr;
}
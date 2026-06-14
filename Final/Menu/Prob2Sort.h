/*
Filename:  Prob2Sort.h
Author:    Philopatair Mallik
Date:      00/00/2026
Purpose:   class Specification
*/

#ifndef PROB2SORT_H
#define PROB2SORT_H

//System libraries
#include  <iostream>
using namespace std;

template <class T>
class Prob2Sort;  //Forward declaration

template <class T>
class Prob2Sort{
  private:
    //Private variables defined here
    int *index; //Index that is utilized

  public:
    //constructors
    Prob2Sort(){index=NULL;}

    //Destructor
    ~Prob2Sort(){delete []index;}

    //Accessors
    
    //Mutators

    //Operator overloads

    //Member functions
    T * sortArray(T*,int,bool);                 //Sorts a single column array
    T * sortArray(T*,int,int,int,bool);         //Sorts a 2 dimensional array 
                                                //represented as a 1 dim array

};

template <class T>
T *Prob2Sort<T>::sortArray(T *a,int n,bool ascending){
  int minIndx;
  T minVal,temp;
  if (ascending){
    for(int i=0;i<(n-1);i++){
      minIndx=i;    
      minVal=a[i];
      for(int j=i+1;j<n;j++){
        if(a[j]<minVal){
          minVal=a[j];
          minIndx=j;
        }
      }
      temp=a[minIndx];
      a[minIndx]=a[i];
      a[i]=temp;
    }
  }
  else{
    for(int i=0;i<(n-1);i++){
      minIndx=i;
      minVal=a[i];
      for(int j=i+1;j<n;j++){
        if(a[j]>minVal){
          minVal=a[j];
          minIndx=j;
        }
      }
      temp=a[minIndx];
      a[minIndx]=a[i];
      a[i]=temp;
    }
  }
  return a;
}

template <class T>
T *Prob2Sort<T>::sortArray(T *a,int rows,int cols,int column,bool ascending){
    int minIndx;
    T minVal, temp;
    column--; //To adjust for 0 based indexing 
    cout <<endl;
    if (ascending){
        for(int i=0;i<(rows-1);i++){
            minIndx=i;
            minVal=a[i*cols+column];
            for(int j=i+1;j<rows;j++){
                if(a[j*cols+column]<minVal){
                    minVal=a[j*cols+column];
                    minIndx=j;
                }
            }
            for(int k=0;k<cols-1;k++){
                temp=a[minIndx*cols+k];
                a[minIndx*cols+k]=a[i*cols+k];
                a[i*cols+k]=temp;
            }
        }
    }
    else{
        for(int i=0;i<(rows-1);i++){
            minIndx=i;
            minVal=a[i*cols+column];
            for(int j=i+1;j<rows;j++){
                if(a[j*cols+column]>minVal){
                    minVal=a[j*cols+column];
                    minIndx=j;
                }
            }
            for(int k=0;k<cols-1;k++){
                temp=a[minIndx*cols+k];
                a[minIndx*cols+k]=a[i*cols+k];
                a[i*cols+k]=temp;
            }
        }
    }
    return a;
}

#endif  // PROB2SORT_H
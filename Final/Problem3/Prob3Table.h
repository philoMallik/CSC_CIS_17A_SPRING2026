/*
Filename:  Prob3Table.h
Author:    Philopatair Mallik
Date:      06/09/2026
Purpose:   class Specification
*/

#ifndef PROB3TABLE_H
#define PROB3TABLE_H

//System libraries
#include  <iostream>
#include  <fstream>
using namespace std;


template<class T>
class Prob3Table{
    protected:
        int rows; //Number of rows in the table
        int cols; //Number of cols in the table
        T *rowSum; //RowSum array
        T *colSum; //ColSum array
        T *table; //Table array
        T grandTotal; //Grand total
        void calcTable(void); //Calculate all the sums

    public:
        Prob3Table(const char *,int,int); //Constructor then Destructor
        ~Prob3Table(){delete [] table;delete [] rowSum;delete [] colSum;};
        const T *getTable(void){return table;};
        const T *getRowSum(void){return rowSum;};
        const T *getColSum(void){return colSum;};
        T getGrandTotal(void){return grandTotal;};
};

template<class T>
Prob3Table<T>::Prob3Table(const char *file,int rows,int cols){
    //Initializing variables
    this->rows=rows;
    this->cols=cols;

    //Allocate memory for the table and sum arrays
    table=new T[rows*cols];
    rowSum=new T[rows];
    colSum=new T[cols];

    //Pre-initialize the sum arrays and grand total
    grandTotal=0;
    for(int i=0;i<rows;i++){
        rowSum[i]=0;
    }
    for(int j=0;j<cols;j++){
        colSum[j]=0;
    }

    //Read in the file and populate the table
    ifstream in(file);
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            in>>table[i*cols+j];
        }
    }
    in.close();
    calcTable();
}

template<class T>
void Prob3Table<T>::calcTable(void){
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            rowSum[i]+=table[i*cols+j];
            colSum[j]+=table[i*cols+j];
            grandTotal+=table[i*cols+j];
        }
    }
}

#endif  // PROB3TABLE_H
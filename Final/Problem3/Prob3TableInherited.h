/*
Filename:  Prob3TableInherited.h
Author:    Philopatair Mallik
Date:      06/09/2026
Purpose:   class Specification
*/

#ifndef PROB3TABLEINHERITED_H
#define PROB3TABLEINHERITED_H

//System libraries
#include  <iostream>
using namespace std;

//User libraries
#include "Prob3Table.h"

template<class T>
class Prob3TableInherited:public Prob3Table<T>{
    protected:
        T *augTable; //Augmented Table with sums
        
    public:
        Prob3TableInherited(const char *,int,int); //Constructor
        ~Prob3TableInherited(){delete [] augTable;}; //Destructor
        const T *getAugTable(void){return augTable;};
};

template<class T>
Prob3TableInherited<T>::Prob3TableInherited(const char *file,int rows,int cols):Prob3Table<T>(file,rows,cols){
    //Allocate memory for the augmented table
    augTable=new T[(rows+1)*(cols+1)];

    //Copy the original array row by row and add row sum at the end of each row
    for(int i=0;i<rows;i++){
        for(int j=0;j<cols;j++){
            augTable[i*(cols+1)+j]=this->table[i*cols+j];
        }
        augTable[i*(cols+1)+cols]=this->rowSum[i]; //Row sum at the end of each row
    }

    //Add the last row for column sums and grand total
    for(int j=0;j<cols;j++){
        augTable[rows*(cols+1)+j]=this->colSum[j]; //Column sum at the end of each column
    }
    augTable[rows*(cols+1)+cols]=this->grandTotal; //Grand total at the bottom right corner
}


#endif  // PROB3TABLEINHERITED_H
/*
Author : Philopatair Mallik
Date   : 1/30/2026 
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <iomanip>    //Format Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argc, char** argv) {
    //Declare all Variables Here
    bool x,y;
    
    //Display the Heading
    cout<<"X Y !X !Y X&&Y X||Y X^Y X^Y^X X^Y^Y !(X&&Y) !X||!Y "<<
          " !(X||Y) !X&&!Y"<<endl;
    
    while(cin >>x>>y){
        cout<<setw(1)<<(x?'T':'F')
            <<setw(2)<<(y?'T':'F')
            <<setw(3)<<(!x?'T':'F')
            <<setw(3)<<(!y?'T':'F')
            <<setw(4)<<(x&&y?'T':'F')
            <<setw(5)<<(x||y?'T':'F')
            <<setw(4)<<(x^y?'T':'F')
            <<setw(5)<<(x^y^x?'T':'F')
            <<setw(6)<<(x^y^y?'T':'F')
            <<setw(8)<<(!(x&&y)?'T':'F')
            <<setw(7)<<((!x)||(!y)?'T':'F')
            <<setw(9)<<(!(x||y)?'T':'F')
            <<setw(7)<<((!x)&&(!y)?'T':'F')
            <<endl;
    }
    cout<<endl;
    //Exit
    return 0;
}
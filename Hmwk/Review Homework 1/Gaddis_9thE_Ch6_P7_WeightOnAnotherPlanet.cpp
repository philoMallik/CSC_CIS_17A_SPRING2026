/*
Author: Philopatair Mallik
Date: 03/12/2026
purpose: Weight on another planet
    a program that calculates the weight of an object on aother planet given its weight on Earth
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions
const float venusW=0.905,
            marsW=0.3787,
            jupiterW=2.53;
//Function Prototype
float CalculateWeight(string,float);
//Execution begins here
int main(int argv, char **argc)
{
    //Set the Random Number seed
    srand(static_cast<unsigned int>(time(0)));

    //Declare Variables
    float weight,fnlWght;
    string planet;
    int choice;
    //Initialize Variables
    cout<<"Input the weight of the object: ";
    cin>>weight;
    cout<<"Which Planet do you want to calculate the weight on?"<<endl;
    cout<<"Enter 1 for Venus."<<endl
        <<"Enter 2 for Mars."<<endl
        <<"Enter 3 for Jupiter"<<endl;
    cin>>choice;
    //Mapping Process -> Inputs to Outputs
    switch(choice){
        case 1: planet="Venus";
        break;
        case 2: planet="Mars";
        break;
        case 3: planet="Jupiter";
        break;
    }
    fnlWght=CalculateWeight(planet,weight);
    //Display Inputs/Outputs
    cout <<"The weight of the object on "<<planet<<" is "<<fnlWght<<"."<<endl;
    //Exit the program
    return 0;
};
float CalculateWeight(string planet, float initWght){
    if(planet=="Venus")return (initWght*venusW);
    else if (planet=="Mars")return (initWght*marsW);
    else if (planet=="Jupiter")return (initWght*jupiterW);
    else return 0;
}
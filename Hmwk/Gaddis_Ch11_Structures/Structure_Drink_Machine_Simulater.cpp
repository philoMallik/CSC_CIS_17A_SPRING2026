/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <iomanip>    //Format Library
using namespace std;

//User libraries
struct DrinkMachine{
    string name;
    int cost; //cost in pennies
    int amt;  //amount of drink in the machine
};
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void displayMenu(DrinkMachine*,int); //Display the menu for the drink machine
int purchaseDrink(DrinkMachine*, int); //Allow the user to purchase a drink from the machine and update the amount of drinks in the machine

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    DrinkMachine drinks[5];
    int sale,
        totMoney=0;

    //Initialize Variables
    drinks[0] = {"Cola", 75, 20};
    drinks[1] = {"Root Beer", 75, 20};
    drinks[2] = {"Lemon-Lime", 75, 20};
    drinks[3] = {"Grape Soda", 80, 20};
    drinks[4] = {"Cream Soda", 80, 20};
    
    //Mapping Process & Display Inputs/Outputs
    do{
        displayMenu(drinks, 5); //Display the menu for the drink machine
        sale = purchaseDrink(drinks, 5); //Allow the user to purchase a drink from the machine and update the amount of drinks in the machine
        totMoney += sale;
    }while (sale!=0);
    
    //Display total money in the machine
    cout<<totMoney<<endl;

    //deallocate dynamically allocated memory
    delete[] drinks;

    //Exit the program
    return 0;
};
void displayMenu(DrinkMachine* drinks, int size){ //Display the menu for the drink machine
    for (int i = 0; i < size; i++){
        cout<<left<<setw(10)<<drinks[i].name<<right<<setw(3)<<drinks[i].cost<<setw(4)<<drinks[i].amt<<endl;
    }
    cout<<"Quit"<<endl;
}
int purchaseDrink(DrinkMachine* drinks, int size){ //Allow the user to purchase a drink from the machine and update the amount of drinks in the machine
    string choice;
    int money=0,
        index;
    int quit;
    getline(cin, choice);
    if (choice == "Quit") quit=0;
    else{
        do{
            cin>>money;
            cin.ignore();
        }while(money<0||money>100);
        if (choice == "Cola") index=0;
        else if (choice == "Root Beer") index=1;
        else if (choice == "Lemon-Lime") index=2;
        else if (choice == "Grape Soda") index=3;
        else if (choice == "Cream Soda") index=4; 
        if (drinks[index].amt > 0){
            drinks[index].amt--;
            cout<<money-drinks[index].cost<<endl;
        }
        else cout<<"Out of stock"<<endl;
        quit=drinks[index].cost;
    }
    return quit;
}
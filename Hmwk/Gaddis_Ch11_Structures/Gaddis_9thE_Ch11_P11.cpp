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
struct MonthlyBudget{
    float housing,
          utilities,
          householdExpenses,
          transportation,
          food,
          medical,
          insurance,
          entertainment,
          clothing,
          misc;
};

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
MonthlyBudget getMoneySpent(); //Get the budget for each category
void CalcBudget(MonthlyBudget, MonthlyBudget); //Calculate the total budget for the month and display the budget for each category and the total budget

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    MonthlyBudget Budget = {500, 150, 65, 50, 250, 30, 100, 150, 75, 50 }; //Structure variable to hold the budget for each category
    MonthlyBudget moneyspent;

    //Initialize Variables
    moneyspent = getMoneySpent(); //Get the budget for each category

    //Mapping Process & Display Inputs/Outputs
    CalcBudget(moneyspent, Budget); //Calculate the total budget for the month and display the budget for each category and the total budget
    
    //Exit the program
    return 0;
};
MonthlyBudget getMoneySpent(){ //Get the budget for each category
    MonthlyBudget moneyspent;
    cout<<"Enter housing cost for the month:$"<<endl;
    cin>>moneyspent.housing;
    cout<<"Enter utilities cost for the month:$"<<endl;
    cin>>moneyspent.utilities;
    cout<<"Enter household expenses cost for the month:$"<<endl;
    cin>>moneyspent.householdExpenses;
    cout<<"Enter transportation cost for the month:$"<<endl;
    cin>>moneyspent.transportation;
    cout<<"Enter food cost for the month:$"<<endl;
    cin>>moneyspent.food;
    cout<<"Enter medical cost for the month:$"<<endl;
    cin>>moneyspent.medical;
    cout<<"Enter insurance cost for the month:$"<<endl;
    cin>>moneyspent.insurance;
    cout<<"Enter entertainment cost for the month:$"<<endl;
    cin>>moneyspent.entertainment;
    cout<<"Enter clothing cost for the month:$"<<endl;
    cin>>moneyspent.clothing;
    cout<<"Enter miscellaneous cost for the month:$"<<endl;
    cin>>moneyspent.misc;

    return moneyspent; //Return the structure variable with the budget for each category
}
void CalcBudget(MonthlyBudget moneyspent, MonthlyBudget Budget){ //Calculate the total budget for the month and display the budget for each category and the total budget
    cout<<"Housing "<<(moneyspent.housing<Budget.housing?"Under":(moneyspent.housing>Budget.housing?"Over":"Even"))<<endl;
    cout<<"Utilities "<<(moneyspent.utilities<Budget.utilities?"Under":(moneyspent.utilities>Budget.utilities?"Over":"Even"))<<endl;
    cout<<"Household Expenses "<<(moneyspent.householdExpenses<Budget.householdExpenses?"Under":(moneyspent.householdExpenses>Budget.householdExpenses?"Over":"Even"))<<endl;
    cout<<"Transportation "<<(moneyspent.transportation<Budget.transportation?"Under":(moneyspent.transportation>Budget.transportation?"Over":"Even"))<<endl;
    cout<<"Food "<<(moneyspent.food<Budget.food?"Under":(moneyspent.food>Budget.food?"Over":"Even"))<<endl;
    cout<<"Medical "<<(moneyspent.medical<Budget.medical?"Under":(moneyspent.medical>Budget.medical?"Over":"Even"))<<endl;
    cout<<"Insurance "<<(moneyspent.insurance<Budget.insurance?"Under":(moneyspent.insurance>Budget.insurance?"Over":"Even"))<<endl;
    cout<<"Entertainment "<<(moneyspent.entertainment<Budget.entertainment?"Under":(moneyspent.entertainment>Budget.entertainment?"Over":"Even"))<<endl;
    cout<<"Clothing "<<(moneyspent.clothing<Budget.clothing?"Under":(moneyspent.clothing>Budget.clothing?"Over":"Even"))<<endl;
    cout<<"Miscellaneous "<<(moneyspent.misc<Budget.misc?"Under":(moneyspent.misc>Budget.misc?"Over":"Even"))<<endl;

    float totBudget=Budget.housing + Budget.utilities + Budget.householdExpenses + Budget.transportation + Budget.food + Budget.medical + Budget.insurance + Budget.entertainment + Budget.clothing + Budget.misc;
    float totMoneySpent=moneyspent.housing + moneyspent.utilities + moneyspent.householdExpenses + moneyspent.transportation + moneyspent.food + moneyspent.medical + moneyspent.insurance + moneyspent.entertainment + moneyspent.clothing + moneyspent.misc;
    cout<<"You were $";
    if(totMoneySpent<totBudget) cout<<fixed<<setprecision(2)<<(totBudget-totMoneySpent)<<" under budget";
    else if(totMoneySpent>totBudget) cout<<fixed<<setprecision(2)<<(totMoneySpent-totBudget)<<" over budget";
    else cout<<"on budget";
}
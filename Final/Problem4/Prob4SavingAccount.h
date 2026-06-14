/*
Filename:  Prob4SavingAccount.h
Author:    Philopatair Mallik
Date:      06/09/2026
Purpose:   class Specification
*/

#ifndef PROB4SAVINGACCOUNT_H
#define PROB4SAVINGACCOUNT_H

//System libraries
#include  <iostream>
using namespace std;

class Prob4SavingAccount;  //Forward declaration

class Prob4SavingAccount{
  public:
        Prob4SavingAccount(float); //Constructor
        void Transaction(float); //Procedure
        float Total(float=0,int=0); //Savings Procedure
        float TotalRecursive(float=0,int=0);
        void toString(); //Output Properties
    private:
        float Withdraw(float); //Utility Procedure
        float Deposit(float); //Utility Procedure
        float Balance; //Property
        int FreqWithDraw; //Property
        int FreqDeposit; //Property

};

#endif  // PROB4SAVINGACCOUNT_H
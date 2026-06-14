/* 
 * File:    Prob4SavingAccount.cpp
 * Author:  Philopatair Mallik
 * Date:    00/00/2026
 * Purpose: class implementation file
 */

//System libraries
#include <iostream>
#include <cmath>
using namespace std;

//User libraries
#include "Prob4SavingAccount.h"

    // Constructors
    Prob4SavingAccount::Prob4SavingAccount(float initialBalance){
        if (initialBalance<0){
            cout <<"Initial balance cannot be negative. Setting balance to 0."<<endl;
            Balance=0;
        }
        else{
            Balance=initialBalance;
        }
        FreqWithDraw=0;
        FreqDeposit=0;
    }
    //Accessors

    //Mutators

    //Operator overloads

    //Member functions
    void Prob4SavingAccount::Transaction(float amount){
        if(amount>0){
            Deposit(amount);
        }
        else{
            Withdraw(-amount);
        }
    }
    float Prob4SavingAccount::Deposit(float amount){
        Balance+=amount;
        FreqDeposit++;
        return Balance;
    }
    float Prob4SavingAccount::Withdraw(float amount){
        if (amount>Balance){
            cout <<"Withdraw not Allowed"<<endl;
            return Balance;
        }
        else{
            Balance-=amount;
            FreqWithDraw++;
            return Balance;
        }
    }

    void Prob4SavingAccount::toString(){
        cout <<"Balance="<<Balance<<endl;
        cout <<"Withdraws="<<FreqWithDraw<<endl;
        cout <<"Deposits="<<FreqDeposit<<endl;
    }

    float Prob4SavingAccount::Total(float Savint, int months){
        float total = Balance;
        for(int i=0;i<months;i++){
            total *= (1 + Savint);
        }
        return total;
    }

    float Prob4SavingAccount::TotalRecursive(float Savint, int months){
        if(months==0){
            return Balance;
        }
        return (TotalRecursive(Savint, months-1) * (1 + Savint));
    }

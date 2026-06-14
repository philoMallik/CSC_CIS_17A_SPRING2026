#ifndef CUSTOMER_H
#define CUSTOMER_H

struct Customer
{
    int accountNumber;    //Five digits only
    char name[50];
    char address[100];
    float initBal;        //Balance at the beginning of the month
    float *checks;       //Record all checks written by this customer this month
    int numChecks;       //Number of checks written
    float *deposits;     //Record all deposits credited to this customer’s account this month
    int numDeposits;     //Number of deposits credited
};

#endif /* CUSTOMER_H */
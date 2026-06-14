/*
Author: Philopatair Mallik
Date: 04/22/2026
purpose: Midterm Problem 7 - 
7. (10 points) Factor an input integer into it’s prime numbers. Create a structure to hold
the array of prime numbers. Any number between [2,65000] will be a valid number to
check for prime factors.
    struct Prime{
        unsigned char power; //Power associated with the prime number
        unsigned short prime;//Prime number factor
    };
    struct Primes{
        unsigned short n; //Number to factor into Primes
        unsigned char nPrimes; //Number of Primes
        Prime *pStrAry; //The Prime Structure Array
    };
Output the number and it’s primes i.e. 300 = 22 ∗ 31 ∗ 52
So create functions to calculate and print.
Primes *factor(int); //Factor the number into it’s Primes
void prtPrms(const Primes *); //Print the prime factors
I also used helper functions but the above 2 function are the only required.
bool isPrime(int); //Determine if the number is Prime
int power(int,int &); //What power is this factor and remove from n
int nPrimes(int); //How many Primes
void cleanUp(Primes *); //Clean it all up
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries
struct Prime{
    unsigned char power;        //Power associated with the prime number
    unsigned short prime;       //Prime number factor
};
struct Primes{
    unsigned short n;           //Number to factor into Primes
    unsigned char nPrimes;      //Number of Primes
    Prime *pStrAry;             //The Prime Structure Array
};

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
Primes *factor(int);            //Factor the number into it’s Primes
void prtPrms(const Primes *);   //Print the prime factors

bool isPrime(int);              //Determine if the number is Prime
int power(int,int &);           //What power is this factor and remove from n
int nPrimes(int);               //How many Primes
void cleanUp(Primes *);         //Clean it all up

//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    int num;

    //Initialize Variables
    cout << "This program factors an input integer into its prime numbers." << endl;
    cout << "Enter an integer between 2 and 65000: ";
    cin >> num;

    //Factor the number into its primes
    Primes *primeFactors = factor(num);

    //Print the prime factors
    prtPrms(primeFactors);

    //Clean up
    cleanUp(primeFactors);

    //Exit the program
    return 0;
};
Primes *factor(int num)
{
    //Declare variables
    int index = 0;
    int temp = num;

    Primes *primeFactors = new Primes;
    primeFactors->n = num;
    primeFactors->nPrimes = nPrimes(num);
    primeFactors->pStrAry = new Prime[primeFactors->nPrimes];

    //Factor the number into its primes
    for (int i = 2; i <= num; i++){
        if (isPrime(i)){
            if (temp % i == 0){
                primeFactors->pStrAry[index].prime = i;
                primeFactors->pStrAry[index].power = power(i, temp);
                index++;
            }
        }
    }

    //Return the prime factors
    return primeFactors;
}
void prtPrms(const Primes *primeFactors){
    cout << primeFactors->n << " = ";
    for (int i = 0; i < primeFactors->nPrimes; i++) {
        cout << primeFactors->pStrAry[i].prime << "^" << (int)primeFactors->pStrAry[i].power;
        if (i < primeFactors->nPrimes - 1) cout << " * ";
    }
    cout << endl;
}

bool isPrime(int num){
    //Check if the number is less than 2
    if (num < 2) return false;

    //Check for factors from 2 to the square root of num
    for (int i = 2; i*i <= num; i++){
        if (num % i == 0) return false;
    }
    return true;
}
int power(int factor, int &num){
    //Declare variables
    int count = 0;

    //Count how many times the factor divides the number
    while(num % factor == 0){
        num /= factor;
        count++;
    }
    return count;
}
int nPrimes(int num){
    int count = 0;
    for (int i = 2; i <= num; i++){
        if (isPrime(i)){
            if (num % i == 0){
                count++;
                while (num % i == 0){
                    num /= i;
                }
            }
        }
    }
    return count;
}
void cleanUp(Primes *primeFactors){
    delete[] primeFactors->pStrAry;
    delete primeFactors;
}
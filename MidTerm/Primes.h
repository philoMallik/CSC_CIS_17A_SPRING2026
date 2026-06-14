#ifndef PRIMES_H
#define PRIMES_H

#include "Prime.h"

struct Primes{
    unsigned short n;           //Number to factor into Primes
    unsigned char nPrimes;      //Number of Primes
    Prime *pStrAry;             //The Prime Structure Array
};

#endif /* PRIMES_H */
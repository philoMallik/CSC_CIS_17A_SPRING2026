/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose:  C++ Patient Class Implementation File 
*/

#include "Patient.h"
#include <iostream>
#include <cstring>
using namespace std;

#include <cstring>


Patient::Patient(char* fstnme, char* midnme, char* lstnme, char* strt, char* city, char* state, char* zip, char* phn, char* emenme, char* emephn) {
    setFstnme(fstnme);
    setMIdnme(midnme);
    setLstnme(lstnme);
    setStrt(strt);
    setCity(city);
    setState(state);
    setZip(zip);
    setPhn(phn);
    setEmeNme(emenme);
    setEmePhn(emephn);
}

void Patient::setFstnme(char* fstnme) {
    strncpy(Fstnme, fstnme, sizeof(Fstnme) - 1);
    Fstnme[sizeof(Fstnme) - 1] = '\0'; // Ensure null-termination
}
void Patient::setMIdnme(char* midnme) {
    strncpy(MIdnme, midnme, sizeof(MIdnme) - 1);
    MIdnme[sizeof(MIdnme) - 1] = '\0'; // Ensure null-termination
}
void Patient::setLstnme(char* lstnme) {
    strncpy(Lstnme, lstnme, sizeof(Lstnme) - 1);
    Lstnme[sizeof(Lstnme) - 1] = '\0'; // Ensure null-termination
}
void Patient::setStrt(char* strt) {
    strncpy(Strt, strt, sizeof(Strt) - 1);
    Strt[sizeof(Strt) - 1] = '\0'; // Ensure null-termination
}
void Patient::setCity(char* city) {
    strncpy(City, city, sizeof(City) - 1);
    City[sizeof(City) - 1] = '\0'; // Ensure null-termination
}
void Patient::setState(char* state) {
    strncpy(State, state, sizeof(State) - 1);
    State[sizeof(State) - 1] = '\0'; // Ensure null-termination
}
void Patient::setZip(char* zip) {
    strncpy(Zip, zip, sizeof(Zip) - 1);
    Zip[sizeof(Zip) - 1] = '\0'; // Ensure null-termination
}
void Patient::setPhn(char* phn) {
    strncpy(Phn, phn, sizeof(Phn) - 1);
    Phn[sizeof(Phn) - 1] = '\0'; // Ensure null-termination
}
void Patient::setEmeNme(char* emenme) {
    strncpy(EmeNme, emenme, sizeof(EmeNme) - 1);
    EmeNme[sizeof(EmeNme) - 1] = '\0'; // Ensure null-termination
}
void Patient::setEmePhn(char* emephn) {
    strncpy(EmePhn, emephn, sizeof(EmePhn) - 1);
    EmePhn[sizeof(EmePhn) - 1] = '\0'; // Ensure null-termination
}
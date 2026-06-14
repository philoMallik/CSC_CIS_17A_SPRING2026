/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: C++ Patient Class 
*/

#ifndef PATIENT_H
#define PATIENT_H

class Patient
{
    private:
        //Name
        char Fstnme[20]; // Patient's first name
        char MIdnme[20]; // Patient's middle name
        char Lstnme[20]; // Patient's last name
        //Address
        char Strt[20];   // Patient's address street        
        char City[20];  // Patient's address city
        char State[20]; // Patient's address state
        char Zip[20];   // Patient's address zip code
        //Phone Number
        char Phn[20];   // Patient's phone number
        //Emergency Contact
        char EmeNme[20]; // Patient's emergency contact name
        char EmePhn[20];   // Patient's emergency contact phone number
    public:
        // Constructor
        Patient(char*, char*, char*, char*, char*, char*, char*, char*, char*, char*); // Default constructor
        // Mutators
        void setFstnme(char*); // Set patient's first name
        void setMIdnme(char*); // Set patient's middle name
        void setLstnme(char*); // Set patient's last name
        void setStrt(char*);   // Set patient's address street
        void setCity(char*);   // Set patient's address city
        void setState(char*);  // Set patient's address state
        void setZip(char*);    // Set patient's address zip code
        void setPhn(char*);    // Set patient's phone number
        void setEmeNme(char*); // Set patient's emergency contact name
        void setEmePhn(char*); // Set patient's emergency contact phone number
        // Accessors
        char* getFstnme(); // Get patient's first name
        char* getMIdnme(); // Get patient's middle name
        char* getLstnme(); // Get patient's last name
        char* getStrt();   // Get patient's address street
        char* getCity();   // Get patient's address city
        char* getState();  // Get patient's address state
        char* getZip();    // Get patient's address zip code
        char* getPhn();    // Get patient's phone number
        char* getEmeNme(); // Get patient's emergency contact name
        char* getEmePhn(); // Get patient's emergency contact phone number
};

#endif // PATIENT_H
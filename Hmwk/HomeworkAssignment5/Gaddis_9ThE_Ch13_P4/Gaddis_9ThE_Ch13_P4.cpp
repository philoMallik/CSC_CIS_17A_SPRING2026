/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstring>    //String library
using namespace std;

//User libraries
#include "Patient.h"
#include "Procedure.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype

//Execution begins here
int main(int argv, char **argc){

    //Declare Variables
    char    fstnme[20] = "John",
            midnme[20] = "A.",
            lstnme[20] = "Doe",
            strt[20] = "123 Main St",
            city[20] = "Anytown",
            state[20] = "CA",
            zip[20] = "12345",
            phn[20] = "555-1234",
            emenme[20] = "Jane Doe",
            emephn[20] = "555-5678";
     char   prcNme[3][20],
            prcDte[3][20],
            docNme[3][20];
     float prcCst[3];


    //Initialize Variables
    cout << "This program will create a patient and three procedures." << endl;

     //Procedure 1
     strcpy(prcNme[0], "Physical Exam");
     strcpy(prcDte[0], "05/20/2026");
     strcpy(docNme[0], "Dr. Irvine");
     prcCst[0] = 250.00f;

     //Procedure 2
     strcpy(prcNme[1], "X-ray");
     strcpy(prcDte[1], "05/20/2026");
     strcpy(docNme[1], "Dr. Jamison");
     prcCst[1] = 500.00f;

     //Procedure 3
     strcpy(prcNme[2], "Blood Test");
     strcpy(prcDte[2], "05/20/2026");
     strcpy(docNme[2], "Dr. Smith");
     prcCst[2] = 200.00f;

    //Create Patient object
    Patient patient(fstnme, midnme, lstnme, strt, city, state, zip, phn, emenme, emephn);

    //Create Procedure objects
    Procedure procedure1(prcNme[0], prcDte[0], docNme[0], prcCst[0]);
    Procedure procedure2(prcNme[1], prcDte[1], docNme[1], prcCst[1]);
    Procedure procedure3(prcNme[2], prcDte[2], docNme[2], prcCst[2]);

    //Display Inputs/Outputs
    cout << "This Program will display the patient's information and the details of the procedures." << endl;
    cout << "Patient Information:" << endl;
    cout << "Name:    " << patient.getFstnme() << " " << patient.getMIdnme() << " " << patient.getLstnme() << endl;
    cout << "Address: " << patient.getStrt() << ", " << patient.getCity() << ", " << patient.getState() << " " << patient.getZip() << endl;
    cout << "Phone:   " << patient.getPhn() << endl;
    cout << "Emergency Contact: " << patient.getEmeNme() << " - " << patient.getEmePhn() << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Procedures:  " << endl;
    cout << "Procedure 1: " << procedure1.getPrcNme() << endl;
    cout << "Date:        " << procedure1.getPrcDte() << endl;
    cout << "Practioner:  " << procedure1.getDocNme() << endl;
    cout << "Charge:       $" << procedure1.getPrcCst() << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Procedure 2: " << procedure2.getPrcNme() << endl;
    cout << "Date:        " << procedure2.getPrcDte() << endl; 
    cout << "Practioner:  " << procedure2.getDocNme() << endl;
    cout << "Charge:       $" << procedure2.getPrcCst() << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Procedure 3: " << procedure3.getPrcNme() << endl;
    cout << "Date:        " << procedure3.getPrcDte() << endl;
    cout << "Practioner:  " << procedure3.getDocNme() << endl;
    cout << "Charge:       $" << procedure3.getPrcCst() << endl;
    cout << "----------------------------------------------" << endl;
    cout << "Total Charges: $" << procedure1.getPrcCst() + procedure2.getPrcCst() + procedure3.getPrcCst() << endl;
    cout << "----------------------------------------------" << endl;

    //Exit the program
    return 0;
};
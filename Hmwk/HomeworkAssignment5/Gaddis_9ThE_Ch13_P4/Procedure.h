/*
Author: Philopatair Mallik
Date: 05/20/2026
purpose: C++ Class Procedure 
*/

#ifndef PROCEDURE_H
#define PROCEDURE_H

class Procedure
{
    private:
        char  PrcNme[20]; // Procedure name
        char  PrcDte[20]; // Procedure date
        char  DocNme[20]; // Doctor name
        float PrcCst;   // Procedure cost
    public:
        // Constructor
        Procedure(char*, char*, char*, float); // Constructor
        // Mutators
        void  setPrcNme(char*); // Set procedure name
        void  setPrcDte(char*); // Set procedure date
        void  setDocNme(char*); // Set doctor name
        void  setPrcCst(float); // Set procedure cost
        // Accessors
        char* getPrcNme(); // Get procedure name
        char* getPrcDte(); // Get procedure date
        char* getDocNme(); // Get doctor name
        float getPrcCst(); // Get procedure cost

};

#endif // PROCEDURE_H
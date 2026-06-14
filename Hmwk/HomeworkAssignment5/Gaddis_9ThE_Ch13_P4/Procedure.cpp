/* 
 * File:    Procedure.cpp
 * Author:  Philopatair Mallik
 * Date:    05/20/2026
 * Purpose: Procedure class implementation file
 */

#include "Procedure.h"
#include <iostream>
#include <cstring>
using namespace std;   
    
    // Constructor
    Procedure::Procedure(char* prcNme, char* prcDte, char* docNme, float prcCst){
        strcpy(PrcNme, prcNme);
        strcpy(PrcDte, prcDte);
        strcpy(DocNme, docNme);
        PrcCst = prcCst;
    }
    // Mutators
    void Procedure::setPrcNme(char* prcNme){
        strcpy(PrcNme, prcNme);
    }
    void Procedure::setPrcDte(char* prcDte){
        strcpy(PrcDte, prcDte);
    }
    void Procedure::setDocNme(char* docNme){
        strcpy(DocNme, docNme);
    }
    void Procedure::setPrcCst(float prcCst){
        PrcCst = prcCst;
    }
    // Accessors
    char* Procedure::getPrcNme(){
        return PrcNme;
    }
    char* Procedure::getPrcDte(){
        return PrcDte;
    }
    char* Procedure::getDocNme(){
        return DocNme;
    }
    float Procedure::getPrcCst(){
        return PrcCst;
    }
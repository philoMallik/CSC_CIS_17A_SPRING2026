/*
Author: Philopatair Mallik
Date: 04/20/2026
purpose: Gaddis_9thE_Ch12_P13_InventoryProgram.cpp
*/

//system libraries
#include <iostream>   //Input/Output library
#include <cstdlib>    //Random Number Library 
#include <ctime>      //Time Library
#include <fstream>    //File Stream Library
using namespace std;

//User libraries
#include "Item.h"

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void addRecord(string);
void displayRecord(string);
void changeRecord(string);
    


//Execution begins here
int main(int argv, char **argc)
{
    //Declare Variables
    int choice;
    string fileName = "inventory.dat";

    // title and purpose of the program
    cout << "This program demonstrates how to use structures to store and display inventory data." << endl;

    do{
        //output the menu and get the user's choice
        cout << " Which of the following would you like to do?" << endl;
        cout << "1. Add new records to the file." << endl;
        cout << "2. Display any record in the file." << endl;
        cout << "3. Change any record in the file." << endl;
        cout << "4. Exit the program." << endl;
        cin>> choice;

        //Process the user's choice
        switch (choice)
        {
            case 1:
                cout<< "You chose to add new records to the file." << endl;
                    addRecord(fileName);
                break;
            case 2:
                cout<< "You chose to display any record in the file." << endl;
                    displayRecord(fileName);
                break;
            case 3:
                cout<< "You chose to change any record in the file." << endl;
                    changeRecord(fileName);
                break;
            case 4:
                cout<< "You chose to exit the program." << endl;
                break;
            default:
                cout<< "Invalid choice. Please choose a valid option from the menu." << endl;
        }
    }while (choice != 4);



    //Exit the program
    return 0;
}

void addRecord(string fileName){
    fstream out;
    out.open(fileName, ios::out | ios::app | ios::binary);
    Item item;
    char choice;
    do{
        //get the data for the structure from the user
        cout<< "Input the item description: ";
        cin.ignore();
        cin.getline(item.itemDescription, 50);
        cout<< "Input the quantity on hand: ";
        do{
            cin>> item.Quantity;
            if (item.Quantity < 0){
                cout<< "Quantity cannot be negative. Please enter a valid quantity: ";
            }
        } while (item.Quantity < 0);
        cout<< "Input the wholesale cost: ";
        do{
            cin>> item.WSCost;
            if (item.WSCost < 0){
                cout<< "Wholesale cost cannot be negative. Please enter a valid wholesale cost: ";
            }
        } while (item.WSCost < 0);
        cout<< "Input the retail cost: ";
        do{
            cin>> item.RTCost;
            if (item.RTCost < 0){
                cout<< "Retail cost cannot be negative. Please enter a valid retail cost: ";
            }
        } while (item.RTCost < 0);
        cout<< "Input the date added (day month year): ";
        do{
            cin>> item.DateAdded[0] >> item.DateAdded[1] >> item.DateAdded[2];
            if (item.DateAdded[0] < 1 || item.DateAdded[0] > 31 || item.DateAdded[1] < 1 || item.DateAdded[1] > 12 || item.DateAdded[2] < 1900){
                cout<< "Invalid date. Please enter a valid date (day month year): ";
            }
        } while (item.DateAdded[0] < 1 || item.DateAdded[0] > 31 || item.DateAdded[1] < 1 || item.DateAdded[1] > 12 || item.DateAdded[2] < 1900);

        //write the record to file
        out.write(reinterpret_cast<char*>(&item), sizeof(item));
        cout<< "Do you want to add another record? (Y/N): ";
        cin>> choice;
    } while (choice == 'Y' || choice == 'y');
    out.close();
}

void displayRecord(string fileName){
    fstream in;
    in.open(fileName, ios::in | ios::binary);
    int recordNum, count = 0;
    long cursor = 0L;
    Item *item = new Item;

    cout<< "Input the record number you want to display: ";
    cin>> recordNum;
    cursor = (recordNum - 1) * sizeof(Item);
    in.seekg(cursor, ios::beg);
    in.read(reinterpret_cast<char*>(item), sizeof(Item));

    cout<< "Item Description: " << item->itemDescription << endl;
    cout<< "Quantity on hand: " << item->Quantity << endl;
    cout<< "Wholesale cost: $" << item->WSCost << endl;
    cout<< "Retail cost: $" << item->RTCost << endl;
    cout<< "Date added: " << item->DateAdded[0] << "/" << item->DateAdded[1] << "/" << item->DateAdded[2] << endl;
    
    delete item;
    in.close();
}

void changeRecord(string fileName){
    fstream inout;
    inout.open(fileName, ios::in | ios::out | ios::binary);
    Item item;
    int recordNum, count = 0;
    cout<< "Input the record number you want to change: ";
    cin>> recordNum;
    while (inout.read(reinterpret_cast<char*>(&item), sizeof(item))){
        count++;
        if (count == recordNum){
            cout<< "Current item description: " << item.itemDescription << endl;
            cout<< "Current quantity on hand: " << item.Quantity << endl;
            cout<< "Current wholesale cost: $" << item.WSCost << endl;
            cout<< "Current retail cost: $" << item.RTCost << endl;
            cout<< "Current date added: " << item.DateAdded[0] << "/" << item.DateAdded[1] << "/" << item.DateAdded[2] << endl;

            //get the new data for the structure from the user
            cout<< "Input the new item description: ";
            cin.ignore();
            cin.getline(item.itemDescription, 50);
            cout<< "Input the new quantity on hand: ";
            do{
                cin>> item.Quantity;
                if (item.Quantity < 0){
                    cout<< "Quantity cannot be negative. Please enter a valid quantity: ";
                }
            } while (item.Quantity < 0);
            cout<< "Input the new wholesale cost: ";
            do{
                cin>> item.WSCost;
                if (item.WSCost < 0){
                    cout<< "Wholesale cost cannot be negative. Please enter a valid wholesale cost: ";
                }
            } while (item.WSCost < 0);
            cout<< "Input the new retail cost: ";
            do{
                cin>> item.RTCost;
                if (item.RTCost < 0){
                    cout<< "Retail cost cannot be negative. Please enter a valid retail cost: ";
                }
            } while (item.RTCost < 0);
            cout<< "Input the new date added (day month year): ";
            do{
                cin>> item.DateAdded[0] >> item.DateAdded[1] >> item.DateAdded[2];
                if (item.DateAdded[0] < 1 || item.DateAdded[0] > 31 || item.DateAdded[1] < 1 || item.DateAdded[1] > 12 || item.DateAdded[2] < 1900){
                    cout<< "Invalid date. Please enter a valid date (day month year): ";
                }
            } while (item.DateAdded[0] < 1 || item.DateAdded[0] > 31 || item.DateAdded[1] < 1 || item.DateAdded[1] > 12 || item.DateAdded[2] < 1900);
            //move the file pointer back to the beginning of the record
            inout.seekp(-static_cast<int>(sizeof(item)), ios::cur);
            //write the updated record to the file
            inout.write(reinterpret_cast<char*>(&item), sizeof(item));
            break;
        }
    }
    if (count < recordNum){
        cout<< "Record not found. Please enter a valid record number." << endl;
    }
    inout.close();
}

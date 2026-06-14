/*
Author: Philopatair Mallik
Date: 04/22/2026
purpose: Midterm Problem 4 - 
4. (10 points) A company wants to transmit data over the telephone, but they are con-
cerned that their phones may be tapped. All of their data is transmitted as four-digit
integers. However, they utilize the digits 0,1,2,3,4,5,6,7 only. They have asked you to
write a program that will encrypt their data so that it may be transmitted more se-
curely.Your application should read a four-digit integer with the numbers 0 to 7 entered
by the user in an input dialog and encrypt it as follows: Replace each digit by (the
sum of that digit plus 3 modulus 8. Then swap the first digit with the third, and swap
the second digit with the fourth. Then print the encrypted integer. Write a separate
application that inputs an encrypted four-digit integer and decrypts. If you encrypt a
number, you should be able to get the same number decrypted back when the user does
this. Note: sometimes errors occur and the digits 8, and 9 might appear. Detect this
condition and flag the error. Can’t read in numbers individually. All the digits must be
read with one cin statement.
*/

//system libraries
#include <iostream>   //Input/Output library
using namespace std;

//User libraries

//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
int encrypt(int, int, int, int);
int decrypt(int, int, int, int);
void swap(int &a, int &b);

//Execution begins here
int main(int argv, char **argc){
    //Declare Variables
    int num;
    int n4, n3, n2, n1;
    int choice = 0;
    int encryptedNum, decryptedNum;

    //Initialize Variables
    cout << "This program encrypts and decrypts four-digit integers using digits 0-7." << endl;
    do{
        cout << "Enter 1 to encrypt a number, 2 to decrypt a number or 3 to exit: ";
        cin >> choice;
        switch(choice){
            case 1: cout << "Enter a four-digit integer (digits 0-7 only): ";
                    cin >> num;

                    //Extract digits from the number
                    n4 = num%10,     
                    n3 = (num/10)%10,
                    n2 = (num/100)%10,    
                    n1 = (num/1000)%10;

                    //Check for invalid digits
                    if (n1 > 7 || n2 > 7 || n3 > 7 || n4 > 7) {
                        cout << "Error: All digits must be between 0 and 7." << endl;
                        break;
                    }

                    //Encrypt the number
                    encryptedNum = encrypt(n1, n2, n3, n4);
                    cout << "Encrypted number: " << encryptedNum << endl;
                    break;
            case 2: cout << "Enter a four-digit encrypted integer (digits 0-7 only): ";
                    cin >> num;
                    n4 = num%10,     
                    n3 = (num/10)%10,
                    n2 = (num/100)%10,    
                    n1 = (num/1000)%10;
                    //Check for invalid digits
                    if (n1 > 7 || n2 > 7 || n3 > 7 || n4 > 7) {
                            cout << "Error: All digits must be between 0 and 7." << endl;
                            break;
                        }
                    //Decrypt the number
                    decryptedNum = decrypt(n1, n2, n3, n4);
                    cout << "Decrypted number: " << decryptedNum << endl;
                    break;
            case 3: cout << "Exiting the program." << endl;
                    break;
            default: cout << "Invalid choice. Please enter 1 to encrypt, 2 to decrypt, or 3 to exit." << endl;

        }
    }while(choice != 3);

    //Exit the program
    return 0;
};

int encrypt(int n1, int n2, int n3, int n4){   
    //Declare variables for digits
    int encryptedNum;

    //Encryption logic here
    //step1: Replace each digit by (the sum of that digit plus 3 modulus 8)
    n1 = (n1 + 3) % 8;
    n2 = (n2 + 3) % 8;
    n3 = (n3 + 3) % 8;
    n4 = (n4 + 3) % 8;

    //step2: Swap the first digit with the third, and swap the second digit with the fourth
    swap(n1, n3);
    swap(n2, n4);

    //Combine the digits back into a single integer
    encryptedNum = n1 * 1000 + n2 * 100 + n3 * 10 + n4;

    //Return the encrypted number
    return encryptedNum;
}


int decrypt(int n1, int n2, int n3, int n4){
    //Declare variables for digits
    int decryptedNum;
    int decryption[8][2] = {{0,3},{1,4},{2,5},{3,6},{4,7},{5,0},{6,1},{7,2}};

    //Decryption logic here
    //step1: Swap the first digit with the third, and swap the second digit with the fourth
    swap(n1, n3);
    swap(n2, n4);

    //step2: Remap each letter back to the original digit by reversing the encryption process
    for (int i = 0; i < 8; i++) {  
        if (n1 == decryption[i][1]) n1 = decryption[i][0];
        if (n2 == decryption[i][1]) n2 = decryption[i][0];
        if (n3 == decryption[i][1]) n3 = decryption[i][0];
        if (n4 == decryption[i][1]) n4 = decryption[i][0];
    }

    //Combine the digits back into a single integer
    decryptedNum = n1 * 1000 + n2 * 100 + n3 * 10 + n4;

    //Return the decrypted number
    return decryptedNum;
}

void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
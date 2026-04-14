/*
Author: Philopatair Mallik
Date: 03/00/2026
purpose: C++ Template 
*/

//system libraries
#include <iostream>   //Input/Output library
#include <iomanip>    //format Library
using namespace std;

//User libraries
struct MovieData{
    char title[100];
    char director[100];
    int yrRelse;;
    int runTime; //in minutes
};
//Global Constants - Physics/Chemistry/Conversons/Array Dimensions

//Function Prototype
void getData(MovieData&);
void displayData(const MovieData&);

//Execution begins here
int main(int argv, char **argc)
{
    //Declare variables
    int count;

    cout<<"This program reviews structures"<<endl;
    cout<<"Input how many movies, the Title of the Movie, Director, Year Released, and the Running Time in (minutes)."<<endl;
    cin>>count;
    cin.ignore();
    
    MovieData *movie = new MovieData[count];

    for(int i=0;i<count;i++){
        getData(movie[i]);
        cout<<endl;
        displayData(movie[i]);
    }

    
    //Exit the program
    return 0;
};
void getData(MovieData &movie){
    cin.getline(movie.title,100);
    cin.getline(movie.director,100);
    cin>>movie.yrRelse;
    cin>>movie.runTime;
    cin.ignore();
}
void displayData(const MovieData &movie){
    cout<<left<<setw(11)<<"Title:"<<movie.title<<endl;
    cout<<left<<setw(11)<<"Director:"<<movie.director<<endl;
    cout<<left<<setw(11)<<"Year:"<<movie.yrRelse<<endl;
    cout<<left<<setw(11)<<"Length:"<<movie.runTime<<endl;
}
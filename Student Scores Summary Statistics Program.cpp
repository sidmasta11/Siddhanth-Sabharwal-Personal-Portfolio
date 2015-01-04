//This program reads a text file and calculates the average, highest score, and lowest score for each student.
//Author Siddhanth Sabharwal
//Date 06/04/2014

//NOTE: YOU NEED TO HAVE A TXT FILE WITH SCORES BEFORE YOU CAN RUN THIS PROGRAM
//ENTER THE LOCATION OF THAT TXT FILE BELOW

#include <iostream>
#include <math.h>
#include <fstream>
#include <string>

double calcAverage (int, int, int); //Prototype for the function that calculates the average of the scores
int findHighest (int, int, int); //Prototype for the function that finds the highest score
int findLowest (int, int, int); //Prototype for the function that finds the lowest score


using namespace std;

int main()
{
    string name; //Variable for the name of the students
    int first, second, third; //Variables for the test scores
    ifstream fileIn; //File stream object for input file
    ofstream fileOut; //File stream object for output file

    fileIn.open(""); //This is the file that will be opened and inputted
    fileOut.open(""); //This is the file that will be created and outputted

    if (fileIn) //If the open operation succeeded this condition will be satisfied
    {
        while(fileIn >> name >> first >> second >> third) //Loop that continues execution and inputs values as long as they are available in the file
        {
            //Three function are called in the following statement (explained below)
            fileOut << name << "  - Average is: " << calcAverage(first, second, third) << "; Highest is: " << findHighest(first, second, third) << "; Lowest is: " << findLowest(first, second, third) << endl; //Creates output file with average, highest score, and lowest score
        }
        cout << "Your file has been made." << endl; //This is the standard output the user will immediately see after the output file has been successfully made.

        fileIn.close(); //Input file is closed, and no further changes are made
        fileOut.close(); //Output file is closed, and no further changes are made
    }
    else cout << "There was an error when opening your file." << endl; //If the input file hasn't been found, this statement is printed in standard output

}

double calcAverage(int first, int second, int third) //This function calculates the average of the three scores for each student
{
    return ((first + second + third) / 3.0); //Returns the average of the three scores when called for in the main function
}

int findHighest(int first, int second, int third) //This function finds the highest of the three scores for each student
{
    if(first >= second && first >= third) //If the first score is greater than or equal to both the second and third score this condition is satisfied
        return first; //The first score is returned when this function is called for in the main function
    else if (second >= first && second >= third) //If the second score is greater than or equal to both the first and third score this conditon is satisfied
        return second; //The second score is returned when this function is called for in the main function
    else return third; //If neither the first nor the second score are returned, the third score is returned into the main function when this function is called for
}

int findLowest(int first, int second, int third) //This function finds the lowest of the three scores for each student
{
    if (first <= second && first <= third) //If the first score is less than or equal to both the second and third score this condition is satisfied
        return first; //The first score is returned when this function is called for in the main function
    else if (second <= first && second <= third) //If the second score is less than or equal to both the first and third score this condition is satisfied
        return second; //The second score is returned when this function is called for in the main function
    else return third; //If neither the first nor the second score are returned, the third score is returned into the main function when this function is called for
}

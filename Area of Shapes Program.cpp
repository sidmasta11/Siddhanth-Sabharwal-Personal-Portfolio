//This program calculates the area of various shapes.
//Author Siddhanth Sabharwal
//Date 05/07/2014

#include <iostream>
#include <math.h>

using namespace std;

//Prototypes for area functions
double square(double);
double rectangle(double,double);
double triangle(double,double);
double circle(double);


int main()
{
    //Variables are declared
    double side, length, width, base, height, radius; //Side variable for square function, length and width variables for rectangle function, base and height variables for triangle function, radius for circle function
    int shape; //shape is the variable that will be switched so user can decide what shape they want to calculate the area for

    //User decides which shape they want to get the area for
    cout << "What kind of shape do you want to calculate the area for?" << endl;
    cout << endl << "Enter 1 for a square" << endl;
    cout << "Enter 2 for a rectangle" << endl;
    cout << "Enter 3 for a triangle" << endl;
    cout << "Enter 4 for a circle" << endl << endl;
    cin >> shape;

    switch (shape)
    {
    //First case asks user to input length of side and then calls the square function and calculates area.
    case 1:
        cout << endl << "What is the length of the side of the square?" << endl;
        cin >> side;
        cout << endl << "The area of the square with side " << side << " is " << square(side) << " units squared." << endl; //Square function is called, where area is calculated and outputted here using side input
        break;
    //Second case asks user to input length and width and then calls the rectangle function and calculates area.
    case 2:
        cout << endl << "What is the length of the rectangle?" << endl;
        cin >> length;
        cout << endl << "What is the width of the rectangle?" << endl;
        cin >> width;
        cout << endl << "The area of the rectangle with length " << length << " and width " << width << " is " << rectangle(length,width) << " units squared." << endl; //Rectangle function is called, where area is calculated and outputted here using length and width inputs
        break;
    //Third case asks user to input base and height and then calls the triangle function and calculates area.
    case 3:
        cout << endl << "What is the length of the base of the triangle?" << endl;
        cin >> base;
        cout << endl << "What is the height of the triangle?" << endl;
        cin >> height;
        cout << endl << "The area of the triangle with base " << base << " and height " << height << " is " << triangle(base,height) << " units squared." << endl; //Triangle function is called, where area is calculated and outputted here using base and height inputs
        break;
    //Fourth case asks user to input radius and then calls the circle function and calculates area.
    case 4:
        cout << endl << "What is the length of the radius of the circle?" << endl;
        cin >> radius;
        cout << endl << "The area of the circle with radius " << radius << " is " << circle(radius) << " units squared." << endl; //Circle function is called, where area is calculated and outputted here using radius input
        break;
    //Error message telling user to input a valid number (1 to 4)
    default:
        cout << endl << "Please enter a number from 1 to 4." << endl;
        break;
    }


    return 0;


}

//Function calculates area of square by squaring length of side.
double square(double side)
{
    return pow(side,2); //area of square is calculated by squaring the side input from case 1
}
//Function calculates area of rectangle by multiplying length by width.
double rectangle(double length, double width)
{
  return length*width; //area of rectangle is calculated by multiplying length and width inputs together from case 2
}

//Function calculates area of triangle by multiplying base by height and then dividing by 2.
double triangle(double base, double height)
{
    return (base*height)/2; //area of triangle is calculated by multiplying base and height inputs together from case 3 and then dividing that result by 2
}

//Function calculates area of circle by squaring radius and multiplying it by PI.
double circle(double radius)
{
    const double PI = 3.14159265359; //constant variable PI is declared
    return PI*pow(radius,2); //area of circle is calculated by multiplying the constant variable PI by the square of the radius input from case 4
}

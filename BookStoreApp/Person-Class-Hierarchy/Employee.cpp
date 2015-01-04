/*
 Employee.cpp
 */

#include "Employee.h"
#include <ctime>
#include <string>

Employee::Employee() : employeeID(-1){}

Employee::Employee(int age, string address, string name, int empId) : Person(age, address, name)
{
    if(!empId)
       setID();
    else
       setID( empId );
}

Employee::~Employee(){}

void Employee::setID()
{
    employeeID = generateRandID();
}

void Employee::setID(int ID)
{
    employeeID = ID;
}

int Employee::getID() const
{
    return employeeID;
}

int Employee::generateRandID()
{
    int id;
    srand(time(NULL) + rand()); 
    id = rand() % INT_MAX;             
    return id;
}

ostream& operator<<(ostream& os, const Employee& emp)
{
    os << "\nEmployee" << "\nName: " << emp.getName() << "\nAddress: " << emp.getAddress() << "\nEmployee ID #: " << emp.getID() << endl;
    return os;
}
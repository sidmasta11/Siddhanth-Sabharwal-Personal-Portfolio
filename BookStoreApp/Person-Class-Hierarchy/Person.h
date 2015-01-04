/*
 Person.h
 */

#ifndef Person_H
#define Person_H

#include <iostream>

enum personType{MANAGER, EMPLOYEE, CUSTOMER};
using namespace std;
class Person
{
public:
    Person();
    Person(int age, string address, string name);
    virtual ~Person();
protected:
    int age; //day of birth, MMDDYYYY
    string address; 
    string name; // First Last

public:
    int getAge() const;
    void setAge(int age);

    virtual string getAddress() const;
    virtual void setAddress(string address);

    virtual string getName() const;
    virtual void setName(string);

    virtual int getID() const { return -1; };
};

#endif



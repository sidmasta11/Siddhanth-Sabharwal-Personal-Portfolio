/*
 Person.cpp
 */

#include "Person.h"

Person::Person() : age(0), address(""), name("")
{}

Person::Person(int age, string address, string name) : age(age), address(address), name(name)
{}

Person::~Person(){}

int Person::getAge() const
{
    return age;
}

void Person::setAge(int age)
{
    this->age = age;
}

void Person::setAddress(string address)
{
    this->address = address;
}

string Person::getAddress() const
{
    return address;
}

string Person::getName() const
{
    return name;
}

void Person::setName(string name)
{
    this->name = name;
}


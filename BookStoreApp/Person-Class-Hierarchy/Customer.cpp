/*
 Customer.cpp
 */

#include "Customer.h"
#include <string>

Customer::Customer(){}

Customer::Customer(int age, string address, string name) : Person(age, address, name){}

Customer::~Customer()
{
}

ostream& operator<<(ostream& os, const Customer& cus)
{
    os << "\nName: " << cus.getName() << "\nAddress: " << cus.getAddress();
    return os;
}
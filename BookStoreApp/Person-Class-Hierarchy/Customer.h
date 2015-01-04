/*
 Customer.h
 */

#ifndef Customer_H
#define Customer_H

#include "Person.h"
#include <vector>

class Customer : public Person {
    public:
        Customer();
        Customer(int age, string address, string name);
        virtual ~Customer();
        friend ostream& operator<<(ostream& os, const Customer& cus);
};

#endif
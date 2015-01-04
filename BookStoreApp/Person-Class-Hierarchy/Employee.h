/*
Employee.h
 */

#ifndef Employee_H
#define Employee_H

#include "Person.h"

class Employee : public Person {
    public:
        Employee();
        Employee(int age, string address, string name, int empId);
        virtual ~Employee();
    protected:
        int employeeID;
    public:
        void setID();
        void setID(int ID);
        int getID() const;
        friend ostream& operator<<(ostream& os, const Employee& emp);
    private:
        int generateRandID();
};

#endif
/*
Manager.h
*/

#ifndef Manager_H
#define Manager_H

#include "Employee.h"
#include "Item.h"

enum managerType { shift_manager, store_manager, VP, CEO };

class Manager :
    public Employee
{
protected:
    managerType managerLevel;
public:
    Manager();
    Manager(int age, string address, string name, int empID, managerType level);
    virtual ~Manager();

    void setLevel(managerType lvl);
    managerType getLevel() const;
    string getLevelString() const;	

    friend ostream& operator<<(ostream& os, const Manager& man);
};

#endif

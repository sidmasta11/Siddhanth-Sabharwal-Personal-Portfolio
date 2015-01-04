/*
 Manager.cpp
 */

#include "Manager.h"
#include <string>


Manager::Manager() : managerLevel((managerType)0)
{
}

Manager::Manager(int age, string address, string name, int empID, managerType level) : Employee(age, address, name, empID), managerLevel(level)
{
}

Manager::~Manager()
{}

void Manager::setLevel(managerType level)
{ 
    managerLevel = level;
}

managerType Manager::getLevel() const
{
    return managerLevel;
}

string Manager::getLevelString() const
{
    string managerStr[] = { "shift_manager", "store_manager", "VP", "CEO" };
    return managerStr[(int)managerLevel];
}


ostream& operator<<(ostream& os, const Manager& man)
{
   os << "\nName: " << man.name << "\nAddress: " << man.address << "\nEmployee ID #: " << man.employeeID << "\nManager Level: " << man.getLevelString();
   return os;
}

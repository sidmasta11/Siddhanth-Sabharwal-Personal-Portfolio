/*
 EmployeeList.h
 List of all the employees. Defines functions to display the list,
 search through the list, remove from the list, etc.
 */

#ifndef EmployeeList_H
#define EmployeeList_H


#include "List.h"
#include "Person.h"
#include "Employee.h"
#include "Manager.h"
#include "Customer.h"
#include <fstream>


class EmployeeList : public List<Person*>{

public:
   EmployeeList();
   EmployeeList( string name, string databasePath);
   virtual ~EmployeeList();

   void BuildFromDatabase();
   void SetDatabasePath( string path );
   string GetDatabasePath() const;
   Person* Search( int employeeID );
   virtual void RemoveFromList( Person* person );
   virtual void DisplayList();
   void SaveToTextFile();

private:
   string DatabasePath;
   void ManagerType(managerType& managerLevel, string identifier);
};

#endif

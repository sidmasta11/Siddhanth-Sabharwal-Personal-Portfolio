/*
 OrderList.h
 List of all the orders. Defines functions to display the list,
 search through the list, remove from the list, etc.
 */

#ifndef ORDER_LIST_H
#define ORDER_LIST_H

#include "StoreOrder.h"
#include "EmployeeList.h"
#include "InventoryList.h"
#include "Item.h"
#include <fstream>
#include <string>

class OrderList : public List<StoreOrder *>{

public:
   OrderList();
   OrderList( string name, string databasePath, EmployeeList* employeeList, InventoryList* inventory);
   virtual ~OrderList();

   void BuildFromDatabase();
   void SetDatabasePath( string path );
   string GetDatabasePath() const;
   StoreOrder* Search(int orderNum);
   virtual void RemoveFromList( StoreOrder * order );
   virtual void DisplayList();
   void SaveToTextFile();

private:
   string DatabasePath;
   EmployeeList * empList;
   InventoryList * invList;
};

#endif

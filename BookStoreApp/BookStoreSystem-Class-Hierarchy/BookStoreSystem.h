/*
 BookStoreSystem.h
 Main entry point for the app. Displays the menu and defines functions to show 
 the entire inventory or add/remove/view an item/order/employee to/from/in the
 corresponding inventories.
 */

#ifndef BookStoreSystem_H
#define BookStoreSystem_H

#include "Manager.h"
#include "Item.h"
#include "StoreOrder.h"
#include "EmployeeList.h"
#include "InventoryList.h"
#include "OrderList.h"
#include <iostream>
#include <cctype>
#include "StoreOrder.h"
#include "Order.h"
#include <string>

using namespace std;
class BookStoreSystem
{
public:

    // 3 constructors
    BookStoreSystem();
    BookStoreSystem(string storeName, string storeAddress, string invPATH, string empPATH, string tranPATH);
    ~BookStoreSystem();

protected:

    InventoryList * inventory;
    EmployeeList  * employeeListing;
    OrderList * transactionsList;
    
    Person * user = NULL;
    string storeName;
    string storeAddress;
    string invPATH;
    string empPATH;
    string tranPATH;
 
public:
    void menu();
    Person * login();
    void makeOrder();

private:
    //Initializes the 3 main vectors
    void initLists(string invPATH, string empPATH, string tranPATH);

    //These display the 3 main vectors
    void showInventory() const;
    void showTransactions() const;
    void showEmployees() const;

    //INVENTORYLIST   interaction
    void modifyInventory();               //add, subtract, edit an Item
    Item * addItem();                       //add item
    void removeItem(Item * targetItem);   //subtract Item
	void viewItem(Item *);
    Item* searchInventory();

    //ORDERLIST interaction
    void modifyTransactions();    //add, subtract, edit a Transaction
	void makeStoreOrder();
	void newStoreOrder();
    void removeTransaction(StoreOrder  * targetTransaction);
	void viewTransaction(StoreOrder  * targetTransactionn);

    //EMPLOYEELIST    interaction
    void modifyEmployees();       //add, subtract, edit an Employee
    void addEmployee();             
    void removeEmployee(Person * targetPerson);
    void viewEmployee(Person * employee);
    
    //Time did not permit
	/*void editItem(Item * targetItem);
	void editTransaction(Order<Item *> * targetTransaction);
    void editEmployee(Person * targetPerson);*/

};

#endif


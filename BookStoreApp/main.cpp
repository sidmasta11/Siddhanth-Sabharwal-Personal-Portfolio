/*
 File name:  main.cpp
 Developers:  Matthew Bozelka, Pegah Sattari, Timothy Walker, Siddhanth Sabharwal, Hasnain Haider
 Course: CS 2B - Team Project
 Program purpose: This program implements an online book store system. The program has three inventory
 database files, for books, orders, and employees. The program has menu options to show the entire inventory
 or edit the books/orders/employees by adding them to or removing them from the inventory. One could also
 search the inventory for a specific book/order/employee.
 
 Text file formats are as follows:
 book-inventory.txt:
 Title;Author;Genre;Price;ID;<Quantity>;ISBN;Publisher;<Book type-specific info>
 PaperBook: <Quantity> = Quantity, <Book type-specific info> = NumberOfPages
 eBook: <Quantity> = NULL, <Book type-specific info> = eBookFileFormat
 AudioBook: <Quantity> = Quantity, <Book type-specific info> = AudioFileFormat
 
 orders.txt:
 ISBN;EmployeeID;Quantity;OrderNumber;Date;OrderedFrom
 
 employee-list.txt:
 Name;Age;ID;Address;<Employee type>;<Employee level>
 Employee: <Employee type> = Employee, <Employee level> = Standard
 Manager: <Employee type> = Manager, <Employee level> = shift_manager/store_manager/VP/CEO
 ................................................
 
 Program history:
 Date         Version        ID        Description
 12/7/2014    1.0            137925    Initial creation
 */

#include <iostream>
#include <map>
#include "List.h"
#include "InventoryList.h"
#include "Item.h"
#include "StoreOrder.h"
#include "BookStoreSystem.h"
using namespace std;


void welcomeMessage();

int main()
{

   //Sid's files
   map<string, string> databases;
   databases["Book-Inventory"] = "C:\\Users\\Owner\\Documents\\Foothill\\CS 2B\\BookStoreApp\\BookStoreApp\\databases\\book-inventory.txt";
   databases["Employee-List"] = "C:\\Users\\Owner\\Documents\\Foothill\\CS 2B\\BookStoreApp\\BookStoreApp\\databases\\employee-list.txt";
   databases["Order-List"] = "C:\\Users\\Owner\\Documents\\Foothill\\CS 2B\\BookStoreApp\\BookStoreApp\\databases\\orders.txt";
   
   welcomeMessage();
   BookStoreSystem * OurBookStore = NULL;
   try{
      OurBookStore = new BookStoreSystem("Our Awesome Book Store", "1234 El Monte dr.", databases["Book-Inventory"], databases["Employee-List"], databases["Order-List"]);
      OurBookStore->menu();
   }catch(string e){

      cout << "\nThere was an error in the system with:\n"
           << e << "\n\n";
      
   }

   if(OurBookStore)
      delete OurBookStore;

   return 0;
}

void welcomeMessage()
{
    cout << "\nWelcome to our Book Store\n";
}


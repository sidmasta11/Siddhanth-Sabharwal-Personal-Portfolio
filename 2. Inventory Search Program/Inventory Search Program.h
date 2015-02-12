/*
File name: Lab2.cpp
Developer: Siddhanth Sabharwal
Program Purpose: This program reads a formatted text file containing name, quantity, price, and condition for various items.
The inventory management system will show all inventory, show defective inventory, and will allow the user
to get information for specific product numbers. The inventory will be stored in an array of pointers meaning
records are to be stored in dynamic memory.
Text File Format: Name;Quantity;Price;Condition
Example:
Panasonic DVD Player;5;125.99;D
Samsung TV;15;298.99;R
Program History:
Date                         Version                        ID                    Description
10/27/2014                   1.0                            1000                  Initial Creation
*/


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

//forward declarations
class InventorySystem;
class InventoryItem;
class Product;
class eProduct;

class InventorySystem{

private:
   string StoreName;
   int StoreID;
   InventoryItem * ItemList[512];                     //array of pointers to InventoryItem objects, max of 512
   int ItemCount;                                    //tracks how many items are stored in the array

public:
   InventorySystem();
   InventorySystem(string storename, int id);
   ~InventorySystem();

   void BuildInventory();
   void ShowInventory()  const;
   void ShowDefectiveInventory() const;
   void SearchItem() const;

};

class InventoryItem{

protected:
   string Name;
   int Quantity;

public:
   InventoryItem();
   InventoryItem(string name, int quantity);
   ~InventoryItem();

   void SetName();
   string GetName() const;
   int GetQuantity() const;
   void AddQuantity();
   void DisplayItem() const;

};

class Product : public InventoryItem {                                  //derived from InventoryItem class

protected:
   int ProductID;
   double Price;

public:
   Product();
   Product(string name, int quantity, int id, double price);
   ~Product();

   void SetID();
   int GetID() const;
   void SetPrice();
   double GetPrice() const;
   void DisplayItem() const;
   int generateProductID();

};

enum Condition{ NEW, REFURBISHED, USED, DEFECTIVE };                         //options for condition of eProduct

class eProduct : public Product{                                            //derived from Product baseclass

private:
   Condition condition;

public:
   eProduct();
   eProduct(string name, int quantity, int id, double price, Condition state);
   ~eProduct();

   Condition GetCondition() const;
   void SetCondition();
   void DisplayItem() const;
   bool DefectiveTest() const;

};

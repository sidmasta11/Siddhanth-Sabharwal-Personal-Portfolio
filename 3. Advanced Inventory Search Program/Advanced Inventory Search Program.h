/*
File name: Assignment3.cpp
Developer: Siddhanth Sabharwal
Program Purpose: This program reads a formatted text file containing product type, name, quantity, price, and special data.
The product type can either be dairy product and eProduct. The special data for dairy products is the expiration date, and the
special data for eProducts is the condition they are in.The inventory management system will show all inventory,
show defective inventory, show expired items, and will allow the user to get information for specific product numbers.
The inventory will be stored in an array of pointers meaningrecords are to be stored in dynamic memory.
Text File Format: <Product Type>;Name;Quantity;Price;<Product Special Data>
Example:
EP;Panasonic DVD Player;35;125.99;D
DP;Dutch Cheese;234;4.95;141836800
Program History:
Date                         Version                        ID                    Description
11/17/2014                   1.0                            1000                  Initial Creation
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
class Item;
class InventoryItem;
class Product;
class eProduct;
class DairyProduct;

class InventorySystem{

private:
   string StoreName;
   int StoreID;
   Item * ItemList[512];                     //array of pointers to Item objects, max of 512
   int ItemCount;                            //tracks how many items are stored in the array

public:
   InventorySystem();
   InventorySystem(string storename, int id);
   ~InventorySystem();

   void BuildInventory();
   void ShowInventory()  const;
   void ReportExpiredItems() const;
   void ReportDefectiveItems() const;
   Item* SearchItem() const;

};

class Item{

public:
   Item();
   virtual ~Item();

   virtual bool IsNew() const = 0;
   virtual Item* Clone() const = 0;
   virtual bool MoreValuable(Item const &ip) const = 0;
   virtual void DisplayItem() const = 0;

};

class InventoryItem : public Item {

protected:
   string ProductType;
   string Name;
   int Quantity;

public:
   InventoryItem();
   InventoryItem(string producttype, string name, int quantity);
   ~InventoryItem();

   void SetName();
   string GetName() const;
   int GetQuantity() const;
   void AddQuantity();
   virtual void DisplayItem() const;

};

class Product : public InventoryItem {                                  //derived from InventoryItem class

protected:
   int ProductID;
   double Price;

public:
   Product();
   Product(string producttype, string name, int quantity, int id, double price);
   ~Product();

   void SetID();
   int GetID() const;
   void SetPrice();
   double GetPrice() const;
   virtual void DisplayItem() const;
   int generateProductID();
   bool MoreValuable(const Item &ip) const;

};

enum Condition{ NEW, REFURBISHED, USED, DEFECTIVE };                         //options for condition of eProduct

class eProduct : public Product{                                            //derived from Product baseclass

private:
   Condition condition;

public:
   eProduct();
   eProduct(string producttype, string name, int quantity, int id, double price, Condition state);
   ~eProduct();

   Condition GetCondition() const;
   void SetCondition();
   virtual void DisplayItem() const;
   bool DefectiveTest() const;
   bool IsNew() const;
   eProduct* Clone() const;
   
   friend ostream & operator<< (ostream& os, const eProduct & c);
   bool operator== (const eProduct& other) const;

};

class DairyProduct : public Product{

private:
   time_t ExpirationTime;

public:
   DairyProduct();
   DairyProduct(string producttype, string name, int quantity, int id, double price, time_t expirationtime);
   ~DairyProduct();

   time_t GetExpirationTime() const;
   void SetExpirationTime();
   virtual void DisplayItem() const;
   bool IsNew() const; 
   DairyProduct* Clone() const;
};
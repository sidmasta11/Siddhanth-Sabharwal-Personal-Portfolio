/*
File name: Assignment4.h
Developer: Siddhanth Sabharwal
Program Purpose: This program reads a formatted text file containing product type, name, quantity, price, special data,
customer ID, order ID, and order Date.The product type can either be dairy product and eProduct.
The special data for dairy products is the expiration date, and the special data for eProducts is the condition
they are in.The inventory management system will show all inventory, show defective inventory, show expired items,
and will allow the user to get information for specific product numbers, and customer IDs.
The inventory will be stored in an array of pointers meaning the records are to be stored in dynamic memory.
Text File Format: <Product Type>;Name;Quantity;Price;<Product Data>;CustomerID;OrderID;OrderDate
Example:
EP;Panasonic DVD Player;35;125.99;D;BestBuy;BB123;1414936800
DP;Dutch Cheese;234;4.95;141836800;Lucky;LK1234;1414831234
Program History:
Date                         Version                        ID                    Description
12/11/2014                   1.0                            1000                  Initial Creation
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <iomanip>
#include<map>
#include<deque>

using namespace std;

//forward declarations
class OrderProcessingSystem;
class Item;
class InventoryItem;
class Product;
class eProduct;
class DairyProduct;
class Address;
template <class T> class Order;

class OrderProcessingSystem{
private:
   string storeName;
   string storeID;
   Address* AddressPtr;
   map < string, deque<Order<Item*>> > customerOrderMap;

public:
   OrderProcessingSystem();
   OrderProcessingSystem(string storename, string storeid, int streenumber, string streetname, int zipcode, string state);
   ~OrderProcessingSystem();

   OrderProcessingSystem & operator=(const OrderProcessingSystem & rhs);
   
   void Init();
   void Menu() const;
   void Start();
   void FindOrders() const;
   void ShowAllOrders() const;
   void ProcessOrder();    
};

template <class T>
class Order {
protected:
   string orderID;
   long orderDate;
   T item;

public:
   Order();
   Order(T t, string orderid, long orderdate);
   ~Order();

   string getOrderID() const;
   void setOrderID(string tempOrderID);
   T getItem() const;
   void setItem(const T &Tref);
   long getOrderDate() const;
   void setOrderDate(long tempOrderDate);

   bool operator== (const Order&rhs) const;
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
   virtual bool MoreValuable(const Item &ip) const;

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
   virtual bool IsNew() const;
   virtual eProduct* Clone() const;

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
   virtual bool IsNew() const;
   virtual DairyProduct* Clone() const;

   friend ostream & operator<< (ostream& os, const DairyProduct & c);
};

class Address{
private:
   int streetNumber;
   string streetName;
   int zipCode;
   string State;
public:
   Address();
   Address(int streetnumber, string streetname, int zipcode, string state);
   ~Address();

   void SetStreetNumber();
   int GetStreetNumber() const;
   void SetStreetName();
   string GetStreetName() const;
   void SetZipCode();
   int GetZipCode() const;
   void GetState();
   string GetState() const;
};


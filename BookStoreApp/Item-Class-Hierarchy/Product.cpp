/*
 Product.cpp
 */

#include "Product.h"

using namespace std;

Product::Product() : InventoryItem(), ProductID(SetID()), Price(0.0) {}

Product::Product(string Name, int Quantity, double Price) : InventoryItem(Name, Quantity), Price(Price)
{
	SetID();
}

Product::Product(string Name, int Quantity, double Price, int ID) : InventoryItem(Name, Quantity), Price(Price), ProductID(ID)
{
}

Product::~Product() 
{
   cout << "Product deleted" << endl;
}

int Product::GetID()
{ 
   return ProductID;
}

double Product::GetPrice()
{ 
   return Price;
}

bool Product::SetID()
{
   ProductID = generateProductID();
   return true;
}

void Product::SetID(int ID)
{
	ProductID = ID;
}

bool Product::SetPrice(double Price)
{
   if (Price >= 0.00)
   {
      this->Price = Price;
      return true;
   }
   else
      return false;
}

const void Product::DisplayItem()
{
   InventoryItem::DisplayItem();
   cout << ProductID << " " << fixed << setprecision(2) << Price << " ";
}

int Product::generateProductID()
{
   int id;
   srand(time(NULL) + rand()); // generate a seed
   id = rand() % 100000;             // generate a number between 0-99999
   return id;
}
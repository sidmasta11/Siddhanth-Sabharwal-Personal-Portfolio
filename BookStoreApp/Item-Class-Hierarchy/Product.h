/*
 Product.h
 */

#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "InventoryItem.h"
using namespace std;

class Product : public InventoryItem //derived from InventoryItem class 
{
protected:
   int ProductID; //never passed, always generated
   double Price;

public:
   //Constructor
   Product();
   Product(string Name, int Quantity, double Price);
   Product(string Name, int Quantity, double Price,int ID);

   //Destructor
   virtual ~Product();

   //Accessors
   int GetID();
   double GetPrice();

   //Mutators
   bool SetID();
   void SetID(int ID);
   bool SetPrice(double Price);

   //Class member funtions
   virtual const void DisplayItem();
   int generateProductID();

};

#endif
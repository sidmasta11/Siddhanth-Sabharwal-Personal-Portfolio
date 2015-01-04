/*
InventoryItem.cpp
 */

#include "InventoryItem.h"

InventoryItem::InventoryItem() : ItemType(""), Quantity(0) {}
InventoryItem::InventoryItem(string Name, int Quantity) : ItemType(Name), Quantity(Quantity) {}

InventoryItem::~InventoryItem() 
{
   cout << "InventoryItem deleted" << endl;
}

string InventoryItem::getName() const
{ 
   return ItemType;
}

int InventoryItem::getQuantity() const
{ 
   return Quantity;
}

void InventoryItem::setName(string Name)
{ 
   this->ItemType = Name;
}

const void InventoryItem::DisplayItem()
{
   Item::DisplayItem();
   cout << ItemType << " " << Quantity << " ";
}

bool InventoryItem::setQuantity(int Quantity)
{
   if (Quantity >= 0 && Quantity < 2147483647)
   {
      this->Quantity = Quantity;
      return true;
   }
   else
      return false; 
}
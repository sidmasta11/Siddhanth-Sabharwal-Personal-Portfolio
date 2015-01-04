/*
 InventoryItem.h
 */

#ifndef INVENTORYITEM_H
#define INVENTORYITEM_H

#include "Item.h"

class InventoryItem : public Item
{
protected:
   string ItemType;
   int Quantity;

public:
   InventoryItem();
   InventoryItem(string Name, int Quantity);

   virtual ~InventoryItem();

   string getName() const;
   int getQuantity() const;

   void setName(string Name);
   bool setQuantity(int Quantity);

   virtual const void DisplayItem();
};

#endif
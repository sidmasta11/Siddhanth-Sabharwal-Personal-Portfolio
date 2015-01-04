/*
Item.h
 */

#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
using namespace std;


class Item
{
public:
   Item();
   virtual ~Item();
   virtual int GetID();
   virtual const void DisplayItem() = 0;                //take no parameter and return nothing.Default implementation is to display an empty string(“”).
};

#endif 

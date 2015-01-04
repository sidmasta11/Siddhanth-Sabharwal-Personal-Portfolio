/*
Item.cpp
 */

#include "Item.h"

using namespace std;

Item::Item() {}

Item::~Item() 
{
   cout << "Item deleted" << endl;
}

int Item::GetID()
{ 
   return -1;
}

void const Item::DisplayItem()             //take no parameter and return nothing. Default implementation is to display an empty string(“”).
{
   cout << "" << endl;
}
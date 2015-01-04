/*
StoreOrder.h
*/

#ifndef StoreOrder_H
#define StoreOrder_H

#include "Order.h"
#include "Item.h"
#include "Person.h"
#include "Employee.h"
#include "Manager.h"
#include <string>

class StoreOrder: public Order<Item *> {
   private:
      string orderFrom;
      Person * person;
   public:
      StoreOrder();
      StoreOrder(Item *givenItem, int quant=0, string name="Amazon", Person *givenPerson=NULL);
      StoreOrder(Item *givenItem, int quantity, int orderNum, string date, string name, Person *givenPerson);

      virtual ~StoreOrder();
      void setOrderFrom(string givenOrderFrom);
      string getOrderFrom() const;
      void setPerson(Person *givenPerson);
      Person * getPerson() const;
      friend ostream & operator<< (ostream & os, const StoreOrder* s);
};

#endif

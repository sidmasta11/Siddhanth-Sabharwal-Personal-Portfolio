/*
StoreOrder.cpp
*/

#include "StoreOrder.h"
#include "eBook.h"
#include "AudioBook.h"
#include "PaperBook.h"
using namespace std;

StoreOrder::StoreOrder(): Order(), orderFrom(""), person(NULL) {}

StoreOrder::StoreOrder(Item *givenItem, int quant, string name, Person *givenPerson):
   Order(givenItem, quant), orderFrom(name), person(givenPerson) {}

StoreOrder::StoreOrder(Item *givenItem, int quantity, int orderNum, string date, string name, Person *givenPerson):
   Order(givenItem, quantity, orderNum, date), orderFrom(name), person(givenPerson){}

StoreOrder::~StoreOrder() {
   cout << "StoreOrder destructor";
}

void StoreOrder::setOrderFrom(string givenOrderFrom) {
   orderFrom = givenOrderFrom;
}

string StoreOrder::getOrderFrom() const {
   return orderFrom;
}

void StoreOrder::setPerson(Person *givenPerson) {
   person = givenPerson;
}

Person * StoreOrder::getPerson() const {
   return person;
}

ostream & operator<< (ostream & os, const StoreOrder* s) {

   eBook * eb = dynamic_cast <eBook *> (s->item);
   PaperBook * pb = dynamic_cast <PaperBook *> (s->item);
   AudioBook * ab = dynamic_cast <AudioBook *> (s->item);

   Employee * ep = dynamic_cast <Employee *> (s->person);
   Manager * mg = dynamic_cast <Manager *> (s->person);

   cout << "Order Number: " << s->orderID << endl;
   if (mg) {
      cout << "Ordered By: " << mg->getName()<< endl;
   }else if(ep){
      cout << "Ordered By: " << ep->getName()<< endl;
   }
   cout << "Order Date: " << s->getOrderDate() << endl;
   cout << "Ordered From: " << s->getOrderFrom();
   if (eb) {
      os << (*eb) << "\n";
   }
   else if (pb) {
      os << (*pb) << "\n";
   }
   else if (ab) {
      os << (*ab) << "\n";
   }
   return os;
}



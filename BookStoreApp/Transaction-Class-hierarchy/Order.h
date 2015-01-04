/*
Order.h, contains the declaration and definition of the Order class template.
 */

#ifndef Order_H
#define Order_H

#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
#include <ctime>
using namespace std;

template <class T>
class Order {
    protected:
        T item;
        int orderQuantity;
        int orderID;
        string orderDate;
    private:
        int generateRandomID() const;
        void setOrderDate();
    public:
        Order();
        Order(T t, int quantity);
        Order(T t, int quantity, int orderNum, string date);
        virtual ~Order();
        void setItem(const T &Tref);
        T getItem() const;
        void setOrderQuantity(int givenQuantity);
        int getOrderQuantity() const;
        void setOrderID(int givenID);
        int getOrderID() const;
        string getOrderDate() const;
};


template <class T>
Order<T>::Order() { cout << "Order constructor"; }

template <class T>
Order<T>::Order(T t, int quantity) {
    item = t;
    orderQuantity = quantity;
    orderID = generateRandomID();
    time_t rawtime = time(NULL);
    orderDate = ctime(&rawtime);
}

template <class T>
Order<T>::Order(T t, int quantity, int orderNum, string date) :
   item(t), orderQuantity(quantity), orderID(orderNum), orderDate(date){}

template <class T>
Order<T>::~Order() { cout << "Order destructor"; }

template <class T>
void Order<T>::setItem(const T &Tref) {
    item = Tref;
}

template <class T>
T Order<T>::getItem() const {
    return item;
}

template<class T>
void Order<T>::setOrderQuantity(int givenQuantity) {
    orderQuantity = givenQuantity;
}

template<class T>
int Order<T>::getOrderQuantity() const{
    return orderQuantity;
}

template<class T>
void Order<T>::setOrderID(int givenID) {
    orderID = givenID;
}

template<class T>
int Order<T>::getOrderID() const{
    return orderID;
}

template<class T>
void Order<T>::setOrderDate() {
   time_t rawtime = time(NULL);
   orderDate = ctime(&rawtime);
}

template<class T>
string Order<T>::getOrderDate() const{
   return orderDate;
}

template<class T>
int Order<T>::generateRandomID() const {
    int id ;
    srand (time(NULL) + rand());   // generate a seed
    id = rand();                   // generate a random number
    return id;
}

#endif

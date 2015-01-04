/*
 List.h
 A class template for the three inventory lists. Parent for list of items/orders/employees.
 */

#ifndef List_H
#define List_H

#include <iostream>
#include <vector>
using namespace std;

template <class T>
class List{

    public:

        List();
        List( string name );
        List( string name, T array[], int arrayLength );
        virtual ~List();
        void AddToList( T item );
        virtual void RemoveFromList( T item );
        virtual void DisplayList();
        string GetListName() const;
        void SetListName( string name );
        int GetListCount() const;
        T GetElementAtPosI(int i) const;

    protected:
        string ListName;
        int ItemCount;
        vector<T> ItemList;
        typename vector<T>::iterator p;
};


template <class T>
List<T>::List():ListName(""), ItemCount(0), ItemList(NULL){}

template <class T>
List<T>::List( string name ):ListName(name), ItemCount(0), ItemList(NULL){}

template <class T>
List<T>::List( string name, T array[], int arrayLength ):ListName(name)
{

   ItemCount = 0;

   for( int i = 0; i < arrayLength; ++i )
   {
      AddToList( array[i] );
      ++ItemCount;
   }

}

template <class T>
List<T>::~List()
{
   cout << "\nList " << this->ListName <<  " was destroyed\n";
}

template <class T>
void List<T>::AddToList( T item )
{

   ItemList.push_back( item );

}

template <class T>
void List<T>::RemoveFromList( T item )
{

   for( int i = 0; i < ItemList.size(); i++ )
   {
      if(ItemList[i] == item)
      {
         ItemList.erase(ItemList.begin() + i);
         --ItemCount;
      }
   }

}

template <class T>
void List<T>::DisplayList()
{

   for( p = ItemList.begin(); p != ItemList.end(); p++ )
   {
      cout << "\n" << *p << "\n";
   }
   
}

template <class T>
string List<T>::GetListName() const
{
   return ListName;

}

template <class T>
void List<T>::SetListName( string name )
{

   ListName = name;

}

template <class T>
int List<T>::GetListCount() const
{
    return ItemList.size();

 
}

template <class T>
T List<T>::GetElementAtPosI(int I) const
{
   return ItemList[I];
}

#endif


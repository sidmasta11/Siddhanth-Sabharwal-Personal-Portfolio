/*
 PaperBook.h
 */


#ifndef PAPERBOOK_H
#define PAPERBOOK_H

#include "Book.h"
class PaperBook : public Book
{
private:
   int pageCount;

public:
   //Constructors
   PaperBook();
   PaperBook(string Name, int Quantity, double Price, int ID, int ISBN, string author, string title,
      genreType genre, string publisher, int pageCount);
   PaperBook(string Name, int Quantity, double Price, int ISBN, string author, string title,
	   genreType genre, string publisher, int pageCount);

   //Destructor
   virtual ~PaperBook();

   //Mutators and Accessors
   int getNumberOfPages();

   bool setNumberOfPages(int pageCount);

   virtual const void DisplayItem();

   friend ostream & operator<< (ostream & os, const PaperBook & paperBookRef);
   const bool operator== (const PaperBook & paperBookRef);
   const bool operator!= (const PaperBook & paperBookRef);
   const PaperBook & operator= (const PaperBook & paperBookRef);
};

#endif
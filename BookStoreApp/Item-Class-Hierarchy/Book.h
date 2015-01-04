/*
 Book.h
 */

#ifndef BOOK_H
#define BOOK_H

#include "Product.h"
#include <iostream>

enum genreType { UNKNOWN, SCIENCE_FICTION, MYSTERY, HORROR, ROMANCE };

using namespace std;
class Book : public Product
{
protected:
   int ISBN;
   string author;
   string title;
   genreType genre;
   string publisher;

public:
   Book();
   Book(string Name, int Quantity, double Price, int ISBN, string author, string title, genreType genre, string publisher);
   Book(string Name, int Quantity, double Price, int ID, int ISBN, string author, string title, genreType genre, string publisher);
   virtual ~Book();

   int getISBN();
   string getAuthor();
   string getTitle();
   genreType getGenre();
   string getPublisher();

   bool setISBN(int ISBN);
   bool setAuthor(string author);
   bool setTitle(string title);
   bool setGenre(genreType genre);
   bool setPublisher(string publisher);

   string getTextForGenre()const;
   virtual const void DisplayItem();
};

#endif

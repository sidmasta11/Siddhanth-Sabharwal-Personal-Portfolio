/*
 eBook.h
 */

#ifndef EBOOK_H
#define EBOOK_H

#include "Book.h"

enum eBookFileFormat { UNKNOWN_EBOOK, PDF, EPUB };

class eBook : public Book
{
private:
   eBookFileFormat fileFormat;

public:
   //Constructors
   eBook();
   eBook(string Name, int Quantity, double Price, int ID,
      int ISBN, string author, string title,
      genreType genre, string publisher, eBookFileFormat fileFormat);
   eBook(string Name, int Quantity, double Price,
	   int ISBN, string author, string title,
	   genreType genre, string publisher, eBookFileFormat fileFormat);

   //Destructor
   virtual ~eBook();
   
   //Mutators and Accessors
   eBookFileFormat getFileFormat();
   bool setFileFormat(eBookFileFormat fileFormat);
   
   string eBookFileFormatText()const;
   virtual const void DisplayItem();

   friend ostream & operator<< (ostream& os, const eBook & eBookRef);
   const bool operator== (const eBook & eBookRef);
   const bool operator!= (const eBook & eBookRef);
   const eBook & operator= (const eBook & eBookRef);
};

#endif
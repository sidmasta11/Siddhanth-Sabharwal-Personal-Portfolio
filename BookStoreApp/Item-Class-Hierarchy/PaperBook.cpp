/*
PaperBook.cpp
*/

#include "PaperBook.h"

PaperBook::PaperBook() : Book(), pageCount(0) {}
PaperBook::PaperBook(string Name, int Quantity, double Price, int ISBN, string author, string title,
                     genreType genre, string publisher, int pageCount) :
                     Book(Name, Quantity, Price, ISBN, author, title, genre, publisher), pageCount(pageCount) {}
PaperBook::PaperBook(string Name, int Quantity, double Price, int ID, int ISBN, string author, string title,
	genreType genre, string publisher, int pageCount) :
	Book(Name, Quantity, Price, ID, ISBN, author, title, genre, publisher), pageCount(pageCount) {}


PaperBook::~PaperBook() 
{
   cout << "PaperBook deleted" << endl;
}

int PaperBook::getNumberOfPages()
{ 
   return pageCount;
}

bool PaperBook::setNumberOfPages(int pageCount)
{
   this->pageCount  = pageCount;
   return true;
}

const void PaperBook::DisplayItem()
{
   Book::DisplayItem();
   cout << pageCount << " ";
}

ostream & operator<<(ostream & os, const PaperBook& paperBookRef)
{
   os << "\nName: " << paperBookRef.ItemType
	  << "\nProduct ID:" << paperBookRef.ProductID
      << "\nQuantity: " << paperBookRef.Quantity
      << "\nPrice: " << paperBookRef.Price
      << "\nISBN: " << paperBookRef.ISBN
      << "\nAuthor: " << paperBookRef.author
      << "\nTitle: " << paperBookRef.title
      << "\nGenre: " << paperBookRef.getTextForGenre()
      << "\nPublisher: " << paperBookRef.publisher
      << "\nPage Count: " << paperBookRef.pageCount;
   return os;
}

const bool PaperBook::operator== (const PaperBook & paperBookRef)
{
   return (this->ItemType == paperBookRef.ItemType
      && this->Quantity == paperBookRef.Quantity
      && this->Price == paperBookRef.Price
      && this->ISBN == paperBookRef.ISBN
      && this->author == paperBookRef.author
      && this->title == paperBookRef.title
      && this->genre == paperBookRef.genre
      && this->publisher == paperBookRef.publisher
      && this->pageCount == paperBookRef.pageCount);
}

const bool PaperBook::operator!= (const PaperBook & paperBookRef)
{
   return !operator==(paperBookRef);
}

const PaperBook & PaperBook::operator= (const PaperBook & paperBookRef)
{
   if (this != &paperBookRef)
   {
      this->ItemType = paperBookRef.ItemType;
      this->Quantity = paperBookRef.Quantity;
      this->Price = paperBookRef.Price;
      this->ISBN = paperBookRef.ISBN;
      this->author = paperBookRef.author;
      this->title = paperBookRef.title;
      this->genre = paperBookRef.genre;
      this->publisher = paperBookRef.publisher;
      this->pageCount = paperBookRef.pageCount;
   }
   return *this;
}
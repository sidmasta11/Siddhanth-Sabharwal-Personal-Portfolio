/*
Book.cpp
*/

#include "Book.h"

Book::Book() : Product(), ISBN(0), author(""), title(""), genre(UNKNOWN), publisher("") {}

Book::Book(string Name, int Quantity, double Price, int ISBN, string author, string title, genreType genre, string publisher) :
Product(Name, Quantity, Price), ISBN(ISBN), author(author), title(title), genre(genre), publisher(publisher) {}

Book::Book(string Name, int Quantity, double Price, int ID ,int ISBN, string author, string title, genreType genre, string publisher) :Product(Name, Quantity, Price, ID), ISBN(ISBN), author(author), title(title), genre(genre), publisher(publisher) {}

Book::~Book()
{
   cout << "Book deleted" << endl;
}

int Book::getISBN()
{ 
   return ISBN;
}

string Book::getAuthor() 
{ 
   return author;
}

string Book::getTitle()
{ 
   return title;
}

genreType Book::getGenre() 
{ 
   return genre;
}

string Book::getPublisher()
{ 
   return publisher; 
}

bool Book::setISBN(int ISBN)
{
   if (ISBN < 0)
      return false;

   this->ISBN = ISBN;
   return true;
}

bool Book::setAuthor(string author)
{
   this->author = author;
   return true;
}

bool Book::setTitle(string title)
{
   this->title = title;
   return true;
}

bool Book::setGenre(genreType genre)
{
   this->genre = genre;
   return true;
}

bool Book::setPublisher(string publisher)
{
   this->publisher = publisher;
   return true;
}

string Book::getTextForGenre() const
{
   switch (genre)
   {
   case SCIENCE_FICTION:
      return "Science Fiction";
   case MYSTERY:
      return "Mystery";
   case HORROR:
      return "Horror";
   case ROMANCE:
      return "Romance";
   default:
      return "Unknown";
   }
}

const void Book::DisplayItem()
{
   Product::DisplayItem();
   cout << ISBN << " " << author << " " << title << " " << getTextForGenre() << " " << publisher << " ";
}

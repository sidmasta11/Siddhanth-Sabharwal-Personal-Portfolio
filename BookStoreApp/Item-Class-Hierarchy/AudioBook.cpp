/*
AudioBook.cpp
*/

#include "AudioBook.h"

AudioBook::~AudioBook()
{
   cout << "AudioBook delete" << endl;
}

AudioBook::AudioBook(string Name, int Quantity, double Price, int ISBN, string author, string title,
	genreType genre, string publisher, audioFileFormat fileFormat) :
	Book(Name, Quantity, Price, ISBN, author, title, genre, publisher), fileFormat(fileFormat) {}

AudioBook::AudioBook(string Name, int Quantity, double Price, int ID, int ISBN, string author, string title,
	genreType genre, string publisher, audioFileFormat fileFormat) :
	Book(Name, Quantity, Price, ID, ISBN, author, title, genre, publisher), fileFormat(fileFormat) {}

audioFileFormat AudioBook::getAudioFormat()
{ 
   return fileFormat;
}

void AudioBook::setAudioFormat(audioFileFormat fileFormat)
{
   this->fileFormat = fileFormat;
}

string AudioBook::audioFileFormatText() const
{
   switch (this->fileFormat)
   {
   case MP3:
      return "MP3";
   default:
      return "Unknown";
   }
}

const void AudioBook::DisplayItem()
{
   Book::DisplayItem();
   cout << audioFileFormatText() << " ";
}

ostream & operator<<(ostream & os, const AudioBook& audioBookRef)
{
   os << "\nType of Product: " << audioBookRef.ItemType
	   << "\nProduct ID:" << audioBookRef.ProductID
      << "\nQuantity: " << audioBookRef.Quantity
      << "\nPrice: " << audioBookRef.Price
      << "\nISBN: " << audioBookRef.ISBN
      << "\nAuthor: " << audioBookRef.author
      << "\nTitle: " << audioBookRef.title
      << "\nGenre: " << audioBookRef.getTextForGenre()
      << "\nPublisher: " << audioBookRef.publisher
      << "\nFile Format: " << audioBookRef.audioFileFormatText();
   return os;
}

const bool AudioBook::operator== (const AudioBook & audioBookRef)
{
   return (this->ItemType == audioBookRef.ItemType
      && this->Quantity == audioBookRef.Quantity
      && this->Price == audioBookRef.Price
      && this->ISBN == audioBookRef.ISBN
      && this->author == audioBookRef.author
      && this->title == audioBookRef.title
      && this->genre == audioBookRef.genre
      && this->publisher == audioBookRef.publisher
      && this->fileFormat == audioBookRef.fileFormat);
}

const bool AudioBook::operator!= (const AudioBook & audioBookRef)
{
   return !operator==(audioBookRef);
}

const AudioBook & AudioBook::operator= (const AudioBook & audioBookRef)
{
   if (this != &audioBookRef)
   {
      this->ItemType = audioBookRef.ItemType;
      this->Quantity = audioBookRef.Quantity;
      this->Price = audioBookRef.Price;
      this->ISBN = audioBookRef.ISBN;
      this->author = audioBookRef.author;
      this->title = audioBookRef.title;
      this->genre = audioBookRef.genre;
      this->publisher = audioBookRef.publisher;
      this->fileFormat = audioBookRef.fileFormat;
   }
   return *this;
}

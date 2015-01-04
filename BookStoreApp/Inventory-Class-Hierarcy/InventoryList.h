/*
 InventoryList.h
 List of all the items in the inventory. Defines functions to display the list, 
 search through the list, remove from the list, etc.
 */

#ifndef InventoryList_H
#define InventoryList_H

#include "List.h"
#include "Item.h"
#include "Book.h"
#include "PaperBook.h"
#include "AudioBook.h"
#include "eBook.h"
#include <fstream>
#include <string>

class InventoryList : public List<Item*>{

public:
   InventoryList();
   InventoryList( string name, string databasePath);
   virtual ~InventoryList();

   void BuildFromDatabase();
   void SetDatabasePath( string path );
   string GetDatabasePath() const;
   vector<Item*> Search( string bookProperty );
   Item * Search(int isbn);
   Item * SearchID(int ID);
   virtual void RemoveFromList( Item* item );
   virtual void DisplayList();
   void SaveToTextFile();

private:
   string DatabasePath;
   void Genre(genreType& bGenre, string identifier);
   void AudioFormat(audioFileFormat& abFormat, string identifier);
   void EbookFormat(eBookFileFormat& ebFormat, string identifier);
};

#endif



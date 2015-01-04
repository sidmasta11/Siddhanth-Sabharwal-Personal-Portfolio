/*
 InventoryList.cpp
 */

#include "Book.h"
#include "InventoryList.h"

InventoryList::InventoryList(): List(), DatabasePath(""){}

InventoryList::InventoryList( string name, string databasePath):
   List(name), DatabasePath(databasePath)
{
   
   this->BuildFromDatabase();

}

InventoryList::~InventoryList()
{
   SaveToTextFile();

   for( p = ItemList.begin(); p != ItemList.end(); ++p )
   {
      if(*p)
      {
         delete *p;
      }
      *p = NULL;
   }
}

void InventoryList::SaveToTextFile() {

    ofstream out(DatabasePath, ios::trunc);
    for( p = ItemList.begin(); p != ItemList.end(); ++p )
    {
        eBook* p1 = dynamic_cast<eBook *> (*p);
        PaperBook* p2 = dynamic_cast<PaperBook*>(*p);
        AudioBook* p3 = dynamic_cast<AudioBook*>(*p);
        if (p1 != NULL) {
            out << "eBook;" << p1->getTitle()
            << ";" << p1->getAuthor()
			<< ";" << p1->getTextForGenre()
            << ";" << p1->GetPrice()
            << ";" << p1->GetID()
            << ";" << "NULL"
            << ";" << p1->getISBN()
            << ";" << p1->getPublisher()
            << ";" << p1->eBookFileFormatText()
            << "\n";
        }
        else if (p2 != NULL) {
            out << "Paper Book;" << p2->getTitle()
            << ";" << p2->getAuthor()
            << ";" << p2->getTextForGenre()
            << ";" << p2->GetPrice()
            << ";" << p2->GetID()
            << ";" << p2->getQuantity()
            << ";" << p2->getISBN()
            << ";" << p2->getPublisher()
            << ";" << p2->getNumberOfPages()
            << "\n";
        }
        else if (p3 != NULL){
            out << "Audio Book;" << p3->getTitle()
            << ";" << p3->getAuthor()
            << ";" << p3->getTextForGenre()
            << ";" << p3->GetPrice()
            << ";" << p3->GetID()
            << ";" << p3->getQuantity()
            << ";" << p3->getISBN()
            << ";" << p3->getPublisher()
            << ";" << p3->audioFileFormatText()
            << "\n";
        }
    }
    out.close();

}

void InventoryList::BuildFromDatabase()
{

   try{

      ifstream inventoryFile(DatabasePath);
      string productType, author, title, genre, publisher, audioFormat, ebookFormat, buffer;
      int quanity, isbn, pageCount;
      double price;
      genreType bGenre;
      audioFileFormat abFormat;
      eBookFileFormat ebFormat;
	   int ID;
      
      if ( !inventoryFile ) {
         throw this->GetListName();
      }

      while ( getline (inventoryFile, buffer, ';') )
      {
         productType = buffer;

         getline (inventoryFile, buffer, ';');
         title = buffer;

         getline (inventoryFile, buffer, ';');
         author = buffer;

         getline (inventoryFile, buffer, ';');
         genre = buffer;
         Genre( bGenre, genre );

         getline (inventoryFile, buffer, ';');
         price = atof(buffer.c_str( ) );

		 getline(inventoryFile, buffer, ';');
		 ID = atoi(buffer.c_str());

         getline (inventoryFile, buffer, ';');
         quanity = atoi( buffer.c_str() );

         getline (inventoryFile, buffer, ';');
         isbn = atoi( buffer.c_str() );

         getline (inventoryFile, buffer, ';');
         publisher = buffer;

         if( productType == "Paper Book" )
         {
            getline (inventoryFile, buffer, '\n');
            pageCount = atoi( buffer.c_str() );
            AddToList( new PaperBook(productType, quanity, price, ID,
                                     isbn, author, title, bGenre,
                                     publisher, pageCount) );

         }
         else if( productType == "Audio Book" ){
            getline (inventoryFile, buffer, '\n');
            audioFormat = buffer;
            AudioFormat( abFormat, audioFormat );
            AddToList( new AudioBook(productType, quanity, price, ID,
                                     isbn, author, title, bGenre,
                                     publisher, abFormat) );

         }
         else if( productType == "eBook" ){
            getline (inventoryFile, buffer, '\n');
            ebookFormat = buffer;
            EbookFormat( ebFormat, ebookFormat );
            AddToList( new eBook(productType, quanity, price, ID, isbn,
                                 author, title, bGenre,
                                 publisher, ebFormat) );

         }else
            AddToList( NULL);
         
         ++ItemCount;
      }
      
      inventoryFile.close();

   }
   catch(string e)
   {

      throw;

   }
   
}

/*overwrties the templates RemoveFromList so it deletes the pointer as well*/
void InventoryList::RemoveFromList( Item* item )
{
   for (int i = 0; i < ItemList.size(); i++)
   {
      if (ItemList.at(i) == item)
         delete item;
         ItemList.erase(ItemList.begin() + i);
   }
}

vector<Item*> InventoryList::Search( string bookProperty )
{

   vector<Item*> temp;

   for( p = ItemList.begin(); p != ItemList.end(); p++ )
   {
      eBook * eb = dynamic_cast<eBook *>(*p);
      PaperBook * pb = dynamic_cast<PaperBook *>(*p);
      AudioBook * ab = dynamic_cast<AudioBook *>(*p);

      if( (eb && eb->getTitle() == bookProperty) || (eb && eb->getAuthor() == bookProperty) )
      {

         temp.push_back( eb );
         
      }
      else if( (pb && pb->getTitle() == bookProperty) || (pb && pb->getAuthor() == bookProperty) )
      {

         temp.push_back( pb );

      }
      else if( (ab && ab->getTitle() == bookProperty) || (ab && ab->getAuthor() == bookProperty) )
      {

         temp.push_back( ab );

      }

   }

   return temp;

}


Item * InventoryList::Search( int isbn )
{

   for( p = ItemList.begin(); p != ItemList.end(); p++ )
   {
      eBook * eb = dynamic_cast<eBook *>(*p);
      PaperBook * pb = dynamic_cast<PaperBook *>(*p);
      AudioBook * ab = dynamic_cast<AudioBook *>(*p);

      if( eb && eb->getISBN() == isbn )
      {

         return eb;

      }
      else if( pb && pb->getISBN() == isbn )
      {

         return pb;

      }
      else if( ab && ab->getISBN() == isbn )
      {

         return ab;
         
      }
      
   }
   
   return NULL;
   
}


Item * InventoryList::SearchID(int ID)
{

   for( p = ItemList.begin(); p != ItemList.end(); p++ )
   {
      eBook * eb = dynamic_cast<eBook *>(*p);
      PaperBook * pb = dynamic_cast<PaperBook *>(*p);
      AudioBook * ab = dynamic_cast<AudioBook *>(*p);

      if( eb && eb->GetID() == ID )
      {

         return eb;

      }
      else if( pb && pb->GetID() == ID )
      {

         return pb;

      }
      else if( ab && ab->GetID() == ID )
      {

         return ab;

      }
      
   }
   
   return NULL;
   
}


void InventoryList::Genre(genreType& bGenre, string identifier)
{
   if( identifier == "Science Fiction" )
      bGenre = SCIENCE_FICTION;
   else if( identifier == "Mystery" )
      bGenre = MYSTERY;
   else if( identifier == "Horror" )
      bGenre = HORROR;
   else if( identifier == "Romance" )
      bGenre = ROMANCE;
   else
      bGenre = UNKNOWN;
}


void InventoryList::AudioFormat(audioFileFormat& abFormat, string identifier)
{
   if( identifier == "MP3" )
      abFormat = MP3;
   else
      abFormat = UNKNOWN_AUDIO;
}


void InventoryList::EbookFormat(eBookFileFormat& ebFormat, string identifier)
{
   if( identifier == "PDF" )
      ebFormat = PDF;
   else if( identifier == "EPUB" )
      ebFormat = EPUB;
   else
      ebFormat = UNKNOWN_EBOOK;
}


void InventoryList::SetDatabasePath( string path )
{

   DatabasePath = path;

}


string InventoryList::GetDatabasePath() const
{

   return DatabasePath;
   
}


void InventoryList::DisplayList()
{

   for( p = ItemList.begin(); p != ItemList.end(); p++ )
   {
      eBook * eb = dynamic_cast<eBook *>(*p);
      PaperBook * pb = dynamic_cast<PaperBook *>(*p);
      AudioBook * ab = dynamic_cast<AudioBook *>(*p);

      if( eb )
      {

         cout << "\n" << *eb << "\n";

      }
      else if( pb )
      {

         cout << "\n" << *pb << "\n";

      }
      else if( ab )
      {

         cout << "\n" << *ab << "\n";
         
      }
   }

}




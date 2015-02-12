#include "Sublist.h"
#include "iTunes.h"

Sublist Sublist::addItem(int indexOfItemToAdd){
   Sublist augmentSublist = *this;
   augmentSublist.indices.push_back(indexOfItemToAdd);
   augmentSublist.sum = (*augmentSublist.originalObjects)[indexOfItemToAdd] + augmentSublist;
   
   return augmentSublist;
}

void Sublist::showSublist() const{
   cout << "Sublist -----------------------------" << endl;
   
   int sum = this->getSum();
   cout << "  sum: " << sum << endl;

   for (int i = 0; i < this->indices.size(); i++){
      iTunesEntry displayEntry = (*this->originalObjects)[indices[i]];
      cout << "array[" << i << "] = " << displayEntry << endl;
   }
}

ostream& operator<<(ostream& os, const iTunesEntry& ite){
   os << ite.getTitle() << " by "
      << ite.getArtist() << "("
      << ite.getTime() << ")";

   return os;
}

int operator+(const iTunesEntry& ite, Sublist existing){
   int newTime = 0;
   newTime = ite.getTime() + existing.getSum();

   return newTime;
}




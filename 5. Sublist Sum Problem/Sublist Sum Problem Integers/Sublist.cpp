#include "Sublist.h"

Sublist Sublist::addItem(int indexOfItemToAdd){
   Sublist augmentSublist = *this;
   augmentSublist.indices.push_back(indexOfItemToAdd);
   augmentSublist.sum += (*augmentSublist.originalObjects)[indexOfItemToAdd];
   return augmentSublist;
}

void Sublist::showSublist() const{
   cout << "Sublist -----------------------------" << endl;
   
   int sum = this->getSum();
   cout << "  sum: " << sum << endl;

   for (int i = 0; i < this->indices.size(); i++){
      int sublistOriginalObjects = (*this->originalObjects)[indices[i]];
      cout << "array[" << i << "] = " << sublistOriginalObjects << endl;
   }
}


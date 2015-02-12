/*
File names: Assignment_2_part_a.cpp, FHsparseMat.h, FHlist.h, FHvector.h, MatNode.h
Developer: Siddhanth Sabharwal
Program Purpose: This program creates, edits, and outputs a sparse matrix.
Program History:
Date       Version  ID    Description
1/19/2015  1.0      1000  Initial Creation
*/

#ifndef FHSPARSEMAT_H
#define FHSPARSEMAT_H
#define MAT_SIZE 100000

#include "FHlist.h"
#include "FHvector.h"
#include "MatNode.h"
#include <iostream>
#include <stdlib.h>
#include <float.h>
using namespace std;

template <class Object>
class SparseMat {
   // use protected, not private, in anticipation of a future subclass
protected:
   typedef FHlist< MatNode<Object> > MatRow;
   typedef FHvector<MatRow> MasterCol;
   MasterCol rows;
   Object defaultVal;
   int rowSize, colSize;

public:
   SparseMat(int r, int c, const Object& defaultVal2);
   const Object& get(int r, int c) const;
   bool set(int r, int c, const Object &x);
   void clear();
   void showSubSquare(int start, int size);
};

template <class Object>
SparseMat<Object>::SparseMat(int r, int c, const Object& defaultVal2) :rowSize(r), colSize(c), defaultVal(defaultVal2){
   rows.resize(r);
}

template <class Object>
const Object& SparseMat<Object>::get(int r, int c) const{
   if (r < 0 || r >= MAT_SIZE){
      throw "Your row index must be greater than or equal 0 and less than the MAT_SIZE.";
   }

   if (c < 0 || c >= MAT_SIZE){
      throw "Your column index must be greater than or equal 0 and less than the MAT_SIZE.";
   }

   typename MatRow::const_iterator const_itr = this->rows[r].begin();

   bool ifFound = false;
   for (; (*const_itr).getCol() != c, const_itr != this->rows[r].end(); const_itr++){
      ifFound = true;
      return (*const_itr).data;
   }

   if (ifFound == false){
      return defaultVal;
   }
}

template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x){
   if (r < 0 || r >= MAT_SIZE){
      return false;
   }

   if (c < 0 || c >= MAT_SIZE){
      return false;
   }

   typename MatRow::iterator itr = this->rows[r].begin();

   bool ifFound = false;
   for (; itr != this->rows[r].end(); itr++){
      if ((*itr).getCol() == c){
         if (x == defaultVal){
            this->rows[r].erase(itr);
            ifFound = true;
            return true;
         }
         else {
            (*itr).data = x;
            ifFound = true;
            return true;
         }
      }
   }

   if (ifFound == false){
      if (x == defaultVal){
         return true;
      }
      else{
         this->rows[r].push_back(MatNode<Object>(c, x));
         return true;
      }
   }
   return true;
}


template <class Object>
void SparseMat<Object>::clear(){
   for (int i = 0; i < rowSize; i++){
      for (typename MatRow::iterator itr = this->rows[i].begin(); itr != this->rows[i].end(); itr++){
         this->rows[i].erase(itr);
         break;
      }
   }
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size){
   for (int i = start; i <= (start + size - 1); i++){
      typename MatRow::iterator itr = this->rows[i].begin();
      for (int j = start; itr != this->rows[i].end(), j <= (start + size - 1); j++){
         if ((*itr).getCol() == j){
            cout << (*itr).data << "  ";
            itr++;
         }
         else{
            cout << "0  ";
         }
      }
      cout << endl;
   }
   cout << endl << endl;
}

#endif
#include <iostream>
#include <vector>
#include "iTunes.h"
using namespace std;

class Sublist{
public:
   Sublist(vector<iTunesEntry> *orig = NULL)
      : sum(0), originalObjects(orig) { }
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }
   friend ostream & operator<< (ostream& os, const iTunesEntry& ite);
   friend int operator+(const iTunesEntry& ite, Sublist existing);

private:
   int sum;
   vector<iTunesEntry> *originalObjects;
   vector<int> indices;
};
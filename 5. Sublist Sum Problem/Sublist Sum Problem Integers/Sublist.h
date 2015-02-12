#include <iostream>
#include <vector>
using namespace std;

class Sublist{
public:
   Sublist(vector <int> *orig = NULL)
      : sum(0), originalObjects(orig){};
   Sublist addItem(int indexOfItemToAdd);
   void showSublist() const;
   int getSum() const { return sum; }

private:
   int sum;
   vector <int> *originalObjects;
   vector <int> indices;
};
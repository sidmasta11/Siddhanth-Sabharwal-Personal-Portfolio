/*
Developer: Siddhanth Sabharwal
Program Purpose: This program finds a solution to the Subset Sum Problem.
Program History:
Date       Version  ID    Description
1/12/2015  1.0      1000  Initial Creation
*/

#include <iostream>
#include <vector>
#include "Sublist.h"
using namespace std;

int main(){
   int TARGET = 180;                   //TARGET can be changed based on result
   vector<int> dataSet;
   vector<Sublist> choices;
   vector<Sublist>::iterator iterBest;
   int k, j, l, numSets, max, masterSum, closestValue;
   bool foundPerfect = false, tester = false;

   //Values from which sublists are created
   dataSet.push_back(20); dataSet.push_back(12); dataSet.push_back(22);
   dataSet.push_back(15); dataSet.push_back(25);
   dataSet.push_back(19); dataSet.push_back(29);
   dataSet.push_back(18);
   dataSet.push_back(11); dataSet.push_back(13); dataSet.push_back(17);

   choices.clear();
   choices.push_back(Sublist(&dataSet));            //initializes choices Sublist vector
   
   cout << "Target time: " << TARGET << endl;       //Goal

   for (l = 0, max = 0; l < dataSet.size(); l++){
      max += dataSet[l];                            //Finds the sum of all values in dataSet vector
   }   

   if (TARGET > max){
      cout << "Target is too big, no solution found." << endl;      //checking to make sure there is a solution
      tester = false;
   }
   else{
      tester = true;
      for (k = 0; k < dataSet.size(); k++){
         numSets = choices.size();
         for (j = 0; j < numSets && foundPerfect != true; j++){             //checking to see if solution is found
            masterSum = choices[j].getSum() + dataSet[k];
            if (masterSum <= TARGET){
               choices.push_back(choices[j].addItem(k));
               foundPerfect = false;
            }
            if (masterSum == TARGET){
               foundPerfect = true;                             //if solution is found there is a break
               break;
            }
         }
      }
   }

   closestValue = choices[0].getSum();
   iterBest = choices.begin();
   for (j = 1; j < choices.size(); j++){
      if (choices[j].getSum() > closestValue){
         closestValue = choices[j].getSum();
         iterBest = choices.begin() + j;
      }
   }

   if (tester != false){
      iterBest->showSublist();
   }

   return 0;
}

/*-------------------------------RUNS-----------------------------------

Target time: 180
Sublist -----------------------------
sum: 179
array[0] = 20
array[1] = 12
array[2] = 15
array[3] = 25
array[4] = 19
array[5] = 29
array[6] = 18
array[7] = 11
array[8] = 13
array[9] = 17
Press any key to continue . . .


Target time: 48
Sublist -----------------------------
sum: 48
array[0] = 19
array[1] = 29
Press any key to continue . . .


Target time: 1000
Target is too big, no solution found.
Press any key to continue . . .




-----------------------------------------------------------------------------*/

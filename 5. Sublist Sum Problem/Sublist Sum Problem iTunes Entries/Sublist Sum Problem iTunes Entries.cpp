/*
Developer: Siddhanth Sabharwal
Program Purpose: This program finds a solution to the Subset Sum Problem for song lengths by seconds.
Text File Format:
#
Artist
Song
Length in Seconds
Example:
#
Carrie Underwood
Cowboy Casanova
236
Program History:
Date       Version  ID    Description
1/12/2015  1.0      1000  Initial Creation
*/

#include <iostream>
#include <vector>
#include "Sublist.h"
#include "iTunes.h"
using namespace std;

int main(){
   const int TARGET = 2400;
   vector<iTunesEntry> dataSet;
   vector<Sublist> choices;
   vector<Sublist>::iterator iterBest;
   int k, j, l, numSets, max, array_size, masterSum, closestValue;
   bool tester = false, foundPerfect = false;

   // read the data
   iTunesEntryReader tunes_input("itunes_file.txt");
   if (tunes_input.readError())
   {
      cout << "couldn't open " << tunes_input.getFileName()
         << " for input.\n";
      exit(1);
   }

   // time the algorithm -------------------------
   clock_t startTime, stopTime;
   startTime = clock();

   // create a vector of objects for our own use:
   array_size = tunes_input.getNumTunes();
   for (k = 0; k < array_size; k++)
      dataSet.push_back(tunes_input[k]);

   cout << "Target time: " << TARGET << endl;

   for (l = 0, max = 0; l < dataSet.size(); l++){
      max = max + dataSet[l].getTime();                            //Finds the sum of all values in dataSet vector
   }

   choices.push_back(Sublist(&dataSet));            //initializes choices Sublist vector

   if (TARGET > max){
      cout << "Target is too big, no solution found." << endl;      //checking to make sure there is a solution
      tester = false;
   }
   else{
      tester = true;
      for (k = 0; k < dataSet.size(); k++){
         numSets = choices.size();
         for (j = 0; j < numSets && foundPerfect != true; j++){             //checking to see if solution is found
            masterSum = dataSet[k] + choices[j];
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



   // how we determine the time elapsed -------------------
   stopTime = clock();
   // report algorithm time
   cout << "\nAlgorithm Elapsed Time: "
      << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
      << " seconds." << endl << endl;

   return 0;
}


/*-------------------------------RUNS-----------------------------------

Target time : 3600
Sublist---------------------------- -
sum : 3600
array[0] = Cowboy Casanova by Carrie Underwood(236)
array[1] = Quitter by Carrie Underwood(220)
array[2] = Russian Roulette by Rihanna(228)
array[3] = Monkey Wrench by Foo Fighters(230)
array[4] = Pretending by Eric Clapton(283)
array[5] = Bad Love by Eric Clapton(308)
array[6] = Everybody's In The Mood by Howlin' Wolf(178)
array[7] = Well That's All Right by Howlin' Wolf(175)
array[8] = Samson and Delilah by Reverend Gary Davis(216)
array[9] = Hot Cha by Roy Buchanan(208)
array[10] = Green Onions by Roy Buchanan(443)
array[11] = I'm Just a Prisoner by Janiva Magness(230)
array[12] = You Were Never Mine by Janiva Magness(276)
array[13] = Hobo Blues by John Lee Hooker(187)
array[14] = I Can't Quit You Baby by John Lee Hooker(182)

Algorithm Elapsed Time : 5.476 seconds.

Press any key to continue . . .

Target time: 2400
Sublist -----------------------------
sum: 2400
array[0] = Quitter by Carrie Underwood(220)
array[1] = Russian Roulette by Rihanna(228)
array[2] = Monkey Wrench by Foo Fighters(230)
array[3] = Bad Love by Eric Clapton(308)
array[4] = Everybody's In The Mood by Howlin' Wolf(178)
array[5] = Well That's All Right by Howlin' Wolf(175)
array[6] = Samson and Delilah by Reverend Gary Davis(216)
array[7] = Twelve Sticks by Reverend Gary Davis(194)
array[8] = Hot Cha by Roy Buchanan(208)
array[9] = Green Onions by Roy Buchanan(443)

Algorithm Elapsed Time: 0.345 seconds.

Press any key to continue . . .


Target time: 250000000
Target is too big, no solution found.

Algorithm Elapsed Time: 0.004 seconds.

Press any key to continue . . .


-----------------------------------------------------------------------------*/
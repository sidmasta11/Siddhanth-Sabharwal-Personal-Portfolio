/*
Developer: Siddhanth Sabharwal
Program Purpose: This program analyzes different shellsort gaps
both explicitly and implicitly.
Program History:
Date         Version  ID     Description
03/02/2015   1.0      3000   Initial Creation
*/

#include <iostream>
#include <time.h>
#include <math.h>
#include "FHvector.h"
using namespace std;

#define ARRAY_SIZE 200000

// ----------- prototypes -------------
template <typename Comparable>
void shellSort1(FHvector<Comparable> & a);
template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int arrayWithGaps[], int gapSize);
template <typename Comparable>
ostream& operator<< (ostream& out, const FHvector<Comparable> & a);

int main()
{
    int k, inputValue;
    FHvector<int> fhVectorOfInts1;
    FHvector<int> fhVectorOfInts2;
    FHvector<int> fhVectorOfInts3;
    FHvector<int> fhVectorOfInts4;

    int gapArray[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
        2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144, 524288,
        1048576 };
    // to be computed using formulas
    int sedgewickArray[28];  
    int pigeonArray[24];

    //build four vectors for comparing sorts
    for (k = 0; k < ARRAY_SIZE; k++){
        int value = rand() % ARRAY_SIZE;
        fhVectorOfInts1.push_back(value);
        fhVectorOfInts2.push_back(value);
        fhVectorOfInts3.push_back(value);
        fhVectorOfInts4.push_back(value);
    }

    //Sedgewick Array Algorithm
    for (inputValue = k = 0; k < 28; k++){
        if (k % 2 == 0)
            inputValue = 9 * pow(2, k) - 9 * pow(2, k / 2) + 1;
        else
            inputValue = 8 * pow(2, k) - 6 * pow(2, (k + 1) / 2) + 1;
        sedgewickArray[k] = inputValue;
    }

    //Pigeon Array Algorithm
    for (inputValue = k = 0; k < 24; k++){
        inputValue = round(1 + exp(k - 2));
        pigeonArray[k] = inputValue;
    }

    //Calculate sizes
    int gapArraySize = (sizeof gapArray / sizeof gapArray[0]);
    int sedgewickArraySize = (sizeof sedgewickArray / sizeof sedgewickArray[0]);
    int pigeonArraySize = (sizeof pigeonArray / sizeof pigeonArray[0]);

    clock_t startTime, stopTime;
    cout << "Array Size is: " << ARRAY_SIZE << endl;

    // << fhVectorOfInts1 << endl;
    startTime = clock();  // ------------------ start 
    shellSort1(fhVectorOfInts1);
    stopTime = clock();  // ---------------------- stop
    //cout << fhVectorOfInts1 << endl;
    cout << "Shell's implied gap sequence computation time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl;

    //cout << fhVectorOfInts2 << endl;
    startTime = clock(); //--------- start
    shellSortX(fhVectorOfInts2, gapArray, gapArraySize);
    stopTime = clock();
    // << fhVectorOfInts2 << endl;
    cout << "Shell's explicit gap sequence computation time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl;

    //cout << fhVectorOfInts3 << endl;
    startTime = clock(); //--------- start
    shellSortX(fhVectorOfInts3, sedgewickArray, sedgewickArraySize);
    stopTime = clock();
    //cout << fhVectorOfInts3 << endl;
    cout << "Sedgewick Array Algorithm Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl;

    //cout << fhVectorOfInts4 << endl;
    startTime = clock(); //--------- start
    shellSortX(fhVectorOfInts4, pigeonArray, pigeonArraySize);
    stopTime = clock();
    //cout << fhVectorOfInts4 << endl;
    cout << "Pigeon Array Algorithm Elapsed Time: "
        << (double)(stopTime - startTime) / (double)CLOCKS_PER_SEC
        << " seconds." << endl;

    return 0;
}

// shellSort #1 -- using shell's outer loop
template <typename Comparable>
void shellSort1(FHvector<Comparable> & a)
{
    int k, pos, arraySize, gap;
    Comparable tmp;

    arraySize = a.size();
    for (gap = arraySize / 2; gap > 0; gap /= 2)  // outer gap loop
        for (pos = gap; pos < arraySize; pos++)   // middle loop (outer of "insertion-sort")
        {
        tmp = a[pos];
        for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)   // inner loop
            a[k] = a[k - gap];
        a[k] = tmp;
        }
}

template <typename Comparable>
void shellSortX(FHvector<Comparable> & a, int arrayWithGaps[], int gapSize)
{
    int i, k, pos, arraySize, gap;
    Comparable tmp;
    arraySize = a.size();

    for (i = gapSize; i > 0; i--){
        gap = arrayWithGaps[i - 1];
        for (pos = gap; pos < arraySize; pos++){
            tmp = a[pos];
            for (k = pos; k >= gap && tmp < a[k - gap]; k -= gap)   // inner loop
                a[k] = a[k - gap];
            a[k] = tmp;
        }
    }
}

//Created for testing purposes, the lines that use this operator are commented out in main()
template <typename Comparable>
ostream& operator<< (ostream& out, const FHvector<Comparable> & a)
{
    for (int i = 0; i < a.size(); i++){
        out << a[i] << " ";
    }
    return out;
}

/*--------------------TESTS----------------------
Array Size is: 10000
Shell's implied gap sequence computation time: 0.025 seconds.
Shell's explicit gap sequence computation time: 0.057 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.02 seconds.
Pigeon Array Algorithm Elapsed Time: 0.021 seconds.
Press any key to continue . . .

Array Size is: 41666
Shell's implied gap sequence computation time: 0.142 seconds.
Shell's explicit gap sequence computation time: 0.488 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.097 seconds.
Pigeon Array Algorithm Elapsed Time: 0.104 seconds.
Press any key to continue . . .

Array Size is: 73332
Shell's implied gap sequence computation time: 0.269 seconds.
Shell's explicit gap sequence computation time: 1.155 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.177 seconds.
Pigeon Array Algorithm Elapsed Time: 0.193 seconds.
Press any key to continue . . .

Array Size is: 104998
Shell's implied gap sequence computation time: 0.424 seconds.
Shell's explicit gap sequence computation time: 1.754 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.263 seconds.
Pigeon Array Algorithm Elapsed Time: 0.278 seconds.
Press any key to continue . . .

Array Size is: 136664
Shell's implied gap sequence computation time: 0.543 seconds.
Shell's explicit gap sequence computation time: 2.454 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.35 seconds.
Pigeon Array Algorithm Elapsed Time: 0.383 seconds.
Press any key to continue . . .

Array Size is: 168330
Shell's implied gap sequence computation time: 0.76 seconds.
Shell's explicit gap sequence computation time: 3.51 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.434 seconds.
Pigeon Array Algorithm Elapsed Time: 0.468 seconds.
Press any key to continue . . .

Array Size is: 200000
Shell's implied gap sequence computation time: 0.931 seconds.
Shell's explicit gap sequence computation time: 3.986 seconds.
Sedgewick Array Algorithm Elapsed Time: 0.515 seconds.
Pigeon Array Algorithm Elapsed Time: 0.554 seconds.
Press any key to continue . . .
*/

/*--------------TABLE----------------------------------
Sequence Type     Shell's Implied     Shell's Explicit     Sedgewick     Pigeon
Array Size
1000               0.025 s             0.057 s              0.02 s       0.021 s
41666              0.142 s             0.488 s              0.097 s      0.104 s
73332              0.269 s             1.155 s              0.177 s      0.193 s
104998             0.424 s             1.754 s              0.263 s      0.278 s
136664             0.543 s             2.454 s              0.35 s       0.383 s
168330             0.76 s              3.51 s               0.434 s      0.468 s
200000             0.931 s             3.986 s              0.515 s      0.554 s
*/

/*------------QUESTIONS-----------------------------
1. Why does Shell's gap sequence implied by shellSort1() give a different timing result than the explicit array described above and passed to shellSortX()?

The Shell's gap sequence implied by shellSort1() gives a different timing result than the explicit array described above and passed to shellSortX() because
the two gap sequences are different.

2. Which is faster and why?

The Shell's gap sequence implied by shellSort1() is faster because:
If the ARRAY_SIZE is less than some of the values in the gapArray then you are going through the loops extra times 
and not doing anything, thus wasting time. On the other hand, shellSort1() immediately starts the gap size at 
ARRAY_SIZE/2 and doesn't waste iterations on values greater than that.

In fact when you make the ARRAY_SIZE = 1048576 (the biggest value in the gapArray) * 2 = 2097152, the results are basically the same:
Array Size is: 2097152
Shell's implied gap sequence computation time: 136.395 seconds.
Shell's explicit gap sequence computation time: 141.847 seconds.
Sedgewick Array Algorithm Elapsed Time: 7.338 seconds.
Pigeon Array Algorithm Elapsed Time: 8.018 seconds.
Press any key to continue . . .
*/
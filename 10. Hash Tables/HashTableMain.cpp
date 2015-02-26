/*
Developer: Siddhanth Sabharwal
Program Purpose: This program implements quadtric probing
with hash tables.
Program History:
Date       Version  ID    Description
2/24/2015  1.0      2000  Initial Creation
*/

#include <iostream>
#include "FHhashQPwFind.h"
using namespace std;

#define NUM_RANDOM_INDICES 25

// ----------- prototypes -------------
int getKey(const EBookEntry & item);
//string getKey( const EBookEntry & item);
int Hash(const EBookEntry & item);
int Hash(const string & key);
int Hash(int key);
void printEbook(const EBookEntry & item);

int main()
{
    //Test will be done on EBookEntry data
    EBookEntry book;
    // how we read the data from files
    EBookEntryReader bookInput("catalog-short4.txt");

    // how we test the success of the read:
    if (bookInput.readError()){
        cout << "couldn't open " << bookInput.getFileName() << " for input.\n";
        exit(1);
    }

    // we want two books to be identical in different ways:  ID or author
    EBookEntry::setSortType(EBookEntry::SORT_BY_ID);
    //EBookEntry::setSortType(EBookEntry::SORT_BY_CREATOR);

    // create a QP hash table of EBooks ...
    FHhashQPwFind<EBookEntry, int> hashTable; // for ID equality
    //FHhashQPwFind<EBookEntry, string> hashTable; // for any string equality

    // insert all books into the hash table (if SORT_BY_ID) or fewer (If SORT_BY_CREATOR) ...
    int numBooks = bookInput.getNumBooks();
    for (int i = 0; i < numBooks; i++){
        hashTable.insert(bookInput[i]);
    }

    // generate some random indices into the EBookEntryReader vector ...
    int randomIndices[NUM_RANDOM_INDICES];
    srand(time(NULL));
    for (int i = 0; i < NUM_RANDOM_INDICES; i++){
        int randomInteger = rand() % numBooks;
        randomIndices[i] = randomInteger;
    }

    cout << bookInput.getFileName() << endl;
    cout << numBooks << endl << endl;

    // display NUM_RANDOM_INDICES books from array ...
    cout << "BOOKS THAT HAVE BEEN RANDOMLY CHOSEN:" << endl;
    for (int i = 0; i < NUM_RANDOM_INDICES; i++){
        printEbook(bookInput[randomIndices[i]]);
    }

    // attempt to find on the selected key
    cout << endl << "The same random books from the hash table " << endl;
    for (int k = 0; k < NUM_RANDOM_INDICES; k++){
        try{
            book = hashTable.find(bookInput[randomIndices[k]].getETextNum());
            //book = hashTable.find( bookInput[ randomIndices[k] ].getCreator() );
            printEbook(book);
        }
        catch (...){
            cout << "no.  ";
        }
    }

    cout << endl << "------------TESTING FOR FAILURES------------" << endl;
    // test known failures exceptions:
    try{
        book = hashTable.find(-3);
        //book = hashTable.find( "Jack Kerouac" );
    }
    catch (...){
        cout << "not found." << endl;
    }

    // more failures
    try{
        book = hashTable.find(5000);
        //book = hashTable.find("Siddhanth Sabharwal");
    }
    catch (...){
        cout << "not found." << endl;
    }

    try{
        book = hashTable.find(0);
        //book = hashTable.find("Professor Anand");
    }
    catch (...){
        cout << "not found." << endl;
    }

    return 0;
}

// used for author equality
//string getKey( const EBookEntry & item )
//{
//return item.getCreator() ;
//}

// used for ID equality
int getKey(const EBookEntry & item)
{
    return item.getETextNum();
}

int Hash(const EBookEntry & item)
{
    return Hash(getKey(item));
}

int Hash(const string & key)
{
    unsigned int k, retVal = 0;

    for (k = 0; k < key.length(); k++)
        retVal = 37 * retVal + key[k];

    return retVal;
}

int Hash(int key)
{
    return key;
}

void printEbook(const EBookEntry & item)
{
    cout << "Creator: " << item.getCreator()
        << "     ID: " << item.getETextNum() << endl;
}

/*------------------------TEST WITH ID------------------------
catalog-short4.txt
4863

BOOKS THAT HAVE BEEN RANDOMLY CHOSEN:
Creator: Various     ID: 16028
Creator: Ludwig Salvator, Archduke of Austria, 1847-1915     ID: 26705
Creator: (no data found)     ID: 24798
Creator: Hancock, H. Irving (Harrie Irving), 1868-1922     ID: 10045
Creator: Vaknin, Samuel, 1961-     ID: 30154
Creator: Hooper, Mary, 1829-1904     ID: 29519
Creator: Project Gutenberg     ID: 200
Creator: Various     ID: 28423
Creator: Woodward, F. W. (Francis W.)     ID: 26354
Creator: Chambers, Robert W. (Robert William), 1865-1933     ID: 28295
Creator: Noah, M. M. (Mordecai Manuel), 1785-1851     ID: 29231
Creator: Sanderson, Robert Edward, 1828-1913     ID: 21881
Creator: Raine, William MacLeod, 1871-1954     ID: 26911
Creator: Trotter, James M., 1842-1892     ID: 28056
Creator: Various     ID: 30073
Creator: Cullum, Ridgwell, 1867-1943     ID: 29628
Creator: Shedlock, Marie L., 1854-1935     ID: 5957
Creator: (no data found)     ID: 25962
Creator: Various     ID: 28668
Creator: Curnick, Edward T.     ID: 20622
Creator: Sergeant, Adeline, 1851-1904     ID: 30110
Creator: Kipling, Rudyard, 1865-1936     ID: 26223
Creator: Donnell, Annie Hamilton, 1862-     ID: 27987
Creator: National Security Council (U.S.)     ID: 29186
Creator: Various     ID: 18223

The same random books from the hash table
Creator: Various     ID: 16028
Creator: Ludwig Salvator, Archduke of Austria, 1847-1915     ID: 26705
Creator: (no data found)     ID: 24798
Creator: Hancock, H. Irving (Harrie Irving), 1868-1922     ID: 10045
Creator: Vaknin, Samuel, 1961-     ID: 30154
Creator: Hooper, Mary, 1829-1904     ID: 29519
Creator: Project Gutenberg     ID: 200
Creator: Various     ID: 28423
Creator: Woodward, F. W. (Francis W.)     ID: 26354
Creator: Chambers, Robert W. (Robert William), 1865-1933     ID: 28295
Creator: Noah, M. M. (Mordecai Manuel), 1785-1851     ID: 29231
Creator: Sanderson, Robert Edward, 1828-1913     ID: 21881
Creator: Raine, William MacLeod, 1871-1954     ID: 26911
Creator: Trotter, James M., 1842-1892     ID: 28056
Creator: Various     ID: 30073
Creator: Cullum, Ridgwell, 1867-1943     ID: 29628
Creator: Shedlock, Marie L., 1854-1935     ID: 5957
Creator: (no data found)     ID: 25962
Creator: Various     ID: 28668
Creator: Curnick, Edward T.     ID: 20622
Creator: Sergeant, Adeline, 1851-1904     ID: 30110
Creator: Kipling, Rudyard, 1865-1936     ID: 26223
Creator: Donnell, Annie Hamilton, 1862-     ID: 27987
Creator: National Security Council (U.S.)     ID: 29186
Creator: Various     ID: 18223

------------TESTING FOR FAILURES------------
not found.
not found.
not found.
Press any key to continue . . .
*/

/*------------------------TEST WITH STRING---------------------
catalog-short4.txt
4863

BOOKS THAT HAVE BEEN RANDOMLY CHOSEN:
Creator: (no data found)     ID: 28351
Creator: Newell, Peter, 1862-1924     ID: 26271
Creator: Okakura, Kakuzo, 1862-1913     ID: 28911
Creator: Sylvester, Charles Herbert     ID: 11250
Creator: Altsheler, Joseph A. (Joseph Alexander), 1862-1919     ID: 25186
Creator: Bruno, Giordano, 1548-1600     ID: 19833
Creator: Birmingham, George A., 1865-1950     ID: 29533
Creator: Various     ID: 28135
Creator: Clontz, J.     ID: 4319
Creator: Merwin, Samuel, 1874-1936     ID: 28958
Creator: Seeley, Levi, 1847-1928     ID: 27963
Creator: Fletcher, J. S. (Joseph Smith), 1863-1935     ID: 26324
Creator: Crawford, F. Marion (Francis Marion), 1854-1909     ID: 26327
Creator: Saint-Sa├½ns, Camille, 1835-1921     ID: 16459
Creator: Vasari, Giorgio, 1511-1574     ID: 28421
Creator: Shea, Robert, 1933-1994     ID: 28438
Creator: Haslam, John, 1764-1844     ID: 27740
Creator: Ryder, Annie H     ID: 6636
Creator: Day, Holman, 1865-1935     ID: 24793
Creator: Vincent, Harl, 1893-1968     ID: 28883
Creator: Faguet, ├ëmile, 1847-1916     ID: 27368
Creator: Meredith, George, 1828-1909     ID: 28823
Creator: Thucydides, 455? BC-395 BC     ID: 26245
Creator: Keene, Louis     ID: 28964
Creator: Murphy, Arthur, 1727-1805     ID: 30271

The same random books from the hash table
Creator: (no data found)     ID: 28351
Creator: Newell, Peter, 1862-1924     ID: 26271
Creator: Okakura, Kakuzo, 1862-1913     ID: 28911
Creator: Sylvester, Charles Herbert     ID: 11250
Creator: Altsheler, Joseph A. (Joseph Alexander), 1862-1919     ID: 17677
Creator: Bruno, Giordano, 1548-1600     ID: 19833
Creator: Birmingham, George A., 1865-1950     ID: 24073
Creator: Various     ID: 28712
Creator: Clontz, J.     ID: 4319
Creator: Merwin, Samuel, 1874-1936     ID: 28958
Creator: Seeley, Levi, 1847-1928     ID: 27963
Creator: Fletcher, J. S. (Joseph Smith), 1863-1935     ID: 27965
Creator: Crawford, F. Marion (Francis Marion), 1854-1909     ID: 28600
Creator: Saint-Sa├½ns, Camille, 1835-1921     ID: 16459
Creator: Vasari, Giorgio, 1511-1574     ID: 28420
Creator: Shea, Robert, 1933-1994     ID: 28976
Creator: Haslam, John, 1764-1844     ID: 27740
Creator: Ryder, Annie H     ID: 6636
Creator: Day, Holman, 1865-1935     ID: 16631
Creator: Vincent, Harl, 1893-1968     ID: 29321
Creator: Faguet, ├ëmile, 1847-1916     ID: 27368
Creator: Meredith, George, 1828-1909     ID: 28823
Creator: Thucydides, 455? BC-395 BC     ID: 26245
Creator: Keene, Louis     ID: 28964
Creator: Murphy, Arthur, 1727-1805     ID: 30271

------------TESTING FOR FAILURES------------
not found.
not found.
not found.
Press any key to continue . . .
*/
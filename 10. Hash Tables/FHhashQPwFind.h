//File FhhasQpwFind.h
//Template Definitions for FHhashQPwFind
//Quadratic Probing Hash Tables with Find
#ifndef FHHASHQPWFIND_H
#define FHHASHQPWFIND_H
#include "FHhashQP.h"
#include "EBookEntry.h"
using namespace std;

//class derived from FHhashQP and takes a second type parameter
template <class Object, typename KeyType>
class FHhashQPwFind : public FHhashQP < Object >
{
public:
    const Object find(const KeyType & key);

protected:
    int myHashKey(const KeyType & key) const;
    int findPosKey(const KeyType & key) const;
};

//returns the found object, or throws a NotFoundException  if it isn't there
template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key)
{
    typename FHhashQP<Object>::HashEntry searchResult = this->mArray[findPosKey(key)];
    if (searchResult.state == ACTIVE)
        return searchResult.data;
    else
        throw typename FHhashQP<Object>::NotFoundException();
}

//a trivial modification to myHash() which uses the key rather than the object, to hash.
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType & key) const
{
    int hashVal;

    hashVal = Hash(key) % this->mTableSize;
    if (hashVal < 0)
        hashVal += this->mTableSize;

    return hashVal;
}

//a trivial modification to findPos() which uses the key rather than the object, to get a position.
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey(const KeyType & key) const
{
    int kthOddNum = 1;
    int index = myHashKey(key);

    while (this->mArray[index].state != EMPTY
        && getKey(this->mArray[index].data) != key){
        index += kthOddNum;  // k squared = (k-1) squared + kth odd #
        kthOddNum += 2;   // compute next odd #
        if (index >= mTableSize)
            index -= mTableSize;
    }

    return index;
}

#endif
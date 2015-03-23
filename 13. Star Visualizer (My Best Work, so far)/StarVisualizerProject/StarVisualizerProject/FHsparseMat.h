#ifndef FHSPARSEMAT_H
#define FHSPARSEMAT_H
#define MAT_SIZE 100000
//
#include "FHlist.h"
#include "FHvector.h"
#include "MatNode.h"

template <class Object>
class SparseMat
{
protected:
    typedef FHlist<MatNode<Object> > MatRow;
    typedef FHvector<MatRow> MasterCol;
    MasterCol rows;
    Object defaultVal;
    int rowSize, colSize;

public:
    SparseMat<Object>(int numRows, int numCols, const Object & defaultVal);
    const Object &get(int r, int c) const;
    bool set(int r, int c, const Object &x);
    MatNode<Object> & set(int r, int c);
    void clear();
    int getRowSize() { return rowSize; }
    int getColSize() { return colSize; }

    // show submatrix, square upper left (start, start)
    void showSubSquare(int start, int size);
    void showAll();
private:
    bool valid(int r, int c) const;

    class MatConstructorException { };
    class MatBoundsException { };
};

// basic set():
template <class Object>
bool SparseMat<Object>::set(int r, int c, const Object &x)
{
    typename MatRow::iterator iter, iterEnd;

    if (!valid(r, c))
        return false;

    iterEnd = rows[r].end();
    for (iter = rows[r].begin(); iter != iterEnd; iter++)
        if ((*iter).getCol() == c)
        {
        if (x == defaultVal)
            rows[r].erase(iter);
        else
            (*iter).data = x;
        return true;
        }

    // not found
    if (x != defaultVal)
        rows[r].push_back(MatNode<Object>(c, x));
    return true;
}

// extra credit set():
template <class Object>
MatNode<Object> & SparseMat<Object>::set(int r, int c)
{
    typename MatRow::iterator iter;

    if (!valid(r, c))
        throw MatBoundsException();

    for (iter = rows[r].begin(); iter != rows[r].end(); iter++)
        if ((*iter).getCol() == c)
            return *iter;

    // this is a mutator so add a default element anticipating a quick mutation
    rows[r].push_front(MatNode<Object>(c, defaultVal));
    iter = rows[r].begin();
    return *iter;
}

template <class Object>
SparseMat<Object>::SparseMat(int numRows, int numCols,
    const Object & defaultVal)
{
    int r;
    if (numRows < 1 || numCols < 1)
        throw MatConstructorException();
    rowSize = numRows;
    colSize = numCols;
    this->defaultVal = defaultVal;
    for (r = 0; r < rowSize; r++)
        rows.push_back(MatRow());   // push a blank row
}

template <class Object>
const Object &SparseMat<Object>::get(int r, int c) const
{
    typename MatRow::const_iterator iter, iterEnd;

    if (!valid(r, c))
        throw MatBoundsException();

    iterEnd = rows[r].end();
    for (iter = rows[r].begin(); iter != iterEnd; iter++)
        if ((*iter).getCol() == c)
            return (*iter).data;
    // not found
    return defaultVal;
}

template <class Object>
void SparseMat<Object>::clear()
{
    int r;

    for (r = 0; r < rowSize; r++)
        rows[r].clear();
}

template <class Object>
bool SparseMat<Object>::valid(int r, int c) const
{
    if (r >= 0 && r < rowSize && c >= 0 && c < colSize)
        return true;
    return false;
}

template <class Object>
void SparseMat<Object>::showSubSquare(int start, int size)
{
    int r, c;

    if (start < 0 || size < 0
        || start + size > rowSize
        || start + size > colSize)
        return;

    for (r = start; r < start + size; r++)
    {
        for (c = start; c < start + size; c++)
        {
            cout.width(2);
            cout.precision(2);
            cout << get(r, c) << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

template <class Object>
void SparseMat<Object>::showAll()
{
    int r, c;

    if (rowSize < 0 || colSize < 0)
        return;

    for (r = 0; r < rowSize; r++){
        for (c = 0; c < colSize; c++){
            cout << get(r, c);
        }
        cout << endl;
    }
    cout << endl << endl;
}

#endif
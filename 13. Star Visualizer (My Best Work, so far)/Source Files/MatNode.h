#ifndef MATNODE_H
#define MATNODE_H

template <class Object>
class MatNode
{
protected:
    int col;

public:
    Object data;
    // we need a default constructor for lists
    MatNode(int cl = 0, Object dt = Object()) : col(cl), data(dt) {}
    MatNode(Object dt) : col(-1), data(dt) {}
    int getCol() const { return col; }

    // not optimized yet for set() = defaultVal;  partial solution to
    // extra credit that does not correctly handle that one case
    const Object & operator=(const Object &x) { return (data = x); }
    bool operator==(const MatNode &x) const
    {
        return (data == x.data);
    }
    bool operator!=(const MatNode &x) const
    {
        return (data != x.data);
    }
    friend ostream& operator<<(ostream& os, const MatNode& mn)
    {
        os << mn.data;
        return os;
    }
};

#endif

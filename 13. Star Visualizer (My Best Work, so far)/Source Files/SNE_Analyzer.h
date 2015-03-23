#ifndef SNE_ANALYZER_H
#define SNE_ANALYZER_H

#include "StarNearEarth.h"

class SNE_Analyzer : public StarNearEarth
{
private:
    double x, y, z;

public:
    void calcCartCoords();
    double getX() { return x; }
    double getY() { return y; }
    double getZ() { return z; }
    string coordToString();
    SNE_Analyzer & operator=(const StarNearEarth &sne);
};

#endif
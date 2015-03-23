#include "SNE_Analyzer.h"
#define _USE_MATH_DEFINES
#include<math.h>
#include<string>
using namespace std;

void SNE_Analyzer::calcCartCoords()
{
    double ly = 3.262 / getParallaxMean();
    double rarad = getRAsc()*M_PI / 180;
    double decrad = getDec()*M_PI / 180;
    x = ly*cos(decrad)*cos(rarad);
    y = ly*cos(decrad)*sin(rarad);
    z = ly*sin(decrad);
}

string SNE_Analyzer::coordToString()
{
    string stringX = to_string(x);
    string stringY = to_string(y);
    string stringZ = to_string(z);
    return "(" + stringX + "," + stringY + "," + stringZ + ")";
}

SNE_Analyzer & SNE_Analyzer::operator=(const StarNearEarth &sne)
{

    setRank(sne.getRank());
    setNameCns(sne.getNameCns());
    setNumComponents(sne.getNumComponents());
    setNameLhs(sne.getNameLhs());
    setRAsc(sne.getRAsc());
    setDec(sne.getDec());
    setPropMotionMag(sne.getPropMotionMag());
    setPropMotionDir(sne.getPropMotionDir());
    setParallaxMean(sne.getParallaxMean());
    setParallaxVariance(sne.getParallaxVariance());
    setWhiteDwarfFlag(sne.getWhiteDwarfFlag());
    setSpectralType(sne.getSpectralType());
    setMagApparent(sne.getMagApparent());
    setMagAbsolute(sne.getMagAbsolute());
    setMass(sne.getMass());
    setNotes(sne.getNotes());
    setNameCommon(sne.getNameCommon());
    calcCartCoords();

    return *this;
}
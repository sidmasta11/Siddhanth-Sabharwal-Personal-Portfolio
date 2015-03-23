/*
Developer: Siddhanth Sabharwal
Program Purpose: This program creates a star map
using sparse matrices.
Program History:
Date        Version  ID    Description
03/17/2015  1.0      5000  Initial Creation
*/

#include <iostream>
#include "StarNearEarth.h"
#include "SNE_Analyzer.h"
#include "FHsparseMat.h"
using namespace std;

typedef SparseMat<MatNode <char> > SpMat;

int main()
{
    int k, arraySize;
    StarNearEarthReader starInput("nearest_stars.txt");

    if (starInput.readError()){
        cout << "couldn't open " << starInput.getFileName() << " for input.\n";
        exit(1);
    }

    cout << starInput.getFileName() << endl;
    cout << starInput.getNumStars() << endl;

    //create an array of objects for our own use:
    arraySize = starInput.getNumStars();
    SNE_Analyzer *starArray = new SNE_Analyzer[arraySize];
    for (k = 0; k < arraySize; k++)
        starArray[k] = starInput[k];

    // display cartesion coords
    for (int k = 0; k < arraySize; k++)
        cout << starArray[k].getNameCommon() << " "
        << starArray[k].coordToString() << endl;

    //plotting stars

    //minimum and maximum for x, y, z coordinates
    double xMin = starArray[0].getX();
    double xMax = xMin;
    double yMin = starArray[0].getY();
    double yMax = yMin;
    double zMin = starArray[0].getZ();
    double zMax = zMin;
    for (k = 1; k < arraySize; k++){
        if (starArray[k].getX() < xMin)
            xMin = starArray[k].getX();
        if (starArray[k].getX() > xMax)
            xMax = starArray[k].getX();
        if (starArray[k].getY() < yMin)
            yMin = starArray[k].getY();
        if (starArray[k].getY() > yMax)
            yMax = starArray[k].getY();
        if (starArray[k].getZ() < zMin)
            zMin = starArray[k].getZ();
        if (starArray[k].getZ() > zMax)
            zMax = starArray[k].getZ();
    }

    //ranges for coordinates
    double xRange = xMax - xMin;
    double yRange = yMax - yMin;
    double zRange = zMax - zMin;

    //constants for aspect ratio
    const double NUM_ROWS = 36.0;
    const double NUM_COLS = 72.0;

    //sparse matrix with blank default character
    SpMat starMap(NUM_ROWS, NUM_COLS, ' ');

    //X-Y projection
    cout << endl << endl <<
        "---------X-Y projection---------" << endl
        << "-----------------------------" << endl;

    double xScale = xRange / NUM_ROWS;
    double yScale = yRange / NUM_COLS;
    starMap.set(NUM_ROWS / 2, NUM_COLS / 2, 'S');       //set sun in middle

    for (int j = 0; j < NUM_COLS - 1; j++){
        double xCoordinate = starArray[j].getX();     //getting X coordinates
        double yCoordinate = starArray[j].getY();     //getting Y coordinates
        char mark = '*';
        if (starArray[j].getRank() < 10)
            mark = '0' + starArray[j].getRank();

        //scale using mins, ranges, and NUM_ROW/COLs
        int roundXCoordinate = round((xCoordinate - xMin) / xScale); //casting into ints
        int roundYCoordinate = round((yCoordinate - yMin) / yScale); //casting into ints
        if (starMap.get(roundXCoordinate, roundYCoordinate) == ' ')
            starMap.set(roundXCoordinate, roundYCoordinate, mark);

    }

    //map is plotted
    starMap.showAll();
    starMap.clear();

    //X-Z projection

    cout << endl << endl <<
        "---------X-Z projection---------" << endl
        << "-----------------------------" << endl;

    xScale = xRange / NUM_ROWS;
    double zScale = zRange / NUM_COLS;
    starMap.set(NUM_ROWS / 2, NUM_COLS / 2, 'S');       //set sun in middle
    for (int i = 0; i < NUM_COLS - 1; i++)
    {
        double xCoordinate = starArray[i].getX();
        double zCoordinate = starArray[i].getZ();
        char mark = '*';
        if (starArray[i].getRank() < 10)
            mark = '0' + starArray[i].getRank();

        int roundXCoordinate = round((xCoordinate - xMin) / xScale);
        int roundZCoordinate = round((zCoordinate - zMin) / zScale);
        if (starMap.get(roundXCoordinate, roundZCoordinate) == ' ')
            starMap.set(roundXCoordinate, roundZCoordinate, mark);
    }

    starMap.showAll();
    starMap.clear();

    //Y-Z projection

    cout << endl << endl <<
        "---------Y-Z projection---------" << endl
        << "-----------------------------" << endl;

    yScale = yRange / NUM_ROWS;
    zScale = zRange / NUM_COLS;
    starMap.set(NUM_ROWS / 2, NUM_COLS / 2, 'S');       //set sun in middle
    for (int i = 0; i < NUM_COLS - 1; i++)
    {
        double yCoordinate = starArray[i].getY();
        double zCoordinate = starArray[i].getZ();
        char mark = '*';
        if (starArray[i].getRank() < 10)
            mark = '0' + starArray[i].getRank();

        int roundYCoordinate = round((yCoordinate - yMin) / yScale);
        int roundZCoordinate = round((zCoordinate - zMin) / zScale);
        if (starMap.get(roundYCoordinate, roundZCoordinate) == ' ')
            starMap.set(roundYCoordinate, roundZCoordinate, mark);
    }

    starMap.showAll();

    delete[] starArray;

    return 0;
}

/*--------------------------------------------RUN------------------------------------------------------
nearest_stars.txt
100
Proxima Centauri (-1.546293,-1.183478,-3.769340)
Barnard's Star (-0.056838,-5.943387,0.487961)
Wolf 359 (-7.430334,2.113549,0.950536)
Lalande 21185 (-6.506375,1.642238,4.870046)
Sirius (-1.609060,8.062019,-2.468945)
BL Ceti (7.540929,3.477280,-2.690181)
Ross 154 (1.910240,-8.648079,-3.912869)
Ross 248 (7.380606,-0.583729,7.193456)
epsilon Eridani (6.213068,8.315009,-1.729235)
Lacaille 9352 (8.465653,-2.037633,-6.292257)
Ross 128 (-10.903230,0.583818,-0.153313)
EZ Aquarii A (10.189198,-3.781402,-2.973612)
Procyon (-4.767961,10.306803,1.038493)
61 Cygni A (6.475334,-6.096803,7.137945)
(no common name) (1.081439,-5.726322,9.944846)
GX Andromedae (8.332564,0.669751,8.079118)
epsilon Indi A (5.656768,-3.156226,-9.893750)
DX Cancri (-6.421589,8.382023,5.328466)
tau Ceti (10.272825,5.014184,-3.264361)
Henry et al. 1997, Henry et al. 2006 (5.026663,6.918290,-8.407314)
YZ Ceti (11.027577,3.610227,-3.547300)
Luyten's Star (-4.584121,11.430974,1.126434)
Henry et al. 2006 (8.722794,8.206661,3.634488)
Henry et al. 2006 (1.078743,-5.412305,-11.296783)
Kapteyn's Star (1.890522,8.832912,-9.038744)
AX Microscopii (7.599337,-6.533289,-8.077083)
Kruger 60 A (6.468808,-2.746124,11.114720)
Jao et al. 2005, Costa et al. 2005 (-9.606479,3.109984,-8.453179)
Ross 614 A (-1.705263,13.224663,-0.655389)
Wolf 1061 (-5.144192,-12.465562,-3.029767)
van Maanen's Star (13.684420,2.981497,1.321096)
(no common name) (11.309459,0.266851,-8.635852)
Wolf 424 A (-13.987421,-2.045946,2.244233)
TZ Arietis (12.235161,7.079642,3.277077)
(no common name) (-0.560574,-5.431906,13.749622)
(no common name) (-13.811689,4.473702,-2.910823)
(no common name) (-1.379413,-10.026031,-10.813192)
G 208-044 A (5.045035,-9.301152,10.367499)
WD 1142-645 (-6.390851,0.398859,-13.633229)
(no common name) (15.175611,0.445762,-2.009403)
Ross 780 (14.245303,-4.268489,-3.780531)
Henry et al. 2006 (-7.112606,2.436807,-13.681678)
(no common name) (-11.156735,2.705454,10.904347)
(no common name) (-9.167211,4.702798,12.043870)
(no common name) (-13.578457,6.360132,5.418779)
(no common name) (8.470209,-6.292444,-12.142197)
(no common name) (7.589388,10.797271,-9.388863)
Costa et al. 2005 (7.976259,7.639721,-11.850010)
(no common name) (-1.168028,-11.631093,-11.415034)
omicron 2 Eridani (7.168128,14.579067,-2.182907)
EV Lacertae (11.186274,-3.697972,11.510862)
70 Ophiuchi A (0.395798,-16.625700,0.726099)
Altair (7.683131,-14.636794,2.579289)
EI Cancri (-11.266125,11.439670,5.768433)
Henry et al. 2006 (-0.004344,17.065735,0.806790)
Henry et al. 2006 (4.317461,16.681370,-2.099341)
(no common name) (-3.437097,0.184793,17.211934)
Wolf 498 (-15.324284,-7.617878,4.550749)
(no common name) (11.711376,-12.498643,-5.228329)
Stein 2051 (3.516778,8.617243,15.475899)
(no common name) (-3.598093,14.755305,9.964317)
(no common name) (2.400166,-15.313299,10.065343)
Wolf 1453 (2.308490,18.439631,-1.194327)
(no common name) (8.137112,16.558068,-3.114971)
sigma Draconis (2.561450,-6.008141,17.619822)
(no common name) (-0.806496,17.463344,-7.015201)
(no common name) (-0.600820,-10.241262,-15.991598)
Wolf 1055 (6.257114,-17.937319,1.718493)
Ross 47 (1.454069,18.636838,4.140631)
(no common name) (-12.781470,-12.501982,-7.012379)
Jao et al. 2005 (4.665867,-12.681454,-13.778124)
(no common name) (19.319468,-0.910379,0.811000)
eta Cassiopei A (10.083004,2.194072,16.395923)
(no common name) (-8.752301,-11.637394,-12.781419)
(no common name) (18.602830,1.257477,-5.393633)
Ross 882 (-8.569699,17.440895,1.206420)
36 Ophiuchi A (-3.370801,-17.082462,-8.720265)
(no common name) (8.635601,-13.400044,-11.625293)
82 Eridani (9.286259,11.059744,-13.499667)
(no common name) (-0.336453,-6.480310,18.712521)
delta Pavonis (4.283820,-6.807420,-18.220683)
QY Aurigae A (-4.711636,14.936582,12.471334)
HN Librae (-15.287629,-12.190854,-4.341807)
(no common name) (-14.172527,10.149651,9.869267)
(no common name) (-9.147653,8.066160,16.001816)
(no common name) (7.870211,-11.903001,-14.351474)
Wolf 562 (-13.081362,-15.513540,-2.751690)
EQ Pegasi (19.296400,-2.380411,7.052438)
Henry et al. 2006 (-13.672346,13.625497,7.734029)
Henry et al. 2006 (-16.076443,-2.749320,-12.918523)
(no common name) (-3.023791,-14.266115,14.925990)
(no common name) (-13.199350,-12.818077,-9.850687)
(no common name) (-5.968151,-14.643988,13.681141)
WD 0552-041 (0.443079,20.984734,-1.530829)
Wolf 630 A (-5.786061,-20.006955,-3.051816)
(no common name) (11.289693,-2.333702,17.866835)
Jao et al. 2005 (-6.342217,4.327448,-19.882306)
GL Virginis (-20.861352,-1.733903,4.116539)
(no common name) (-5.029564,-11.486251,17.452763)
Ross 104 (-19.340642,5.175828,8.429745)


---------X-Y projection---------
-----------------------------





*
*          *
*                                *

*   *              *
* *

3
* 4           *
*                                       *
*     *
*
*              1               5        *
* *        *         S                             *
*                  2                                       *
7    **                        *                *
*                *                                          *
*
*     *                           *                *
*                   *     *                   9
*         8      6            *      *
*              *       *   *            *              *
*
*               *
*               *      *    *
*
*           *
*







---------X-Z projection---------
-----------------------------





*
*        *
*                      *

*          *        *
*                                      *

*                          3
*                                 4*
*       *
*                *
*
*            1 5   *
*        *       *           S                          *
2*
*   *         7              *          *
*                    *             *
*
*         *           *                      *
*              9     *         *       *
* *         6*                 8
**         *     *          *         *
*
**
*     *  *                            *
*
*         *
*







---------Y-Z projection---------
-----------------------------


*
*
*
*
*
*       *  *   *

*         *                                      *
7
*
*       *               2           *                   *
*                                       *      *
* *                          *
*                                      *
*               *
1                    8
*        *           *  S*              *                *
3      4
*        *                  *                *
* 6
*                            *
*
*     *                     *
*           5 9         *  *                  *

*                  *
*        *
*
*
*
* *
*              *
*         *



Press any key to continue . . .
*/
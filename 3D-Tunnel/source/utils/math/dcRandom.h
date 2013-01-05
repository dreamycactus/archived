////////////////////////////////////////////////////////////////////////////////
/**
 * \file    dcRandom.h
 * \author  Hua Fei Yu 0951402
 * \date    Nov 13, 2011
 * \brief   Random class
 */
////////////////////////////////////////////////////////////////////////////////
// Include Guard
#ifndef DCRANDOM_H
#define DCRANDOM_H

#include <time.h>
#include <cstdlib>

class dcRandom
{
    public:
        static void init()                              { srand(time(0)); }
        static int randInt(int min, int max)            { return rand() % (max-min+1) + min; }
        static float randFloat(float min, float max)    { return min + ((max-min) * rand()) / (RAND_MAX + 1.0);}
};

#endif // DCRANDOM_H

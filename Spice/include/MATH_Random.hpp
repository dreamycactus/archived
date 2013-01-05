#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <ctime>

namespace MATH
{
    inline  void InitRandSeed()
    { srand(time(0)); }
    inline int RandInt(int min, int max)
    { return rand() % (max-min+1) + min; }
    inline float RandFloat(float min, float max)
    { return min + ((max-min) * rand()) / (RAND_MAX + 1.0);}
}

#endif // RANDOM_H

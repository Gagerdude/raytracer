#ifndef PERLIN_H
#define PERLIN_H

#include "vec3.h"

class Perlin{
    public:
        double noise(const vec3& p) const;

        static double* randouble;
        static int* perm_x;
        static int* perm_y;
        static int* perm_z;
};

#endif
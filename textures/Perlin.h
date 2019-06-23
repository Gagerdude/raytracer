#ifndef PERLIN_H
#define PERLIN_H

#include "vec3.h"

class Perlin{
    public:
        Perlin();
        ~Perlin();
        double noise(const vec3& p) const;
        double turbulence(vec3 p, int depth = 7) const;

    private:
        vec3* ranvec;
        int* perm_x;
        int* perm_y;
        int* perm_z;

        vec3* perlin_generate();
        void permute(int* array, int array_size);
        int* perlin_generate_permutation();
};

#endif
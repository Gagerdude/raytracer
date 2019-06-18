#ifndef TEXTURE_H
#define TEXTURE_H

#include "../engine/vec3.h"

class Texture{
    public:
        virtual ~Texture() {}
        virtual vec3 value(double u, double v, const vec3& p) const = 0;
};

#endif
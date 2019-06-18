#ifndef CONSTANT_TEXTURE_H
#define CONSTANT_TEXTURE_H

#include "Texture.h"

class ConstantTexture: public Texture{
    public:
        ConstantTexture();
        ConstantTexture(const vec3& c);

        virtual vec3 value(double u, double v, const vec3& p) const;

    private:
        vec3 color;
};

#endif
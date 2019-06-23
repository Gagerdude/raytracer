#ifndef NOISETEXTURE_H
#define NOISETEXTURE_H

#include "Texture.h"
#include "Perlin.h"

class NoiseTexture: public Texture{
    public:
        NoiseTexture();
        
        virtual vec3 value(double u, double v, const vec3& p) const;

    private:
        Perlin noise;
};

#endif
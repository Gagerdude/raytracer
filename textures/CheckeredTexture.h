#ifndef CHECKERED_TEXTURE_H
#define CHECKERED_TEXTURE_H

#include "Texture.h"

class CheckeredTexture: public Texture{
    public:
        CheckeredTexture(Texture* t1, Texture* t2);
        ~CheckeredTexture();

        virtual vec3 value(double u, double v, const vec3& p) const;

    private:
        Texture* even;
        Texture* odd;
};

#endif
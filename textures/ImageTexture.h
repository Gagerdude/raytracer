#ifndef IMAGETEXTURE_H
#define IMAGETEXTURE_H

#include "Texture.h"
#include "ImageWrapper.h"

class ImageTexture: public Texture{
    public:
        ImageTexture();
        ImageTexture(const ImageWrapper<unsigned char>& img);
        
        virtual vec3 value(double u, double v, const vec3& p) const;

    private:
        ImageWrapper<unsigned char> image;
};

#endif
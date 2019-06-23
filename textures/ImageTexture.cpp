#include "ImageTexture.h"

ImageTexture::ImageTexture(){
    
}

ImageTexture::ImageTexture(const ImageWrapper<unsigned char>& img){
    image = img;
}

vec3 ImageTexture::value(double u, double v, const vec3& p) const{
    int i = u * image.x();
    int j = (1 - v) * image.y();

    if(i < 0){
        i = image.x() - (std::abs(i) % image.x());
    } else {
        i = i % image.x();
    }

    if(j < 0){
        j = image.y() - (std::abs(j) % image.y());
    } else {
        j = j % image.y();
    }

    return vec3(image.get(i, j, 0) / 255.0, image.get(i, j, 1) / 255.0, image.get(i, j, 2) / 255.0);
}
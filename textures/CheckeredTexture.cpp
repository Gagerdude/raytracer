#include "CheckeredTexture.h"

#include <cmath>

CheckeredTexture::~CheckeredTexture(){
    delete even;
    delete odd;
}

CheckeredTexture::CheckeredTexture(Texture* t1, Texture* t2){
    even = t1;
    odd = t2;
}

vec3 CheckeredTexture::value(double u, double v, const vec3& p) const{
    double sine = std::sin(10*p.x()) * std::sin(10*p.y()) * std::sin(10*p.z());

    if(sine < 0){
        return odd->value(u, v, p);
    } else {
        return even->value(u, v, p);
    }
}
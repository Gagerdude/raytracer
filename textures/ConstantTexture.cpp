#include "ConstantTexture.h"

ConstantTexture::ConstantTexture(){

}

ConstantTexture::ConstantTexture(const vec3& c){
    color = c;
}

vec3 ConstantTexture::value(double u, double v, const vec3& p) const{
    return color;
}
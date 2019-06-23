#include "NoiseTexture.h"

NoiseTexture::NoiseTexture(){
    
}

vec3 NoiseTexture::value(double u, double v, const vec3& p) const{
    return vec3(1) * noise.noise(p);
}
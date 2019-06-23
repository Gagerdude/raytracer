#include "NoiseTexture.h"

NoiseTexture::NoiseTexture(double scale_in){
    scale = scale_in;
}

vec3 NoiseTexture::value(double u, double v, const vec3& p) const{
    return vec3(.5) * (1 + std::sin(scale * p.z() + 10 * noise.turbulence(p)));
}
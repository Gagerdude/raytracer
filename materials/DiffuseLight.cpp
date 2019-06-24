#include "DiffuseLight.h"
DiffuseLight::DiffuseLight(Texture* a){
    emit = a;
}

DiffuseLight::~DiffuseLight(){
    delete emit;
}

bool DiffuseLight::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    return false;
}

vec3 DiffuseLight::emitted(float u, float v, const vec3& p) const{
    return emit->value(u, v, p);
}

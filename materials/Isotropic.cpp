#include "Isotropic.h"

Isotropic::Isotropic(Texture* albedo){
    m_albedo = albedo;
}

Isotropic::~Isotropic(){
    delete m_albedo;
}

bool Isotropic::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    ray_scattered = Ray(rec.p, vec3::random(), ray_in.time());
    attenuation = m_albedo->value(rec.u, rec.v, rec.p);

    return true;    
}

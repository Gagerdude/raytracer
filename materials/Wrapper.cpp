#include "Wrapper.h"

Wrapper::Wrapper(Material* material){
    m_material = material;
}

bool Wrapper::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    return m_material->scatter(ray_in, rec, attenuation, ray_scattered);
}

vec3 Wrapper::emitted(float u, float v, const vec3& p) const{
    return m_material->emitted(u, v, p);
}

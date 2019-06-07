#include "Dielectric.h"

Dielectric::Dielectric(double ri){
    refractive_index = ri;
}

bool Dielectric::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    vec3 outward_normal;
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    float refl_index;
    attenuation = vec3(1.0);
    vec3 refracted;
    if(dot(ray_in.direction(), rec.normal) > 0){
        outward_normal = -rec.normal;
        refl_index = refractive_index;
    } else {
        outward_normal = rec.normal;
        refl_index = 1.0 / refractive_index;
    }
    if(refract(ray_in.direction(), outward_normal, refl_index, refracted)){
        ray_scattered = Ray(rec.p, refracted);
        return true;
    } else {
        ray_scattered = Ray(rec.p, reflected);
        return false;
    }
}
    
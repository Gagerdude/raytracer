#include "Lambertian.h"

Lambertian::Lambertian(const vec3& a){
    albedo = a;
}

bool Lambertian::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    vec3 target = rec.p + rec.normal + vec3::random();
    ray_scattered = Ray(rec.p, target - rec.p);
    attenuation = albedo;
    return true;
}
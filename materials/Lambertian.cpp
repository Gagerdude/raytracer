#include "Lambertian.h"

Lambertian::Lambertian(Texture* a){
    albedo = a;
}

Lambertian::~Lambertian(){
    delete albedo;
}

bool Lambertian::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    vec3 target = rec.p + rec.normal + vec3::random();
    ray_scattered = Ray(rec.p, target - rec.p, ray_in.time());
    attenuation = albedo->value(0, 0, rec.p);
    return true;
}
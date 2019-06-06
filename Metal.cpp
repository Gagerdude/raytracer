#include "Metal.h"

Metal::Metal(const vec3& a){
    albedo = a;
}

bool Metal::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    ray_scattered = Ray(rec.p, reflected);
    attenuation = albedo;
    return dot(ray_scattered.direction(), rec.normal) > 0;
}
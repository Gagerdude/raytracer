#include "Metal.h"

Metal::Metal(const vec3& a, double f){
    albedo = a;
    if(f > 1){
        fuzz = 1;
    } else {
        fuzz = f;
    }
}

bool Metal::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    ray_scattered = Ray(rec.p, reflected + fuzz * vec3::random(), ray_in.time());
    attenuation = albedo;
    return dot(ray_scattered.direction(), rec.normal) > 0;
}
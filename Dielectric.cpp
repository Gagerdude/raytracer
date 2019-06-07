#include "Dielectric.h"

#include "Raytracer.h"

#include <random>
#include <cmath>

Dielectric::Dielectric(double ri){
    refractive_index = ri;
}

double schlick(double cos, double refractive_index){
    double r = (1 - refractive_index) / (1 + refractive_index);
    r = r * r;
    return r + (1 - r) * std::pow((1 - cos), 5);
}

bool Dielectric::scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const{
    vec3 outward_normal;
    vec3 reflected = reflect(ray_in.direction(), rec.normal);
    double ref_index;
    attenuation = vec3(1.0);
    vec3 refracted;
    double reflect_prob;
    double cos;

    if(dot(ray_in.direction(), rec.normal) > 0){
        outward_normal = -rec.normal;
        ref_index = refractive_index;
        cos = refractive_index * dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
    } else {
        outward_normal = rec.normal;
        ref_index = 1.0 / refractive_index;
        cos = -dot(ray_in.direction(), rec.normal) / ray_in.direction().length();
    }
    
    if(refract(ray_in.direction(), outward_normal, ref_index, refracted)){
        reflect_prob = schlick(cos, refractive_index);
    } else {
        reflect_prob = 1.0;
    }

    std::uniform_real_distribution<double> dist;
    if(dist(Raytracer::rng) < reflect_prob){
        ray_scattered = Ray(rec.p, reflected);
    } else {
        ray_scattered = Ray(rec.p, refracted);
    }
    return true;
}
    
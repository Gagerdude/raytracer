#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "Material.h"

class Lambertian: public Material {
    public:
        Lambertian(const vec3& a);
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
    
    private:
        vec3 albedo;
};

#endif
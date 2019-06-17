#ifndef METAL_H
#define METAL_H

#include "Material.h"

class Metal: public Material {
    public:
        Metal(const vec3& a, double f);
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
    
    private:
        vec3 albedo;
        double fuzz;
};

#endif
#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "Ray.h"

class Dielectric: public Material {
    public:
        Dielectric(double ri);
        virtual bool scatter(const Ray& ray_in, const hit_record& rec, vec3& attenuation, Ray& ray_scattered) const;
    
    private:
        double refractive_index;
};

#endif